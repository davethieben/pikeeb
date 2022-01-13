#include <stdio.h>
#include <wiringPi.h>

#include "PiMatrix.h"

using namespace std;

PiMatrix::PiMatrix()
{
    int setupResult = wiringPiSetupGpio();
    if (setupResult == -1) // use BCM pin numbering
    {
        printf("Setup wiringPi failed\n");
        return;
    }

}

void PiMatrix::AddColumn(int bcmPinNumber)
{
    // add to cols array
    _cols.push_back(bcmPinNumber);

    pinMode(bcmPinNumber, INPUT);
    pullUpDnControl(bcmPinNumber, PUD_DOWN);
}

void PiMatrix::AddRow(int bcmPinNumber)
{
    // add to rows array
    _rows.push_back(bcmPinNumber);

    pinMode(bcmPinNumber, OUTPUT);
    digitalWrite(bcmPinNumber, LOW);
}

void PiMatrix::AddMapping(int col, int row, map_t mapped)
{
    //printf("PiMatrix AddMapping: %d, %d = %c \n", col, row, mapped );

    while (col >= _layout.size())
    {
        vector<map_t> newcol;
        _layout.push_back(newcol);
    }

    vector<map_t> *colmap = &_layout[col];
    while(row >= colmap->size())
    {
        map_t newrow;
        colmap->push_back(newrow);
    }

    _layout.at(col).at(row) = mapped;
    //printf("PiMatrix AddMapping done \n");
}
// TODO - AddMapping(col, row, char[] output) => _layout[col][row] = (delegate)(() => { hid_send(output); });

void PiMatrix::Run()
{
    int ncols = _cols.size();
    int nrows = _rows.size();
    printf("PiMatrix: Found %d columns and %d rows\n", ncols, nrows);

    int matrix[ncols][nrows];

    printf("PiMatrix: Running...\n");

    while (1)
    {
        delay(10);

        for (int row = 0; row < nrows; row++)
        {
            SetRow(row, HIGH);

            for (int col = 0; col < ncols; col++)
            {
                if (digitalRead(_cols[col]) == HIGH)
                {
                    if (matrix[col][row] != HIGH)
                    {
                        matrix[col][row] = HIGH;
                        OnKeyChange(col, row, 1);
                    }
                    else
                    {
                        //printf(" Still: %d, %d \n", col, row);
                    }
                }
                else if (matrix[col][row] == HIGH)
                {
                    matrix[col][row] = LOW;
                    OnKeyChange(col, row, 0);
                }
            }

            SetRow(row, LOW);
            delay(2);
        }
    }
}

void PiMatrix::SetRow(int rowIndex, int state)
{
    digitalWrite(_rows[rowIndex], state);
}

void PiMatrix::OnKeyChange(int colIndex, int rowIndex, bool isDown)
{
    map_t keycode = _layout[colIndex][rowIndex];

    printf("Key %s: %d, %d - Key Code: %d \n", (isDown ? "Down" : " Up "), colIndex, rowIndex, keycode);

}
