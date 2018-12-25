// Pre-compiled headers
//
// For the latest on this project, please see <https://github.com/tsereg/Blite>.
//
// Copyright (c) 2018 Tomislav �ereg (itobjectives.com). All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//
 #pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifdef _DEBUG
#define D3DCOMPILE_DEBUG 1
#endif

#include <windows.h>
#include <d3d12.h>                      // #include <%DXSDK_DIR%Include\d3d12.h>

