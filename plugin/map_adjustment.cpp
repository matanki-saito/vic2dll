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
			// dec ecx
			BytePattern::temp_instance().find_pattern("49 0F 57 C9 0F 5A C0 F3 0F 2A C9");
			if (BytePattern::temp_instance().has_size(1, u8"‹Ï“™Š„‚è•t‚¯")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtsi2ss xmm1, ecx
				mapAdjustmentProc1ReturnAddress = address + 0x7;

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