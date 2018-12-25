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

static ID3D12Device4* m_pDevice = nullptr;

bool EnableDebugLayer
    (
    )
{
    HRESULT hr = S_OK;

    ID3D12Debug1* pDebug = nullptr;
    hr = ::D3D12GetDebugInterface( __uuidof(ID3D12Debug1), ( void** )&pDebug );
    if( SUCCEEDED(hr) ) 
    {
        pDebug->EnableDebugLayer();
        
        pDebug->Release();
    }
    
    return SUCCEEDED(hr);                
}

bool CreateDevice
    (
    )
{
    HRESULT hr = S_OK;

    IDXGIFactory6* pFactory = nullptr;
    hr = ::CreateDXGIFactory2( BLITE_DXGI_DEBUG, __uuidof(IDXGIFactory6), ( void** )&pFactory );
    if( SUCCEEDED(hr) )
    {
        IDXGIAdapter4* pAdapter = nullptr;
        hr = pFactory->EnumWarpAdapter( __uuidof(IDXGIAdapter4), ( void** )&pAdapter );
        if( SUCCEEDED(hr) )
        {
            ID3D12Device4* pDevice = nullptr;
            hr = ::D3D12CreateDevice( pAdapter, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device4), ( void**)&pDevice );
            if( SUCCEEDED(hr) )
            {
                pDevice->AddRef();
                m_pDevice = pDevice;

                pDevice->Release();
            }
            pAdapter->Release();
        }
        pFactory->Release();
    }

    return SUCCEEDED(hr);                
}

void DestroyDevice
    (
    )
{
    if( m_pDevice )
    {
        m_pDevice->Release();
        m_pDevice = nullptr;
    }
}

}
