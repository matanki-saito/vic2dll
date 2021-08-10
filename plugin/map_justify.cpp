#include "pch.h"
#include "plugin.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		uintptr_t mapJustifyProc1ReturnAddress1;
		uintptr_t mapJustifyProc1ReturnAddress2;
		uintptr_t mapJustifyProc1CallAddress;
		void mapJustifyProc2();
		uintptr_t mapJustifyProc2ReturnAddress;
		void mapJustifyProc3();
		uintptr_t mapJustifyProc3ReturnAddress;
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

	DllError mapJustifyProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// cvtpd2ps xmm0, xmm0
			BytePattern::temp_instance().find_pattern("66 0F 5A C0 0F 2F C8 0F 86 68 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"無効化")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jbe     loc_xxxxx
				mapJustifyProc2ReturnAddress = Injector::GetBranchDestination(address + 7).as_int();

				Injector::MakeJMP(address, mapJustifyProc2, true);
			}
			else {
				e.unmatch.mapJustifyProc2Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc2Injector = true;
		}

		return e;
	}

	DllError mapJustifyProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    1
			BytePattern::temp_instance().find_pattern("6A 01 68 ? ? ? ? 8D 8D 6C FF FF FF C7 45 80 0F");
			if (BytePattern::temp_instance().has_size(1, u8"領を入れる　例）イギリス領オーストリア")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call xxxxx
				mapJustifyProc3ReturnAddress = address + 0x21;

				Injector::MakeJMP(address, mapJustifyProc3, true);
			}
			else {
				e.unmatch.mapJustifyProc3Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapJustifyProc1Injector(options);
		//result |= mapJustifyProc2Injector(options); // （デバッグ用で使わない） 
		result |= mapJustifyProc3Injector(options);

		return result;
	}
}