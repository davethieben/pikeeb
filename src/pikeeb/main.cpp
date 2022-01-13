#include <stdio.h>

#include "PiMatrix.h"

using namespace std;

#define COL0 10
#define COL1 9
#define COL2 11

#define ROW0 5
#define ROW1 6
#define ROW2 13

#define LED0 23
#define LED1 24

int main()
{
	PiMatrix matrix;
	matrix.AddColumn(COL0);
	matrix.AddColumn(COL1);
	matrix.AddColumn(COL2);

	matrix.AddRow(ROW0);
	matrix.AddRow(ROW1);
	matrix.AddRow(ROW2);

	// row 0:
	matrix.AddMapping(0, 0, '7');
	matrix.AddMapping(1, 0, '8');
	matrix.AddMapping(2, 0, '9');

	// row 1:
	matrix.AddMapping(0, 1, '4');
	matrix.AddMapping(1, 1, '5');
	matrix.AddMapping(2, 1, '6');

	// row 2:
	matrix.AddMapping(0, 2, '1');
	matrix.AddMapping(1, 2, '2');
	matrix.AddMapping(2, 2, '3');

	matrix.Run();

	return 0;
}
