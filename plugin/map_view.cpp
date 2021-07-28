#include "pch.h"
#include "plugin.h"

namespace MapView {
	extern "C" {
		void mapViewProc1();
		uintptr_t mapViewProc1ReturnAddress;
		void mapViewProc2();
		uintptr_t mapViewProc2ReturnAddress;
		void mapViewProc3();
		uintptr_t mapViewProc3ReturnAddress;
		void mapViewProc4();
		uintptr_t mapViewProc4ReturnAddress;
		uintptr_t mapViewProc4CallAddress;
		void mapViewProc6();
		uintptr_t mapViewProc6ReturnAddress;
		uintptr_t mapViewProc6ReturnAddress2;

		void mapViewProc7();
		uintptr_t mapViewProc7ReturnAddress;
	}

	DWORD WINAPI CharUpperBuffAX(_Inout_updates_(cchLength) LPSTR lpsz, _In_ DWORD cchLength);

	DllError mapViewProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edx, [esp+328h+var_318]
			BytePattern::temp_instance().find_pattern("8B 54 24 10 0F B6 04 10 8B 55 08");
			if (BytePattern::temp_instance().has_size(1, u8"ÉãÅ[ÉvÇPÇÃï∂éöéÊìæèCê≥")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz	loc_xxxxx
				mapViewProc1ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, mapViewProc1, true);
			}
			else {
				e.unmatch.mapViewProc1Injector = true;
			}
			break;
		default:
			e.version.mapViewProc1Injector = true;
		}

		return e;
	}

	DllError mapViewProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   edx, byte ptr [edx+ebx]
			BytePattern::temp_instance().find_pattern("0F B6 14 1A 8B 7D 08 8B 94 97 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ÉãÅ[ÉvÇQÇÃï∂éöéÊìæèCê≥")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz	loc_xxxxx
				mapViewProc2ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, mapViewProc2, true);
			}
			else {
				e.unmatch.mapViewProc2Injector = true;
			}
			break;
		default:
			e.version.mapViewProc2Injector = true;
		}

		return e;
	}

	// ï ÇÃä÷êîÇ…Ç†ÇÈ
	DllError mapViewProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// movzx   ecx, byte ptr [eax+esi]
			BytePattern::temp_instance().find_pattern("0F B6 0C 30 8B 45 F0 8B 8C 88 94 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ï∂éöïùéÊìæèàóù")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz	loc_xxxxx
				mapViewProc3ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, mapViewProc3, true);
			}
			else {
				e.unmatch.mapViewProc3Injector = true;
			}
			break;
		default:
			e.version.mapViewProc3Injector = true;
		}

		return e;
	}

	DllError mapViewProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     edx, [esp+328h+var_318]
			BytePattern::temp_instance().find_pattern("8B 54 24 10 8A 04 10 88 44 24 28");
			if (BytePattern::temp_instance().has_size(1, u8"ÉãÅ[ÉvÇPÇÃÉRÉsÅ[èàóù")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// push    0FFFFFFFFh
				mapViewProc4ReturnAddress = address + 0x40;

				// call {xxxxx}
				mapViewProc4CallAddress = Injector::GetBranchDestination(address + 0x3B).as_int();

				Injector::MakeJMP(address, mapViewProc4, true);
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

	DllError mapViewProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// push    ecx
			BytePattern::temp_instance().find_pattern("51 50 FF D6 8B 85 40 FF FF FF");
			if (BytePattern::temp_instance().has_size(1, u8"CharUpperBuffA")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				uintptr_t ptr = Injector::ReadMemory<uintptr_t>(address - 4);
				void* adr = (void*) CharUpperBuffAX;
				Injector::WriteMemory(ptr, adr, true);
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

	DWORD WINAPI CharUpperBuffAX(_Inout_updates_(cchLength) LPSTR lpsz, _In_ DWORD cchLength) {
		//DWORD result = CharUpperBuffA(lpsz, cchLength);
		return cchLength;
	}

	DllError mapViewProc6Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// mov     eax, [edx+10h]
			BytePattern::temp_instance().find_pattern("8B 42 10 46 89 75 F4 89 45 E8 3B");
			if (BytePattern::temp_instance().has_size(1, u8"AAAA")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     edi, [ebp+var_4]
				mapViewProc6ReturnAddress2 = address + 0x12;

				// jl	xxxxx
				mapViewProc6ReturnAddress = address + 0xC;

				Injector::MakeJMP(address, mapViewProc6, true);
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

	DllError mapViewProc7Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// cvtpd2ps xmm0, xmm0
			BytePattern::temp_instance().find_pattern("66 0F 5A C0 0F 2F C8 0F 86 68 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"-")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jbe     loc_xxxxx
				mapViewProc7ReturnAddress = Injector::GetBranchDestination(address + 7).as_int();

				Injector::MakeJMP(address, mapViewProc7, true);
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

		result |= mapViewProc1Injector(options);
		result |= mapViewProc2Injector(options);
		//result |= mapViewProc3Injector(options);
		result |= mapViewProc4Injector(options);
		//result |= mapViewProc5Injector(options);
		//result |= mapViewProc6Injector(options);
		result |= mapViewProc7Injector(options);

		return result;
	}
}