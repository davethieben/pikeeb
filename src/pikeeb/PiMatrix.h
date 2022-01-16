#pragma once
#include <vector>
#include "Event.cpp"

using namespace std;

typedef pair<unsigned short, unsigned short> position_t;
typedef function<bool(position_t)> key_event_predicate;
typedef function<void(key_event_args)> key_event_handler;

struct key_event_args {
    position_t position;
    bool pressed;
};

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
