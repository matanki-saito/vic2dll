#include "pch.h"
#include "plugin.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		uintptr_t mapJustifyProc1ReturnAddress1;
		uintptr_t mapJustifyProc1ReturnAddress2;
		uintptr_t mapJustifyProc1CallAddress;
	}

	DllError mapJustifyProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     byte ptr [ebp+var_4], 0Bh
			BytePattern::temp_instance().find_pattern("C6 45 FC 0B 39 7D C0 72 0C 8B 4D AC");
			if (BytePattern::temp_instance().has_size(1, u8"リターンアドレス取得")) {
				mapJustifyProc1ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}

			// mov     cl, [eax+esi]
			BytePattern::temp_instance().find_pattern("8A 0C 30 8D 45 18 88 4D 18 8D 50 01");
			if (BytePattern::temp_instance().has_size(1, u8"スペース挿入")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// push    0FFFFFFFFh
				mapJustifyProc1ReturnAddress1 = address + 0x25;

				// call {xxxxx}
				mapJustifyProc1CallAddress = Injector::GetBranchDestination(address + 0x20).as_int();

				Injector::MakeJMP(address, mapJustifyProc1, true);
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapJustifyProc1Injector(options);

		return result;
	}
}