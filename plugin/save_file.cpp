#include "pch.h"
#include "plugin.h"
#include "escape_tool.h"

namespace SaveFile {
	extern "C" {
		void saveFileProc1();
		uintptr_t saveFileProc1InjectionFunctionAddress;
		uintptr_t saveFileProc1ReturnAddress;

		void saveFileProc3();
		uintptr_t saveFileProc3ReturnAddress;

		void saveFileProc5();
		uintptr_t saveFileProc5InjectionFunctionAddress;
		uintptr_t saveFileProc5ReturnAddress;
	}

	PString* __fastcall saveFileProc1InjectionFunction(PString *s) {
		PString* t = utf8ToEscapedStr2(s);
		return t;
	}

	PString* __fastcall saveFileProc5InjectionFunction(PString* s) {
		PString* t = escapedStrToUtf8A(s);
		return t;
	}

	DllError saveFileProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    0FFFFFFFFh
			BytePattern::temp_instance().find_pattern("6A FF 6A 00 50 8D 8D 3C FF");
			if (BytePattern::temp_instance().has_size(1, u8"UTF8Str to SpecailEncodedText")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call xxxxx
				saveFileProc1ReturnAddress = address + 0xF;

				saveFileProc1InjectionFunctionAddress = (uintptr_t)saveFileProc1InjectionFunction;

				Injector::MakeJMP(address, saveFileProc1, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError saveFileProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edx, [esp+120h+var_114]
			BytePattern::temp_instance().find_pattern("8B 54 24 0C 8B 02 8B D0");
			if (BytePattern::temp_instance().has_size(1, u8"Skip ascii file name check")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz xxxxx -> jmp xxxx
				Injector::WriteMemory<byte>(address + 0xC,0xEB,true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError saveFileProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    0FFFFFFFFh
			BytePattern::temp_instance().find_pattern("6A FF 53 50 8D 4C 24 7C C6 84 24 38 01 00 00 13");
			if (BytePattern::temp_instance().has_size(1, u8"UTF8Str to SpecailEncodedText")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call xxxxx
				saveFileProc3ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, saveFileProc3, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError saveFileProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edx, [esi+10h]
			BytePattern::temp_instance().find_pattern("8B 56 10 57 33 FF 85 D2 0F 8E 7E 02 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"skip escape string")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jle loc_xxxxx -> jmp loc_xxxxx
				Injector::WriteMemory<byte>(address + 8, 0xE9, true);
				Injector::WriteMemory<byte>(address + 9, 0x7F, true);
				Injector::WriteMemory<byte>(address + 0xA, 0x02, true);
				Injector::WriteMemory<byte>(address + 0xB, 0x00, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError saveFileProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edi, [ebp+arg_4]
			BytePattern::temp_instance().find_pattern("8B 7D 0C 83 7F 14 10 72 04 8B 17 EB 02 8B D7 E8 ? ? ? ? 8B");
			if (BytePattern::temp_instance().has_size(1, u8"convert to UTF8")) {
				//
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				saveFileProc5InjectionFunctionAddress = (uintptr_t)saveFileProc5InjectionFunction;

				// call xxxxx
				saveFileProc5ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, saveFileProc5, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
			break;
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= saveFileProc1Injector(options);
		result |= saveFileProc2Injector(options);
		result |= saveFileProc3Injector(options);
		result |= saveFileProc4Injector(options);
		result |= saveFileProc5Injector(options);

		return result;
	}
}