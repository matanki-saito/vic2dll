#include "pch.h"
#include "plugin.h"

namespace TooltipAndButton {
	extern "C" {
		void tooltipAndButtonProc1();
		uintptr_t tooltipAndButtonProc1ReturnAddress;
		void tooltipAndButtonProc2();
		uintptr_t tooltipAndButtonProc2ReturnAddress;
	}

	DllError tooltipAndButtonProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx eax, byte ptr [eax+ebx]
			BytePattern::temp_instance().find_pattern("0F B6 04 18 8B B4 87 94 00 00 00 85 F6 0F 85 C3");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc
				tooltipAndButtonProc1ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, tooltipAndButtonProc1, true);
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

	DllError tooltipAndButtonProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   eax, byte ptr [eax+esi]
			BytePattern::temp_instance().find_pattern("0F B6 04 30 8B BC 87 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"?")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc
				tooltipAndButtonProc2ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, tooltipAndButtonProc2, true);
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

		result |= tooltipAndButtonProc1Injector(options);

		result |= tooltipAndButtonProc2Injector(options);

		return result;
	}
}