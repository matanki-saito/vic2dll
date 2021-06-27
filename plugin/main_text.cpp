#include "pch.h"
#include "plugin.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		uintptr_t maintTextProc1SrcAddress;
		uintptr_t maintTextProc1ReturnAddress;
	}

	DllError maintTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov al, byte_xxxx[eax]
			BytePattern::temp_instance().find_pattern("8A 80 ? ? ? ? 0F B6 C8 8B BC 8B 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc
				maintTextProc1ReturnAddress = address + 0x12;

				maintTextProc1SrcAddress = Injector::ReadMemory<uint32_t>(address + 2);

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

		result |= maintTextProc1Injector(options);

		return result;
	}
}