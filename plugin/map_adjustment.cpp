#include "pch.h"
#include "plugin.h"

namespace MapAdjustment {
	extern "C" {
		void mapAdjustmentProc1();
		uintptr_t mapAdjustmentProc1ReturnAddress;
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

	DllError Init(RunOptions options) {
		DllError result = {};

		 result |= mapAdjustmentProc1Injector(options);

		return result;
	}
}