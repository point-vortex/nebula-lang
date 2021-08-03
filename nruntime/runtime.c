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
                if (context->stack_shift + token->data_size >= context->stack_size) return false;

                context->meta[context->meta_shift].type = token->data_type;
                context->meta[context->meta_shift].size = token->data_size;
                if (token->data_type == DT_STRING) {
                    memcpy(context->stack + context->stack_shift, token->data._string,
                           token->data_size * sizeof(uint8_t));
                } else {
                    memcpy(context->stack + context->stack_shift, &token->data, token->data_size * sizeof(uint8_t));
                }
                ++context->meta_shift;
                context->stack_shift += token->data_size * sizeof(uint8_t);
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
