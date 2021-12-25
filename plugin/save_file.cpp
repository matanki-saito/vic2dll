#include "pch.h"
#include "plugin.h"
#include "escape_tool.h"

namespace SaveFile {
	extern "C" {
		void saveFileProc1();
		uintptr_t saveFileProc1InjectionFunctionAddress;
		uintptr_t saveFileProc1ReturnAddress;
	}

	PString* __fastcall saveFileProc1InjectionFunction(PString *s) {
		PString* t = utf8ToEscapedStr2(s);
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

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= saveFileProc1Injector(options);
		result |= saveFileProc2Injector(options);

		return result;
	}
}