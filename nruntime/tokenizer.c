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

NSTATUS nextToken(struct program *program, struct program_token *token) {
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
                    if (!token->data_size) return NFATAL;
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
            return NFATAL;
    }
    return NSUCCESS;
}

void cleanupToken(struct program_token *token) {
    if (token->data_type == DT_STRING) {
        free((void *) token->data._string);
        token->data._string = NULL;
    }
}
