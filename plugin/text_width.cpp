#include "pch.h"
#include "plugin.h"

namespace TextWidth {
	extern "C" {
		void textWidthProc1();
		uintptr_t textWidthProc1ReturnAddress;

		void textWidthProc2();
		uintptr_t textWidthProc2ReturnAddress;

		void textWidthProc3();
		uintptr_t textWidthProc3ReturnAddress1;
		uintptr_t textWidthProc3ReturnAddress2;

		void textWidthProc4();
		uintptr_t textWidthProc4ReturnAddress;
	}

	DllError textWidthProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   eax, byte ptr [eax+esi]
			BytePattern::temp_instance().find_pattern("0F B6 04 30 8B BC 87 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"改行のためのカウント処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc
				textWidthProc1ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, textWidthProc1, true);
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

	DllError textWidthProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     al, [ebx+edx]
			BytePattern::temp_instance().find_pattern("8A 04 13 0F B6 C8 8B 8C 8E 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字幅取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      short loc_xxxxx
				textWidthProc2ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, textWidthProc2, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError textWidthProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     al, [ebx+edx]
			BytePattern::temp_instance().find_pattern("43 3B 5D F4 0F 8C 13 FF FF FF");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jl      loc_{xxxxx}
				textWidthProc3ReturnAddress1 = Injector::GetBranchDestination(address + 4).as_int();
				// mov     eax, [ebp+var_8]
				textWidthProc3ReturnAddress2 = address + 0x0A;

				Injector::MakeJMP(address, textWidthProc3, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError textWidthProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   ecx, byte ptr [eax+ebx]
			BytePattern::temp_instance().find_pattern("0F B6 0C 18 8B 45 E0 8B BC 88 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz_xxxxx
				textWidthProc4ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, textWidthProc4, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		// ルーチンA
		result |= textWidthProc1Injector(options);

		// ルーチンB
		result |= textWidthProc2Injector(options);
		result |= textWidthProc3Injector(options);

		// ルーチンC
		result |= textWidthProc4Injector(options);

		return result;
	}
}