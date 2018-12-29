// Blite engine
//
// For the latest on this project, please see <https://github.com/tsereg/Blite>.
//
// Copyright (c) 2018 Tomislav �ereg (itobjectives.com). All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//
#pragma once

namespace blite
{

bool EnableDebugLayer
    (
    );

bool CreateDevice
    (
        bool bUseSoftwareRenderer
    );

void DestroyDevice
    (
    );

bool CreateCommandQueue
    (
    );

void DestroyCommandQueue
    (
    );

}
