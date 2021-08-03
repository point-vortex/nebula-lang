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

#ifndef NEBULA_LANG_RUNTIME_H
#define NEBULA_LANG_RUNTIME_H

#include "tokenizer.h"

struct runtime_context {
    unsigned long stack_size;
    unsigned long meta_length;
    unsigned long meta_shift;
    unsigned long stack_shift;
    void *stack;
    struct stack_item_meta *meta;
};

struct stack_item_meta {
    uint32_t size;
    enum DATA_TYPE type;
};

struct runtime_context createRuntimeContext(long stack_buffer_size, long stack_cells_quantity);

void cleanupContext(struct runtime_context *context);

bool runtime(struct runtime_context *context, struct program_token *token, struct program *program);

bool execute(void *program, long stack_buffer_size, long stack_cells_size);

#endif //NEBULA_LANG_RUNTIME_H
