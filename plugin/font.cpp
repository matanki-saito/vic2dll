#include "pch.h"
#include "plugin.h"

namespace Font {

	DllError fontBufferHeapZeroClearInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			// db
			// test ebx, ebx
			BytePattern::temp_instance().find_pattern("59 85 DB 74 04");
			if (BytePattern::temp_instance().has_size(1, "Font buffer heap zero clear")) {
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0xE), 0x08, true);
			}
			else {
				e.unmatch.fontBufferHeapZeroClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferHeapZeroClearInjector = true;
		}

		return e;
	}

	DllError fontBufferExpansionInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v3_0_4_0:
			BytePattern::temp_instance().find_pattern("68 BC 26 00 00");
			if (BytePattern::temp_instance().has_size(1, "Font buffer expansion")) {
				// push 26BCh
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferExpansionInjector = true;
			}
			break;
		default:
			e.version.fontBufferExpansionInjector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		BytePattern::LoggingInfo(u8"font etc fix");

		/* zero clear*/
		result |= fontBufferHeapZeroClearInjector(options);

		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		return result;
	}
}