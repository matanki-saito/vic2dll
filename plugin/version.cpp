#include "pch.h"
#include "plugin.h"

using namespace std;

namespace Version {
	typedef struct _Pattern {
		char ascii1;
		char dot;
		char ascii2;
		char ascii3;

		int calVer() {
			int ver = (ascii1 - 0x30) * 100 + (ascii2 - 0x30) * 10 + (ascii3 - 0x30);
			return ver;
		}
	} Pattern;

	string versionString(Vic2Version version) {
		switch (version) {
		case v3_0_4_0:
			return u8"v3_0_4_0";
		default:
			return u8"UNKNOWN";
		}
	}

	void GetVersionFromExe(RunOptions* options) {
		Vic2Version version;

		// V2 v?.??
		BytePattern::temp_instance().find_pattern("56 32 20 76 ? 2E ? ? 00");
		if (BytePattern::temp_instance().count() > 0) {
			// ??‚ðŽæ“¾‚·‚é
			Pattern minor = Injector::ReadMemory<Pattern>(BytePattern::temp_instance().get_first().address(0x4), true);

			switch (minor.calVer()) {
			case 304:
				version = v3_0_4_0;
				break;
			default:
				version = UNKNOWN;
				break;
				;;
			}
		}
		else {
			version = UNKNOWN;
		}

		BytePattern::LoggingInfo(versionString(version));

		options->version = version;
	}
}