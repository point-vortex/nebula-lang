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
#include "flex_buffer.h"

NSTATUS flex_buffer_resize(struct flex_buffer* this, unsigned long new_capacity) {
    void* old_data = this->data;
    this->data = malloc(new_capacity * sizeof(uint8_t));
    if (!this->data) {
        this->data = old_data;
        return NFATAL;
    }
    memcpy(this->data, old_data, this->capacity);
    this->capacity = new_capacity;
    return NSUCCESS;
}

NSTATUS flex_buffer_construct(struct flex_buffer* this, unsigned long start_capacity) {
    this = malloc(sizeof(struct flex_buffer));
    this->data = malloc(start_capacity * sizeof(uint8_t));
    this->capacity = start_capacity;
    this->payload_size = 0;
    return NSUCCESS;
}

void flex_buffer_destruct(struct flex_buffer* this) {
    free(this->data);
    free(this);
}

NSTATUS flex_buffer_store(struct flex_buffer* this, void* data, unsigned long size) {
    if (this->capacity < size) {
        flex_buffer_resize(this, size);
    }
    memcpy(this->data, data, size * sizeof(uint8_t));
    this->payload_size = size;
    return NSUCCESS;
}
