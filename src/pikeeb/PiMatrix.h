#pragma once
#include <vector>

using namespace std;

typedef char 	map_t;
// TODO - typedef - struct { char[] send_chars, delegate* handler } n

class PiMatrix {

    vector<int> _rows;
    vector<int> _cols;

    vector<vector<map_t>> _layout;

public:
    PiMatrix();

    void AddColumn(int bcmPinNumber);
    void AddRow(int bcmPinNumber);
    void AddMapping(int col, int row, map_t mapped);

    void Run();

private: 

    void SetRow(int rowIndex, int state);
    void OnKeyChange(int colIndex, int rowIndex, bool isDown);

};