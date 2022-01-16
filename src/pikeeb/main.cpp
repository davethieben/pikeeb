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
#include <stdio.h>
#include "debug.h"
#include "HidKeyboard.h"
#include "PiMatrix.h"
#include "PiLights.h"
#include "UsbHidKeys.h"

using namespace std;

#define COL0	10		//	SPMOSI		// grey
#define COL1	9		//	SPMISO		// yellow
#define COL2	11		//	SPCLK		// purple

#define ROW0	5		//	GPIO5		// green
#define ROW1	6		//	GPIO6		// red
#define ROW2	13		//	GPIO13		// blue

#define LED0	23		//	GPIO23
#define LED1	24		//	GPIO24


int main()
{
    dprintf("pikeeb starting \n");

    PiMatrix matrix;
    PiLights lights;

    matrix.AddColumn(COL0);
    matrix.AddColumn(COL1);
    matrix.AddColumn(COL2);

    matrix.AddRow(ROW0);
    matrix.AddRow(ROW1);
    matrix.AddRow(ROW2);

    HidKeyboard kb("/dev/hidg0");
    //kb.Send("hello c++ kb");

    // indicate button presses w/ LED:
    matrix.AddMapping([](position_t pos) -> bool { return true; },
        [&lights](key_event_args args) -> void {
            if (args.pressed) lights.Enable(LED0);
            else lights.Disable(LED0);
        });

    // row 0:   
    matrix.AddMapping(0, 0, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("7");
        });
    matrix.AddMapping(1, 0, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("8");
        });
    matrix.AddMapping(2, 0, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("9");
        });

    // row 1:
    matrix.AddMapping(0, 1, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                //kb.Send("4");
                kb.Send(KEY_KP4);
        });
    matrix.AddMapping(1, 1, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("5");
        });
    matrix.AddMapping(2, 1, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("6");
        });

    // row 2:
    matrix.AddMapping(0, 2, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("1");
        });
    matrix.AddMapping(1, 2, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("2");
        });
    matrix.AddMapping(2, 2, [&kb](key_event_args args) -> void
        {
            if (args.pressed)
                kb.Send("3");
        });


    matrix.Run();
    return 0;
}
