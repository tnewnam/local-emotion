// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <TlHelp32.h>

#include "Classes.h"
#include "xor.h"
#include "hkdD3D9.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// TODO: reference additional headers your program requires here
