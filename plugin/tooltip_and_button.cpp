#include "pch.h"
#include "plugin.h"

namespace TooltipAndButton {
	extern "C" {
		void tooltipAndButtonProc1();
		uintptr_t tooltipAndButtonProc1ReturnAddress;
		void tooltipAndButtonProc3();
		uintptr_t tooltipAndButtonProc3ReturnAddress;
		void tooltipAndButtonProc4();
		uintptr_t tooltipAndButtonProc4ReturnAddress;
		uintptr_t tooltipAndButtonProc4CallAddress;

		void tooltipAndButtonProc5();
		uintptr_t tooltipAndButtonProc5ReturnAddress1;
		uintptr_t tooltipAndButtonProc5ReturnAddress2;
		uintptr_t tooltipAndButtonProc5ReturnAddress3;
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

	DllError tooltipAndButtonProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   eax, byte ptr [eax+esi]
			BytePattern::temp_instance().find_pattern("0F B6 04 30 8B 84 87 94 00 00 00 85 C0 0F 84 2F 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc
				tooltipAndButtonProc3ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, tooltipAndButtonProc3, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc3Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc3Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     cl, [eax+esi]
			BytePattern::temp_instance().find_pattern("8A 0C 30 88 8C 24 90 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字コピー処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// push 0FFFFFFFFh
				tooltipAndButtonProc4ReturnAddress = address + 0x46;

				// call xxxxx
				tooltipAndButtonProc4CallAddress = Injector::GetBranchDestination(address + 0x41).as_int();

				Injector::MakeJMP(address, tooltipAndButtonProc4, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc4Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc4Injector = true;
		}

		return e;
	}
	
	DllError tooltipAndButtonProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// cmp     [esp+400h+var_394], 0
			BytePattern::temp_instance().find_pattern("83 7C 24 6C 00 0F 85 A4 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"改行処理？")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// push    1
				tooltipAndButtonProc5ReturnAddress1 = address + 0x12;

				// jnz     loc_C32408
				tooltipAndButtonProc5ReturnAddress2 = Injector::GetBranchDestination(address + 5).as_int();

				// cmp     [esp+400h+var_3A0], 0
				tooltipAndButtonProc5ReturnAddress3 = address + 0xB;

				Injector::MakeJMP(address, tooltipAndButtonProc5, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc5Injector = true;
			}
			break;
		default:
			e.version.tooltipAndButtonProc5Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= tooltipAndButtonProc1Injector(options);

		result |= tooltipAndButtonProc3Injector(options);

		result |= tooltipAndButtonProc4Injector(options);

		result |= tooltipAndButtonProc5Injector(options);

		return result;
	}
}
