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
#include "addition_operation.h"

NSTATUS add(struct dstack_item *operand1, struct dstack_item *operand2) {
    switch (operand1->type) {
        case DT_INT:
            return add_int_int(operand1, operand2);
        case DT_LONG:
            return add_long_long(operand1, operand2);
        case DT_FLOAT:
            return add_float_float(operand1, operand2);
        case DT_DOUBLE:
            return add_double_double(operand1, operand2);
        default:
            return NERROR;
    }
}

NSTATUS add_int_int(struct dstack_item *operand1, struct dstack_item *operand2) {
    NSTATUS status = NSUCCESS;
    //TODO: figure out why: Clang-Tidy: Narrowing conversion from 'int' to signed type 'int16_t' (aka 'short') is implementation-defined
    *(int16_t *) operand1->data = *(int16_t *) (operand1->data) + *(int16_t *) (operand2->data);
    return status;
}

NSTATUS add_long_long(struct dstack_item *operand1, struct dstack_item *operand2) {
    NSTATUS status = NSUCCESS;
    *(int32_t *) operand1->data = *(int32_t *) (operand1->data) + *(int32_t *) (operand2->data);
    return status;
}

NSTATUS add_float_float(struct dstack_item *operand1, struct dstack_item *operand2) {
    NSTATUS status = NSUCCESS;
    *(float *) operand1->data = *(float *) (operand1->data) + *(float *) (operand2->data);
    return status;
}

NSTATUS add_double_double(struct dstack_item *operand1, struct dstack_item *operand2) {
    NSTATUS status = NSUCCESS;
    *(double *) operand1->data = *(double *) (operand1->data) + *(double *) (operand2->data);
    return status;
}
