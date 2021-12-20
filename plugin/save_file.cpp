#include "pch.h"
#include "plugin.h"
#include "escape_tool.h"

namespace SaveFile {
	extern "C" {
		void saveFileProc1();
		uintptr_t saveFileProc1InjectionFunctionAddress;
		uintptr_t saveFileProc1ReturnAddress;
	}

	void __fastcall saveFileProc1InjectionFunction(char** c) {
		while (*c != NULL) {
			printf("%s\n",*c);
			char* w = utf8ToEscapedStr3(*c);
			int len = strlen(w);
			memcpy(*c, w, len+1);
			*c++;
		}
	}

	DllError saveFileProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// add esp, 4
			BytePattern::temp_instance().find_pattern("83 C4 04 89 44 24 10 89 44 24 0C");
			if (BytePattern::temp_instance().has_size(1, u8"After PHYSFS_enumerateFiles")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz xxxxx
				saveFileProc1ReturnAddress = address + 0xD;

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