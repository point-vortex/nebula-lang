#ifndef NEBULA_LANG_DSTACK_H
#define NEBULA_LANG_DSTACK_H

#include <stdbool.h>
#include "../enums/data_type.h"

struct dstack_item {
    void* data;
    unsigned long size;
    enum DATA_TYPE type;
};

struct dstack {
    void* buffer;
    unsigned long buffer_capacity;
    void* buffer_cursor;

    struct dstack_item* items;
    unsigned long items_capacity;
    struct dstack_item* items_cursor;
};

struct dstack* dstack_construct(unsigned long capacity, unsigned long buffer_capacity);
void dstack_destruct(struct dstack* this);
bool dstack_push(struct dstack* this, struct dstack_item *item);
bool dstack_pop(struct dstack* this);
bool dstack_top(struct dstack* this, struct dstack_item *item);
bool dstack_is_full(struct dstack* this);
bool dstack_is_empty(struct dstack* this);





#endif //NEBULA_LANG_DSTACK_H
