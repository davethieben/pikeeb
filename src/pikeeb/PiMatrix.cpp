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

void PiMatrix::AddMapping(int col, int row, key_event_handler handler)
{
    _keyMaps.push_back({ make_pair(col, row), handler });
}

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
    //printf("PiMatrix Key %s: %d, %d \n", (isDown ? "Down" : " Up "), colIndex, rowIndex);

    for (key_map map : _keyMaps)
    {
        if (map.position.first == colIndex && map.position.second == rowIndex)
        {
            map.handler({ make_pair(colIndex, rowIndex), isDown });
        }
    }

}
