#include "pch.h"
#include "plugin.h"

namespace AnimatedText {
	extern "C" {
		void animatedTextProc1();
		void animatedTextProc2();
		void animatedTextProc3();
		uintptr_t animatedTextProc1ReturnAddress;
		uintptr_t animatedTextProc2ReturnAddress;
		uintptr_t animatedTextProc3ReturnAddress;
		uintptr_t animatedTextProc3CallAddress;
	}

	DllError animatedTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   eax, byte ptr [edx+eax]
			BytePattern::temp_instance().find_pattern("0F B6 04 02 8B 84 83 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Animated text")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz xxxxx
				animatedTextProc1ReturnAddress = address + 0x0D;

				Injector::MakeJMP(address, animatedTextProc1, true);
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

	DllError animatedTextProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   eax, byte ptr [eax+edx]
			BytePattern::temp_instance().find_pattern("0F B6 04 10 8B 8C 83 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Animated text")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz xxxxx
				animatedTextProc2ReturnAddress = address + 0x0D;

				Injector::MakeJMP(address, animatedTextProc2, true);
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

	DllError animatedTextProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edx, [esp+198h+var_184]
			BytePattern::temp_instance().find_pattern("8B 54 24 14 8A 04 10 88 44 24 28");
			if (BytePattern::temp_instance().has_size(1, u8"Animated text")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {xxxxx}
				animatedTextProc3CallAddress = Injector::GetBranchDestination(address+0x3F).as_int();

				// push    0FFFFFFFFh
				animatedTextProc3ReturnAddress = address + 0x44;

				Injector::MakeJMP(address, animatedTextProc3, true);
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

		result |= animatedTextProc1Injector(options);
		result |= animatedTextProc2Injector(options);
		result |= animatedTextProc3Injector(options);

		return result;
	}
}