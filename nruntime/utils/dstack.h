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

#ifndef NEBULA_LANG_DSTACK_H
#define NEBULA_LANG_DSTACK_H

#include <stdbool.h>
#include "../enums/data_type.h"
#include "nstatus.h"

struct dstack_item {
    void *data;
    unsigned long size;
    enum DATA_TYPE type;
};

struct dstack {
    void *buffer;
    unsigned long buffer_capacity;
    void *buffer_cursor;

    struct dstack_item *items;
    unsigned long items_capacity;
    struct dstack_item *items_cursor;

    unsigned long items_chunk_size;
    unsigned long buffer_chunk_size;
};

struct dstack *dstack_construct(unsigned long capacity, unsigned long buffer_capacity);
void dstack_destruct(struct dstack *this);
NSTATUS dstack_push(struct dstack *this, struct dstack_item *item);
NSTATUS dstack_pusha(struct dstack *this, void *data, unsigned long size, enum DATA_TYPE type);
NSTATUS dstack_pop(struct dstack *this);
struct dstack_item *dstack_top(struct dstack *this);
bool dstack_is_full(struct dstack *this);
bool dstack_is_empty(struct dstack *this);


#endif //NEBULA_LANG_DSTACK_H
