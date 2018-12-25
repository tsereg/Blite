// Blite engine initialization and cleanup.
//
// For the latest on this project, please see <https://github.com/tsereg/Blite>.
//
// Copyright (c) 2018 Tomislav Šereg (itobjectives.com). All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//
#include "common.h"
#include "blite.h"

namespace blite
{

bool EnableDebugLayer
    (
    )
{
    ID3D12Debug* pDebug = nullptr;

    HRESULT hr = S_OK;
    hr = ::D3D12GetDebugInterface( __uuidof(ID3D12Debug), ( void** )&pDebug );
    if( FAILED(hr) ) 
        return false;

    pDebug->EnableDebugLayer();
    pDebug->Release();

    return true;
}

}
