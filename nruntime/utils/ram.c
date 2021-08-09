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

#include <malloc.h>

#include "ram.h"

NSTATUS ram_reset(struct ram* ram) {
    if (!ram) return NFATAL;

    ram->ip = 0;
    ram->sp = ram->max_address;
    ram->fp = ram->sp;
    ram->lp = ram->sp - 1;

    /// Initialize registers
    ram->r1 = 0;
    ram->r2 = 0;
    ram->r3 = 0;
    ram->r4 = 0;
    return NSUCCESS;
}

struct ram* ram_construct(nword capacity) {
    struct ram* this = malloc(sizeof(struct ram));
    this->max_address = capacity;
    ram_reset(this);
    return this;
}
