#pragma once
#include "pch.h"

enum Vic2Version {
	UNKNOWN = 0,
	v3_0_4_0 = 3040,
};

typedef UINT64 DllErrorCode;

struct DllError {
	union {
		DllErrorCode code0;
		struct {
			bool timeout : 1;
			bool waitFailed : 1;
			bool proccessFaild : 1;
		};
	} mod;

	union {
		DllErrorCode code1;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
			bool mapViewProc1Injector : 1;
			bool mapViewProc2Injector : 1;
			bool mapViewProc3Injector : 1;
			bool mapViewProc4Injector : 1;
			bool mapAdjustmentProc1Injector : 1;
			bool mapAdjustmentProc2Injector : 1;
			bool mapAdjustmentProc3Injector : 1;
			bool mapAdjustmentProc4Injector : 1;
			bool mapAdjustmentProc5Injector : 1;
			bool mapJustifyProc1Injector : 1;
			bool mapJustifyProc2Injector : 1;
			bool mapJustifyProc3Injector : 1;
			bool mapJustifyProc4Injector : 1;
			bool eventDialog1Injector : 1;
			bool eventDialog2Injector : 1;
			bool mapPopupProc1Injector : 1;
			bool mapPopupProc2Injector : 1;
			bool mapPopupProc3Injector : 1;
			bool listFieldAdjustmentProc1Injector : 1;
			bool listFieldAdjustmentProc2Injector : 1;
			bool listFieldAdjustmentProc3Injector : 1;
			bool fileSaveProc1Injector : 1;
			bool fileSaveProc2Injector : 1;
			bool fileSaveProc3Injector : 1;
			bool fileSaveProc4Injector : 1;
			bool fileSaveProc5Injector : 1;
			bool fileSaveProc6Injector : 1;
			bool fileSaveProc7Injector : 1;
			bool dateProc1Injector : 1;
			bool mapNudgeViewProc1Injector : 1;
			bool imeProc1Injector : 1;
			bool imeProc2Injector : 1;
			bool imeProc3Injector : 1;
			bool inputProc1Injector : 1;
			bool inputProc2Injector : 1;
			bool localizationProc1Injector : 1;
			bool localizationProc2Injector : 1;
			bool localizationProc3Injector : 1;
			bool localizationProc4Injector : 1;
			bool localizationProc5Injector : 1;
			bool localizationProc6Injector : 1;
			bool localizationProc7Injector : 1;
			bool localizationProc8Injector : 1;
			bool localizationProc9Injector : 1;
		};
	} version;

	union {
		DllErrorCode code2;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc3Injector2 : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
			bool mapViewProc1Injector : 1;
			bool mapViewProc2Injector : 1;
			bool mapViewProc3Injector : 1;
			bool mapViewProc4Injector : 1;
			bool mapAdjustmentProc1Injector : 1;
			bool mapAdjustmentProc2Injector : 1;
			bool mapAdjustmentProc3Injector : 1;
			bool mapAdjustmentProc4Injector : 1;
			bool mapAdjustmentProc5Injector : 1;
			bool mapJustifyProc1Injector : 1;
			bool mapJustifyProc2Injector : 1;
			bool mapJustifyProc3Injector : 1;
			bool mapJustifyProc4Injector : 1;
			bool eventDialog1Injector : 1;
			bool eventDialog2Injector : 1;
			bool mapPopupProc1Injector : 1;
			bool mapPopupProc2Injector : 1;
			bool mapPopupProc3Injector : 1;
			bool listFieldAdjustmentProc1Injector : 1;
			bool listFieldAdjustmentProc2Injector : 1;
			bool listFieldAdjustmentProc3Injector : 1;
			bool fileSaveProc1Injector : 1;
			bool fileSaveProc2Injector : 1;
			bool fileSaveProc3Injector : 1;
			bool fileSaveProc4Injector : 1;
			bool fileSaveProc5Injector : 1;
			bool fileSaveProc6Injector : 1;
			bool fileSaveProc7Injector : 1;
			bool dateProc1Injector : 1;
			bool mapNudgeViewProc1Injector : 1;
			bool imeProc1Injector : 1;
			bool imeProc2Injector : 1;
			bool imeProc3Injector : 1;
			bool inputProc1Injector : 1;
			bool inputProc2Injector : 1;
			bool localizationProc1Injector : 1;
			bool localizationProc2Injector : 1;
			bool localizationProc3Injector : 1;
			bool localizationProc4Injector : 1;
			bool localizationProc5Injector : 1;
			bool localizationProc6Injector : 1;
			bool localizationProc7Injector : 1;
			bool localizationProc8Injector : 1;
			bool localizationProc9Injector : 1;
		};
	} unmatch;

	void operator |= (DllError e)
	{
		this->mod.code0 |= e.mod.code0;
		this->version.code1 |= e.version.code1;
		this->unmatch.code2 |= e.unmatch.code2;
	}
};

// same std::basic_string<char>
typedef struct _ParadoxTextObject {
	union {
		char text[0x10];
		char* p;
	} t;
	UINT32 len;
	UINT32 len2;

	std::string getString() {
		if (len2 >= 0x10) {
			return std::string(t.p);
		}
		else {
			return std::string(t.text);
		}
	}

	void setString(std::string* src) {

		len = src->length();

		if (len >= 0x10) {
			len2 = 0x1F;
			auto p = (char*)calloc(len + 3, sizeof(char));
			if (p != NULL) {
				memcpy(p, src->c_str(), len);
				t.p = p;
			}
		}
		else {
			memcpy(t.text, src->c_str(), len);
		}
	}

} PString;

typedef struct _RunOptions {
	Vic2Version version;
	bool test;
	bool reversingWordsBattleOfArea;
	int separateCharacterCodePoint;
} RunOptions;

namespace Version {
	void GetVersionFromExe(RunOptions* option);
}

namespace Ini {
	void GetOptionsFromIni(RunOptions* option);
}

namespace Debug {
	DllError Init(RunOptions option);
}

namespace Font {
	DllError Init(RunOptions option);
}

namespace MainText {
	DllError Init(RunOptions option);
}

namespace TooltipAndButton {
	DllError Init(RunOptions option);
}

namespace MapView {
	DllError Init(RunOptions option);
}

namespace MapAdjustment {
	DllError Init(RunOptions option);
}

namespace MapJustify {
	DllError Init(RunOptions option);
}

namespace EventDialog {
	DllError Init(RunOptions option);
}

namespace MapPopup {
	DllError Init(RunOptions option);
}

namespace ListFieldAdjustment {
	DllError Init(RunOptions option);
}

namespace Validator {
	void Validate(DllError dllError, RunOptions options);
	bool ValidateVersion(DllError dllError, RunOptions options);
}

namespace FileSave {
	DllError Init(RunOptions option);
}

namespace LoadingText {
	DllError Init(RunOptions option);
}

namespace Date {
	DllError Init(RunOptions option);
}

namespace MapNudgeView {
	DllError Init(RunOptions option);
}

namespace Ime {
	DllError Init(RunOptions option);
}

namespace Input {
	DllError Init(RunOptions option);
}

namespace Localization {
	DllError Init(RunOptions option);
}

namespace TextWidth {
	DllError Init(RunOptions option);
}

namespace SaveFile {
	DllError Init(RunOptions option);
}

namespace Input {
	DllError Init(RunOptions option);
}

namespace Localization {
	DllError Init(RunOptions option);
}
