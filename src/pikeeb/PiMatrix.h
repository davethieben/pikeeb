#pragma once
#include <vector>
#include "Event.cpp"

using namespace std;

struct key_event_args {
    pair<int, int> position;
    bool pressed;
};

typedef function<void(key_event_args)> key_event_handler;

struct key_map {
    pair<int, int> position;
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
    void AddMapping(int col, int row, key_event_handler handler);

    void Run();

private:

    void SetRow(int rowIndex, int state);
    void OnKeyChange(int colIndex, int rowIndex, bool isDown);

};