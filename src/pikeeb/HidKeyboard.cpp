#include <iostream>
#include <stdio.h>
#include <string> 

#include "HidKeyboard.h"

using namespace std;

HidKeyboard::HidKeyboard(string deviceFilename)
{
    _deviceFilename = deviceFilename;
}

void HidKeyboard::Send(string data)
{
	FILE* device_file = fopen(_deviceFilename.data(), "w");

	//sprintf("HidKeyboard::Send: %s \n", data);
	cout << "HidKeyboard::Send: " << data << endl;

	/*
	for (int i = 0; i < strlen(in_string); i++)
	{
		if (in_string[i] < 32)
		{
			if (in_string[i] != '\n' && in_string[i] != '\t')
			{
				fprintf(stderr, "Cannot print control characters!\n");
				return;
			}
		}

		char tmp[UTF8_MAX_LENGTH] = { in_string[i], in_string[i + 1], in_string[i + 2], '\0' };
		// TODO: replace by something less stupid
		if (in_string[i] < 128)
		{ // not multi byte
			tmp[1] = '\0';
		}
		else
		{ // is multi byte
			if (in_string[i] < 0xe0)
			{
				i++; // skip next thing
				tmp[2] = 0;
			}
			else
			{
				i += 2; // WARN: fails on utf8 > 3 byte
			}
		}

		struct keysym* s = toscan(tmp);
		if (s == NULL)
		{
			fprintf(stderr, "Key Symbol not found.\n");
			return;
		}

		struct layout* l = tolay(s, atoi("1"));
		if (l == NULL)
		{
			fprintf(stderr, "Unrecognised keyboard layout.\n");
			return;
		}

		if (l->key != 0x00)
		{
			send_key(device_file, l->key, l->mod);
			send_key(device_file, '\0', '\0'); // release all keys
			if (l->is_dead)
			{
				// dead keys need to be pressed twice to show up
				send_key(device_file, l->key, l->mod);
				send_key(device_file, '\0', '\0'); // release all keys
			}
		}
		else
		{
			// key does not exist in this layout, use unicode method
			fprintf(stderr, "Warning: Key '%s'(0x%x) not in this layout!\n", s->sym, s->unicode);
			//send_unicode(_device_file, s->unicode, atoi(argv[P_UNI]), atoi(argv[P_LAY]));
		}
	}
	*/

	fclose(device_file);
}

/*
void send_key(FILE* device_file, unsigned short key, unsigned short mod)
{
	printf("     send_hid->send_key mod: %d   key: %d  \n", mod, key);

	fprintf(device_file, "%c%c%c%c%c%c%c%c", mod, '\0', key, '\0', '\0', '\0', '\0', '\0');
}
*/
