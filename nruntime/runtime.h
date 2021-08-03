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
