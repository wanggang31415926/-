#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"th.h"

#pragma comment(lib , "winmm.lib")

#define DEFAULT_VOLUMN 0x4f
#define DEFAULT_VOICE 0x0
#define DEFAULT_SLEEP 300

void playMuaic();

int main()
{
	playMuaic();
	system("pause");

	return 0;
}

void playMuaic()
{
	HMIDIOUT handle;
	midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);

	//音量大小
	int volume = DEFAULT_VOLUMN ;

	//乐器
	DWORD voice = DEFAULT_VOICE;

	//演示
	int sleep = DEFAULT_SLEEP;

	int i = 0;
	for (i = 0; i < sizeof(trivial); i++)
	{
		if (trivial[i] == LOW_SPEED || trivial[i] == MIDDLE_SPEED || trivial[i] == HIGH_SPEED)
		{
			sleep = trivial[i];
			continue;
		}

		if (trivial[i] == 0)
		{
			sleep = 150;
			continue;
		}
		else if (trivial[i] == 700)
		{
			Sleep(180);
			continue;
		}
		else if (trivial[i] == _)
		{
			Sleep(DEFAULT_SLEEP);
			continue;
		}
		volume =  0x4f;
		voice = (volume << 16) + (trivial[i] << 8) + 0x90;
		midiOutShortMsg(handle, voice);
		Sleep(sleep);
	}
}