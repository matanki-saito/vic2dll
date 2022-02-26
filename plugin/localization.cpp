#include "pch.h"
#include "plugin.h"

namespace Localization {
	extern "C" {
		void localizationProc1();
		uintptr_t localizationProc1ReturnAddress;
	}

	DllError localizationProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    0Ch
			BytePattern::temp_instance().find_pattern("6A 0C 68 ? ? ? ? 8D 4C 24 74");
			if (BytePattern::temp_instance().has_size(1, u8"MainDate:ISSUE-3")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call xxxxx
				localizationProc1ReturnAddress = address + 0x1D;

				Injector::MakeJMP(address, localizationProc1, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc1Injector = true;
			}

			break;
		default:
			e.version.tooltipAndButtonProc1Injector = true;
		}

		return e;
	}


	DllError Init(RunOptions options) {
		DllError result = {};

		result |= localizationProc1Injector(options);

		return result;
	}
}