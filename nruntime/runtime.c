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

#include <stdint.h>
#include <malloc.h>

#include "runtime.h"
#include "operations/operations.h"


NSTATUS runtime(struct runtime_context *context, struct flex_buffer *buffer, struct program *program) {
    NSTATUS status = NSUCCESS;
    struct program_token token;
    while (nextToken(program, &token, buffer) && token.instruction != I_TERMINATE) {
        switch (token.instruction) {
            case I_PUSH:
                if (dstack_is_full(context->stack)) return NERROR;
                status = dstack_pusha(context->stack, token.data, token.size, token.type);
                break;
            case I_POP:
                if (dstack_is_empty(context->stack)) return NERROR;
                status = dstack_pop(context->stack);
                break;
            case I_FETCH:
                // TODO: create variables map.
                break;

            case I_ADD: {
                struct dstack_item *operand2 = dstack_top(context->stack);
                status = dstack_pop(context->stack);
                if (status != NSUCCESS) return status;
                struct dstack_item *operand1 = dstack_top(context->stack);
                add(operand1, operand2);
            }
                break;
        }
    }
    return status;
}

NSTATUS execute(void *program_binaries, long stack_buffer_size, long stack_cells_size) {
    struct runtime_context *context = runtime_context_construct(stack_buffer_size, stack_cells_size);
    if (!context) return NFATAL;
    struct program program = {program_binaries, program_binaries};
    struct flex_buffer *buffer = flex_buffer_construct(128);
    if (!buffer) {
        runtime_context_destruct(context);
        return NFATAL;
    }

    NSTATUS status = runtime(context, buffer, &program);

    flex_buffer_destruct(buffer);
    runtime_context_destruct(context);
    return status;
}

struct runtime_context *runtime_context_construct(long stack_buffer_size, long stack_cells_quantity) {
    struct runtime_context *this = malloc(sizeof(struct runtime_context));
    if (!this) return NULL;
    this->stack = dstack_construct(30, 1024);
    return this;
}

void runtime_context_destruct(struct runtime_context *this) {
    free(this->stack);
    free(this);
}
