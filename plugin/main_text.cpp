#include "pch.h"
#include "plugin.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		void mainTextProc3();
		void mainTextProc4();
		void mainTextProc5();

		uintptr_t maintTextProc1SrcAddress;
		uintptr_t maintTextProc1ReturnAddress;
		uintptr_t maintTextProc2SrcAddress;
		uintptr_t maintTextProc2DstAddress;
		uintptr_t maintTextProc3ReturnAddress;
		uintptr_t maintTextProc4ReturnAddress1;
		uintptr_t maintTextProc4ReturnAddress2;
		uintptr_t maintTextProc5ReturnAddress;
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

	DllError maintTextProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov cl, byte_xxxxx[eax]
			BytePattern::temp_instance().find_pattern("8A 88 ? ? ? ? 88 8E ? ? ? ? 46 80");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の文字コピー処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				maintTextProc2SrcAddress = Injector::ReadMemory<uint32_t>(address + 2);
				maintTextProc2DstAddress = Injector::ReadMemory<uint32_t>(address + 8);
			}
			else {
				e.unmatch.mainTextProc2Injector = true;
			}
			break;
		default:
			e.version.mainTextProc2Injector = true;
		}

		return e;
	}


	DllError maintTextProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx ecx, cl
			BytePattern::temp_instance().find_pattern("0F B6 C9 8B 8C 8B 94 00 00 00 85 C9");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				maintTextProc3ReturnAddress = address + 0xC;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.unmatch.mainTextProc3Injector = true;
			}
			break;
		default:
			e.version.mainTextProc3Injector = true;
		}

		return e;
	}

	DllError maintTextProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// cmp     [esp+530h+var_4E8], 0
			BytePattern::temp_instance().find_pattern("83 7C 24 48 00 0F 85 2F 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz loc_xxxxx
				maintTextProc4ReturnAddress1 = address + 5;

				// mov     eax, [ebp+arg_1C]
				maintTextProc4ReturnAddress2 = address + 0xB;

				Injector::MakeJMP(address, mainTextProc4, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError maintTextProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     eax, [esp+530h+var_514]
			BytePattern::temp_instance().find_pattern("8B 44 24 1C 40 89 44 24 1C 3B 44 24 2C");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１のカウントアップ処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jl loc_xxxxx
				maintTextProc5ReturnAddress = address + 0xD;

				Injector::MakeJMP(address, mainTextProc5, true);
			}
			else {
				e.unmatch.mainTextProc4Injector = true;
			}
			break;
		default:
			e.version.mainTextProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= maintTextProc1Injector(options);

		result |= maintTextProc2Injector(options);

		result |= maintTextProc3Injector(options);

		result |= maintTextProc4Injector(options);

		result |= maintTextProc5Injector(options);

		return result;
	}
}