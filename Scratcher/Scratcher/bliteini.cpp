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
        bool bUseSoftwareRenderer
    )
{
    assert( !m_pDevice );

    HRESULT hr = S_OK;

    // Creating a factory object that is used to enumerate available graphics adapters.

    IDXGIFactory6* pFactory = nullptr;
    hr = ::CreateDXGIFactory2( BLITE_DXGI_DEBUG, __uuidof(IDXGIFactory6), ( void** )&pFactory );
    if( SUCCEEDED(hr) )
    {
        // Either a software renderer is chosen as a adapter, or a hardware adapter has to be found that supports
        // Direct3D 12.

        if( bUseSoftwareRenderer )
        {
            // A device is created that uses the WARP software renderer.

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
        }
        else
        {
            // An actual video card has to be found.

            IDXGIAdapter1* pAdapterIter = nullptr;
            UINT           nEnumIndex   = 0;
            bool           bFound       = false;
            while( !bFound && DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(nEnumIndex, &pAdapterIter) )
            {
                // The adapter has to support DGXI v. 1.6 interface.                

                IDXGIAdapter4* pAdapter = nullptr;
                hr = pAdapterIter->QueryInterface(__uuidof(IDXGIAdapter4), ( void** )&pAdapter);
                if( SUCCEEDED(hr) )
                {
                    // The adapter has to be hardware adapter, not a software renderer.

                    DXGI_ADAPTER_DESC3 desc;
                    pAdapter->GetDesc3(&desc);
                    if( 0 == (DXGI_ADAPTER_FLAG_SOFTWARE & desc.Flags) )
                    {
                        // The driver has to suport Direct3D 12.

                        ID3D12Device4* pDevice = nullptr;
                        hr = ::D3D12CreateDevice( pAdapter, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device4), ( void**)&pDevice );
                        if( SUCCEEDED(hr) )
                        {
                            bFound = true;

                            pDevice->AddRef();
                            m_pDevice = pDevice;

                            pDevice->Release();
                        }
                    }
                    pAdapter->Release();
                }

                pAdapterIter->Release();
                nEnumIndex++;
            }
        }

        pFactory->Release();
    }

    return !!m_pDevice;
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
