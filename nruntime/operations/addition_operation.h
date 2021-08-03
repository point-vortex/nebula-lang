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

#ifndef NEBULA_LANG_ADDITION_OPERATION_H
#define NEBULA_LANG_ADDITION_OPERATION_H

#include "../utils/nstatus.h"
#include "../utils/dstack.h"

NSTATUS add(struct dstack_item* operand1, struct dstack_item* operand2);

NSTATUS add_int_int(struct dstack_item* operand1, struct dstack_item* operand2);
NSTATUS add_long_long(struct dstack_item* operand1, struct dstack_item* operand2);
NSTATUS add_float_float(struct dstack_item* operand1, struct dstack_item* operand2);
NSTATUS add_double_double(struct dstack_item* operand1, struct dstack_item* operand2);

#endif //NEBULA_LANG_ADDITION_OPERATION_H
