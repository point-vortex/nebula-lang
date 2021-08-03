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

#include <malloc.h>
#include <memory.h>
#include <stdint.h>
#include <errno.h>

#include "dstack.h"

extern int errno;

struct dstack *dstack_construct(unsigned long capacity, unsigned long buffer_capacity) {
    struct dstack *this = (struct dstack *) malloc(sizeof(struct dstack));
    this->items_capacity = capacity;
    this->buffer_capacity = buffer_capacity;
    this->items = (struct dstack_item *) malloc(capacity * sizeof(struct dstack_item));
    this->items_cursor = this->items;
    this->buffer = malloc(buffer_capacity * sizeof(uint8_t));
    this->buffer_cursor = this->buffer;
    return this;
}

NSTATUS extend_buffer(struct dstack *this, unsigned long delta) {
    void *old_buffer = this->buffer;
    unsigned long old_capacity = this->buffer_capacity;
    unsigned long shift = this->buffer_cursor - this->buffer;

    this->buffer_capacity = old_capacity + delta;
    this->buffer = malloc(this->buffer_capacity * sizeof(uint8_t));
    if (this->buffer == NULL) {
        this->buffer = old_buffer;
        this->buffer_capacity = old_capacity;
        return NFATAL;
    }
    this->buffer_cursor = this->buffer + shift;
    memcpy(this->buffer, old_buffer, old_capacity);
    free(old_buffer);
    return NSUCCESS;
}

inline bool check_capacity_is_enough(struct dstack *this, unsigned long size) {
    return this->buffer_cursor + size < this->buffer + this->buffer_capacity;
}

void dstack_destruct(struct dstack *this) {
    free(this->items);
    free(this->buffer);
    free(this);
}

NSTATUS dstack_push(struct dstack *this, struct dstack_item *item) {
    const unsigned long chunk_size = 1024 * sizeof(uint8_t);

    if (!item) return NERROR;

    unsigned long size_to_extend = 0;
    while (!check_capacity_is_enough(this, size_to_extend)) {
        size_to_extend += chunk_size;
    }
    if (size_to_extend) extend_buffer(this, size_to_extend);

    memcpy(this->buffer_cursor, item->data, item->size * sizeof(uint8_t));
    *(++this->items_cursor) = *item;
    this->items_cursor->data = this->buffer_cursor;
    this->buffer_cursor += item->size * sizeof(uint8_t);

    return NSUCCESS;
}

NSTATUS dstack_pop(struct dstack *this) {
    this->buffer_cursor -= this->items_cursor->size;
    --this->items_cursor;
    return NSUCCESS;
}

NSTATUS dstack_top(struct dstack *this, struct dstack_item *item) {
    *item = *this->items_cursor;
    return NSUCCESS;
}

bool dstack_is_full(struct dstack *this) {
    return this->items_cursor == this->items + this->items_capacity - 1;
}

bool dstack_is_empty(struct dstack *this) {
    return this->items == this->items_cursor;
}
