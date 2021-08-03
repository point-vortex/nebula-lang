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

#ifndef NEBULA_LANG_TOKENIZER_H
#define NEBULA_LANG_TOKENIZER_H

#include "utils/nstatus.h"
#include "utils/flex_buffer.h"
#include "enums/instruction.h"
#include "enums/data_type.h"

struct program {
    void *cursor;
    void *entry;
};

//union dynamic_data {
//    int _int;
//    long _long;
//    float _float;
//    double _double;
//    const char *_string;
//};

struct program_token {
//    union dynamic_data data;
    void* data;
    enum DATA_TYPE type;
    enum INSTRUCTION instruction;
    uint32_t size;
};

NSTATUS nextToken(struct program *program, struct program_token *token, struct flex_buffer* buffer);

#endif //NEBULA_LANG_TOKENIZER_H
