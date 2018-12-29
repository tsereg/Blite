// Menu command handlers
//
// For the latest on this project, please see <https://github.com/tsereg/Blite>.
//
// Copyright (c) 2018 Tomislav Šereg (itobjectives.com). All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//
#include "common.h"
#include "commands.h"
#include "blite.h"

void OnFileNewHandler
    (
        HWND hWnd
    )
{
    if( !blite::EnableDebugLayer() )
        return;
    if( !blite::CreateDevice(false) && !blite::CreateDevice(true) )
        return;
    if( !blite::CreateCommandQueue() )
    {
        blite::DestroyDevice();
        return;
    }
    if( !blite::CreateSwapChain(hWnd) )
    {
        blite::DestroyCommandQueue();
        blite::DestroyDevice();
        return;
    }
}

void OnFileCloseHandler
    (
    )
{
    blite::DestroySwapChain();
    blite::DestroyCommandQueue();
    blite::DestroyDevice();
}
