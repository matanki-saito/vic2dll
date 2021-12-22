// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin.h"
#include "mod_download.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ulReasonForCall,
                       LPVOID lpReserved
                     )
{
	if (ulReasonForCall == DLL_PROCESS_ATTACH) {
		BytePattern::StartLog(L"vic2_jps");

		DllError e = {};

		// 設定
		RunOptions options;

		// Version取得
		Version::GetVersionFromExe(&options);

		// INIから取得
		Ini::GetOptionsFromIni(&options);

		// Versionチェック
		if (Validator::ValidateVersion(e, options)) {

			// mod download
#ifndef _DEBUG
			e |= ModDownload::Init();
#endif

			// フォント読み込み
			e |= Font::Init(options);

			// テキスト幅
			e |= TextWidth::Init(options);

			// メインテキスト
			e |= MainText::Init(options);

			// ツールチップとボタン
			e |= TooltipAndButton::Init(options);

			// Map表示
			e |= MapView::Init(options);
			e |= MapJustify::Init(options);
			e |= MapAdjustment::Init(options);

			// ロード画面
			e |= LoadingText::Init(options);

			// セーブ
			//e |= SaveFile::Init(options);

			Validator::Validate(e, options);
		}
	}
	else if (ulReasonForCall == DLL_PROCESS_DETACH) {
		BytePattern::ShutdownLog();
	}
	return TRUE;
}

