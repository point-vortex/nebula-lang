//  MIT License
//
// Copyright (c) 2021 Danil Maksimovich Andrieiev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef NEBULA_LANG_RAM_H
#define NEBULA_LANG_RAM_H

#include "nstatus.h"
#include "../enums/nword.h"

/**
 * Random Access Memory for Nebula runtime.
 * @c
 * @author Danil Andreev
 * @copyright Copyright (c) 2021 Danil Maksimovich Andrieiev
 */
struct ram {
    /// Memory buffer
    nword *memory;
    /// Instruction pointer
    nword ip;
    /// Stack pointer
    nword sp;
    /// Frame pointer
    nword fp;
    /// Locals pointer
    nword lp;

    nword max_address;

    /// Registers
    nword r1;
    nword r2;
    nword r3;
    nword r4;
};

NSTATUS ram_reset(struct ram* ram);

struct ram* ram_construct(nword capacity);

#endif //NEBULA_LANG_RAM_H
