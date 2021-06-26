#pragma once

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <filesystem>
#include <shlobj.h>
#include "plugin.h"

using namespace std;
using namespace std::filesystem;

namespace ModDownload {
	DllError Init();
}