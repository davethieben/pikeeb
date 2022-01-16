#pragma once
#include <string> 

using namespace std;

class HidKeyboard
{
    string _deviceFilename = "";

public:
    HidKeyboard(string deviceFilename);
    void Send(int data);
    void Send(string data);

};
