// Copyright (c) 2017 Dillon Huff

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "gcode_program.h"

using namespace std;

namespace gpr {

ostream& operator<<(ostream& stream, const chunk& ic) {
    ic.print(stream);
    return stream;
}

ostream& operator<<(ostream& stream, const block& block) {
    block.print(stream);
    return stream;
}

ostream& operator<<(ostream& stream, const gcode_program& program) {
    for (auto b : program) { stream << b << endl; }
    return stream;
}

addr make_int_address(const int i) {
    addr_value v;
    v.int_val = i;
    return addr{ADDRESS_TYPE_INTEGER, v};
}

addr make_double_address(const double i) {
    addr_value v;
    v.dbl_val = i;
    return addr{ADDRESS_TYPE_DOUBLE, v};
}

chunk make_word_int(const char c, const int i) {
    addr int_address = make_int_address(i);
    return chunk(c, int_address);
}

chunk make_word_double(const char c, const double i) {
    addr double_addr = make_double_address(i);
    return chunk(c, double_addr);
}

bool operator==(const chunk& l, const chunk& r) {
    return l.equals(r);
}

bool operator!=(const chunk& l, const chunk& r) {
    return !(l == r);
}

chunk make_comment(const char start_delim,
                   const char end_delim,
                   const std::string& comment_text) {
    return chunk(start_delim, end_delim, comment_text);
}

chunk make_percent_chunk() {
    return chunk();
}

chunk make_isolated_word(const char c) {
    return chunk(c);
}
}
