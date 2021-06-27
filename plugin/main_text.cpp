#include "pch.h"
#include "plugin.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		uintptr_t mainTextProc1ReturnAddress;
	}

	DllError mainTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx eax, byte ptr [eax+ebx]
			BytePattern::temp_instance().find_pattern("0F B6 04 18 8B B4 87 94 00 00 00 85 F6 0F 85 C3");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc
				mainTextProc1ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, mainTextProc1, true);
			}
			else {
				e.unmatch.mainTextProc1Injector = true;
			}
			break;
		default:
			e.version.mainTextProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mainTextProc1Injector(options);

		return result;
	}
}