#include <stdio.h>

#include "HidKeyboard.h"
#include "PiMatrix.h"

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
    printf("pikeeb starting \n");

    PiMatrix matrix;

    matrix.AddColumn(COL0);
    matrix.AddColumn(COL1);
    matrix.AddColumn(COL2);

    matrix.AddRow(ROW0);
    matrix.AddRow(ROW1);
    matrix.AddRow(ROW2);

    HidKeyboard kb("/dev/hidg0");
    //kb.Send("hello c++ kb");

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
                kb.Send("4");
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
