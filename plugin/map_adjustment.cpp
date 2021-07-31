#include "pch.h"
#include "plugin.h"

namespace MapAdjustment {
	extern "C" {
		void mapAdjustmentProc1();
		uintptr_t mapAdjustmentProc1ReturnAddress;

		void mapAdjustmentProc2();
		uintptr_t mapAdjustmentProc2ReturnAddress;
	}

	DllError mapAdjustmentProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// xorps   xmm0, xmm0
			BytePattern::temp_instance().find_pattern("0F 57 C0 F3 0F 2A C3 49 0F 57 C9 0F 5A C0 F3 0F 2A C9");
			if (BytePattern::temp_instance().has_size(1, u8"均等割り付け")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtsi2ss xmm1, ecx
				mapAdjustmentProc1ReturnAddress = address + 0xB;

				Injector::MakeJMP(address, mapAdjustmentProc1, true);
			}
			else {
				e.unmatch.mapAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc1Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// xorps   xmm0, xmm0
			BytePattern::temp_instance().find_pattern("0F 86 74 0B 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"a")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				mapAdjustmentProc2ReturnAddress = Injector::GetBranchDestination(address).as_int();

				Injector::MakeJMP(address, mapAdjustmentProc2, true);
			}
			else {
				e.unmatch.mapAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.version.mapAdjustmentProc2Injector = true;
		}

		return e;
	}


	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapAdjustmentProc1Injector(options);
		result |= mapAdjustmentProc2Injector(options);

		return result;
	}
}