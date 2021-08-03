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
#include <memory.h>
#include <malloc.h>
#include <stdbool.h>

#include "runtime.h"
#include "tokenizer.h"
#include "enums/instruction.h"


bool runtime(struct runtime_context *context, struct program_token *token, struct program *program) {
    while (nextToken(program, token) && token->instruction != I_TERMINATE) {
        switch (token->instruction) {
            case I_PUSH:
                if (context->meta_shift >= context->meta_length) return false;
                if (context->stack_shift + token->size >= context->stack_size) return false;

                context->meta[context->meta_shift].type = token->type;
                context->meta[context->meta_shift].size = token->size;
                if (token->type == DT_STRING) {
                    memcpy(context->stack + context->stack_shift, token->data._string,
                           token->size * sizeof(uint8_t));
                } else {
                    memcpy(context->stack + context->stack_shift, &token->data, token->size * sizeof(uint8_t));
                }
                ++context->meta_shift;
                context->stack_shift += token->size * sizeof(uint8_t);
                break;
            case I_POP:
                if (context->meta_shift <= 0) return false;
                --context->meta_shift;
                break;
            case I_FETCH:
                // TODO: create variables map.
                break;

            case I_ADD: {
                if (context->meta_shift <= 1) return false;
                struct stack_item_meta* l_meta = &context->meta[context->meta_shift - 2];
                struct stack_item_meta* r_meta = &context->meta[context->meta_shift - 1];
                void* lvalue = context->stack + context->stack_shift - l_meta->size;
                void* rvalue = context->stack + context->stack_shift - l_meta->size - r_meta->size;

                //TODO: add functions.

                context->meta_shift -= 2ul;
            }
                break;
        }
        cleanupToken(token);
    }
    return true;
}

bool execute(void *program, long stack_buffer_size, long stack_cells_size) {
    struct runtime_context context = createRuntimeContext(stack_buffer_size, stack_cells_size);
    struct program prog = {program, program};
    struct program_token token;

    bool status = runtime(&context, &token, &prog);

    cleanupToken(&token);
    cleanupContext(&context);
    return status;
}

struct runtime_context createRuntimeContext(long stack_buffer_size, long stack_cells_quantity) {
    struct runtime_context context;
    context.stack_shift = 0l;
    context.stack_shift = 0l;
    context.stack_size = stack_cells_quantity;
    context.stack_size = stack_buffer_size;
    context.stack = malloc(stack_buffer_size * sizeof(int8_t));
    context.meta = (struct stack_item_meta*)malloc(context.meta_length * sizeof(struct stack_item_meta));
    return context;
}

void cleanupContext(struct runtime_context *context) {
    free(context->meta);
    context->meta = NULL;
    free(context->stack);
    context->stack = NULL;
}
