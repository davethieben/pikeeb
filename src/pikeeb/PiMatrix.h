/* MIT License - Copyright (c) 2022 Dave Thieben (https://github.com/davethieben/pikeeb)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once
#include <vector>
#include "Event.cpp"

using namespace std;

typedef pair<unsigned short, unsigned short> position_t;
typedef function<bool(position_t)> key_event_predicate;

struct key_event_args {
    position_t position;
    bool pressed;
};
typedef function<void(key_event_args)> key_event_handler;

struct key_map {
    key_event_predicate predicate;
    key_event_handler handler;
};

class PiMatrix
{
    vector<int> _rows;
    vector<int> _cols;
    
    list<key_map> _keyMaps;

public:
    PiMatrix();

    void AddColumn(int bcmPinNumber);
    void AddRow(int bcmPinNumber);
    void AddMapping(key_event_predicate predicate, key_event_handler handler);
    void AddMapping(int col, int row, key_event_handler handler);

    void Run();

private:

    void SetRow(int rowIndex, int state);
    void OnKeyChange(int colIndex, int rowIndex, bool isDown);

};
