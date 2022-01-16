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
#include <cstdio>
#include <string> 
#include <unordered_map>

#include "debug.h"
#include "HidKeyboard.h"
#include "UsbHidKeys.h"

using namespace std;

const unordered_map<char, int> char_key_map = {
    { '1', KEY_KP1 },
    { '2', KEY_KP2 },
    { '3', KEY_KP3 },
    { '4', KEY_KP4 },
    { '5', KEY_KP5 },
    { '6', KEY_KP6 },
    { '7', KEY_KP7 },
    { '8', KEY_KP8 },
    { '9', KEY_KP9 },
};

HidKeyboard::HidKeyboard(string deviceFilename)
{
    _deviceFilename = deviceFilename;
}

void send_key(FILE* device_file, unsigned short key, unsigned short mod)
{
    dprintf("     send_hid->send_key mod: %d   key: %d  \n", mod, key);
    fprintf(device_file, "%c%c%c%c%c%c%c%c", mod, '\0', key, '\0', '\0', '\0', '\0', '\0');
}

void HidKeyboard::Send(int data)
{
    dprintf("HidKeyboard::Send(int): %d \n", data);

    FILE* deviceFile = fopen(_deviceFilename.data(), "w");

    send_key(deviceFile, data, '\0');
    send_key(deviceFile, '\0', '\0'); // release all keys

    fclose(deviceFile);
}

void HidKeyboard::Send(string contents)
{
    dprintf("HidKeyboard::Send: %s \n", contents.data());

    FILE* deviceFile = fopen(_deviceFilename.data(), "w");

    for (int i = 0; i < contents.length(); i++)
    {
        int keyCode = char_key_map.at(contents[i]);
        send_key(deviceFile, keyCode, '\0');
        send_key(deviceFile, '\0', '\0'); // release all keys
    }

    fclose(deviceFile);
}
