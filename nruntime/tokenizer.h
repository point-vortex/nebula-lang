#ifndef NEBULA_LANG_TOKENIZER_H
#define NEBULA_LANG_TOKENIZER_H

#include "enums/instruction.h"
#include "enums/data_type.h"

struct program {
    void *cursor;
    void *entry;
};

union dynamic_data {
    int _int;
    long _long;
    float _float;
    double _double;
    const char *_string;
};

struct program_token {
    union dynamic_data data;
    enum DATA_TYPE data_type;
    enum INSTRUCTION instruction;
    uint32_t data_size;
};

bool nextToken(struct program *program, struct program_token *token);

void cleanupToken(struct program_token *token);

#endif //NEBULA_LANG_TOKENIZER_H
