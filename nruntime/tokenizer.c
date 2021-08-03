#include <memory.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

#include "tokenizer.h"

uint32_t getDataTypeSize(enum DATA_TYPE type) {
    switch (type) {
        case DT_DOUBLE:
            return sizeof(double);
        case DT_FLOAT:
            return sizeof(float);
        case DT_INT:
            return sizeof(uint16_t);
        case DT_LONG:
            return sizeof(uint32_t);
        default:
            return 0;
    }
}

bool nextToken(struct program *program, struct program_token *token) {
    token->instruction = (enum INSTRUCTION) (*(uint16_t *) program->cursor);
    program->cursor += sizeof(uint16_t);
    switch (token->instruction) {
        case I_STORE:
        case I_FETCH:
            token->data_size = *(uint32_t *) program->cursor;
            program->cursor += sizeof(uint32_t);

            token->data_type = DT_STRING;
            token->data._string = (const char *) malloc(token->data_size * sizeof(uint8_t)); //TODO: use allocator
            memcpy((void *) token->data._string, program->cursor, token->data_size * sizeof(uint8_t));
            program->cursor += token->data_size * sizeof(uint8_t);
            break;
        case I_PUSH:
            token->data_type = (enum DATA_TYPE) (*(uint16_t *) program->cursor);
            program->cursor += sizeof(uint16_t);


            switch (token->data_type) {
                case DT_STRING:
                    token->data_size = *(uint32_t *) program->cursor;
                    program->cursor += sizeof(uint32_t);
                    token->data._string = (const char *) malloc(
                            token->data_size * sizeof(uint8_t)); //TODO: use allocator
                    memcpy((void *) token->data._string, program->cursor, token->data_size * sizeof(uint8_t));
                    break;
                default:
                    token->data_size = getDataTypeSize(token->data_type);
                    if (!token->data_size) return false;
                    memcpy((void *) &token->data, program->cursor, token->data_size * sizeof(uint8_t));
                    break;
            }
            program->cursor += token->data_size * sizeof(uint8_t);
            break;
        case I_ADD:
        case I_TERMINATE:
        case I_POP:
            token->data_size = 0;
            token->data_type = DT_NONE;
        default:
            return false;
    }
    return true;
}

void cleanupToken(struct program_token *token) {
    if (token->data_type == DT_STRING) {
        free((void *) token->data._string);
        token->data._string = NULL;
    }
}
