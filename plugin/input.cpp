#include "pch.h"
#include "plugin.h"
#include "escape_tool.h"

namespace Input {
	extern "C" {
		void inputProc1();
		uintptr_t inputProc1ReturnAddress1;
		uintptr_t inputProc1ReturnAddress2;
		uintptr_t DefWindowProcHookAddress;
	}

	int machineCP = 0;

	LRESULT WINAPI DefWindowProcHook(
		_In_ HWND hWnd,
		_In_ UINT Msg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam) {

		if (Msg == 0x286) { // WM_IME_CHAR

			// IMEから渡ってきたコードポイントはマシン依存（Multibyte）であるためUnicodeにする
			char imeSource[32] = { 0 };

			// TODO
			// 4 byte
			if (wParam > 0xFFFFFF) {
				imeSource[0] = (wParam & 0xFF000000) >> 24;
				imeSource[1] = (wParam & 0xFF0000) >> 16;
				imeSource[2] = (wParam & 0xFF0000) >> 8;
				imeSource[3] = wParam & 0xFF;
			}
			// 3 byte
			else if (wParam > 0xFFFF) {
				imeSource[0] = (wParam & 0xFF0000) >> 16;
				imeSource[1] = (wParam & 0xFF00) >> 8;
				imeSource[2] = wParam & 0xFF;
			}
			// 2 byte
			else if (wParam > 0xFF) {
				imeSource[0] = (wParam & 0xFF00) >> 8;
				imeSource[1] = wParam & 0xFF;
			}
			// 1 byte
			else if (wParam > 0) {
				imeSource[0] = wParam & 0xFF;
			}

			int wideTextSize = MultiByteToWideChar(
				machineCP,
				NULL,
				imeSource,
				-1,
				NULL,
				NULL);

			WCHAR w[32];
			auto err = MultiByteToWideChar(
				machineCP,
				NULL,
				imeSource,
				-1,
				w,
				wideTextSize);

			// Unicodeから特殊エンコードに変換する
			char* s = NULL;
			convertWideTextToEscapedText(w, &s);
			for(int i=0;i<strlen(s);i++){
				//DefWindowProcA(hWnd, WM_CHAR, w, 1);
				SendMessageA(hWnd, WM_CHAR, (byte)s[i], 1);
			}

			free(s);

			return NULL;
		}
		else {
			return DefWindowProcA(hWnd, Msg, wParam, lParam);
		}
	}

	DllError inputProc1Injector(RunOptions options) {
		DllError e = {};

		// https://docs.microsoft.com/ja-jp/windows/win32/api/winnls/nf-winnls-getacp
		// get machine codepage
		machineCP = GetACP();

		switch (options.version) {
		case v3_0_4_0:
			// mov     eax, [ebp+lParam]
			BytePattern::temp_instance().find_pattern("8B 45 14 8B 4D 08 50 52 56 51");
			if (BytePattern::temp_instance().has_size(1, u8"DefWindowProcA")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    ds:DefWindowProcA
				inputProc1ReturnAddress1 = address +0xA;

				// skip DefWindowProcA 
				inputProc1ReturnAddress2 = address + 0x10;

				DefWindowProcHookAddress = (uintptr_t)DefWindowProcHook;

				Injector::MakeJMP(address, inputProc1, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc2Injector = true;
			}

			break;
		default:
			e.version.tooltipAndButtonProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= inputProc1Injector(options);

		return result;
	}
}