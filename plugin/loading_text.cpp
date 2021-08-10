#include "pch.h"
#include "plugin.h"

namespace LoadingText {
	extern "C" {
		void loadingTextProc1();
		uintptr_t loadingTextProc1ReturnAddress;
		uintptr_t loadingTextProc1DataAddress;
		uintptr_t loadingTextProc1HookFuncAddress;
	}

	int WINAPI loadingTextProc1HookFunc(
		ID3DXFont& self,
		THIS_ LPD3DXSPRITE pSprite,
		LPCSTR pString,
		INT Count,
		LPRECT pRect,
		DWORD Format,
		D3DCOLOR Color
	) {
		return self.DrawTextW(pSprite, L"ÇµÇŒÇÁÇ≠Ç®ë“Çøâ∫Ç≥Ç¢Åc", 11, pRect, Format, Color);
	}

	DllError loadingTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    ecx
			BytePattern::temp_instance().find_pattern("51 50 FF D2 A1 ? ? ? ? 8B 08");
			if (BytePattern::temp_instance().has_size(1, u8"ID3DXFont::DrawText")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov	ecx, [eax]
				loadingTextProc1ReturnAddress = address + 0x9;

				// dword_xxxxx
				loadingTextProc1DataAddress = Injector::ReadMemory<uintptr_t>(address + 5, true);

				// 
				void* p = (void*)loadingTextProc1HookFunc;
				loadingTextProc1HookFuncAddress = (uintptr_t)p;

				Injector::MakeJMP(address, loadingTextProc1, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= loadingTextProc1Injector(options);

		return result;
	}
}