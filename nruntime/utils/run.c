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

#include <stdbool.h>

#include "../enums/nword.h"
#include "ram.h"
#include "nstatus.h"

NSTATUS run(struct ram* ram) {
    nword r1 = 0;
    nword r2 = 0;
    nword r3 = 0;
    nword r4 = 0;

    // Lets suppose that ram is preparad (ip, sp, ...)

    bool running = true;
    while (running) {
        switch (ram->memory[ram->ip++]) {
            /// STACK OPERATIONS
            case I_CONST:
                ram->memory[--ram->sp] = ram->memory[ram->ip++];
                continue;
            case I_PUSH:
                r1 = ram->memory[ram->ip++];
                ram->memory[--ram->sp] = ram->memory[r1];
                continue;
            case I_POP:
                r1 = ram->memory[ram->ip++];
                ram->memory[r1] = ram->memory[ram->sp++];
                continue;
            /// ARITHMETIC OPERATIONS
            case I_ADD:
                r2 = ram->memory[ram->sp++];
                r1 = ram->memory[ram->sp++];
                ram->memory[--ram->sp] = r1 + r2;
            /// FLOW CONTROL
            case I_JMP:
                ram->ip += ram->memory[ram->ip];
                continue;
            case I_JMPZ:
                r1 = ram->memory[ram->sp++];
                r1 ? ram->ip += ram->memory[ram->ip] : ram->ip++;
                continue;
            /// FUNCTIONS CALL
            case I_CALL:
                r1 = ram->memory[ram->ip++];
                r2 = ram->memory[ram->ip++];
                r2 = ram->sp + r2;
                ram->memory[--ram->sp] = ram->ip;
                ram->memory[--ram->sp] = ram->fp;
                ram->memory[--ram->sp] = ram->lp;
                ram->ip = r1;
                ram->fp = r2;
                ram->lp = ram->sp - 1;
                continue;
            case I_RET:
                r1 = ram->memory[ram->sp++];
                r2 = ram->lp;
                ram->sp = ram->fp;
                ram->lp = ram->memory[r2 + 1];
                ram->fp = ram->memory[r2 + 2];
                ram->ip = ram->memory[r2 + 3];
                continue;
            case I_SYSCALL:
                r1 = ram->memory[ram->ip++];
                // SYSTEM CALL;
                continue;
            case I_HALT:
                running = false;
                continue;
            /// VARIABLES
            case I_LOAD:
                r1 = ram->memory[ram->ip++];
                r2 = ram->lp - r1;
                ram->memory[--ram->sp] = ram->memory[r2];
                continue;
            case I_STORE:
                r1 = ram->memory[ram->ip++];
                r2 = ram->lp - r1;
                ram->memory[r2] = ram->memory[ram->sp++];
                continue;
            case I_ARG:
                r1 = ram->memory[ram->ip++];
                r2 = ram->fp - r1 - 1;
                ram->memory[--ram->sp] = ram->memory[r2];
                continue;
            default:
                return NFATAL;
        }
    }
}

NSTATUS prepare_ram(struct ram* ram) {
    ram->ip = 0;
    ram->sp = ram->max_address;
    ram->fp = ram->sp;
    ram->lp = ram->sp - 1;
}