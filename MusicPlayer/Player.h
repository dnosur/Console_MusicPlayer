#pragma once
#include "FileManager.h"
#include "helpers.h";
#include "Color.h"

#include <future>
#include <Mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

#include <string>
using namespace std;

class Player
{
	 const int maxFileView = 5;
	 bool isPlay = false;
	 bool isPause = false;

	 wchar_t* w_length;
	 int seconds;

	 string currentMusic;

	 std::filesystem::path* playlist;
	 int playlistSize;

	 Color color;
public:
	 Player(Color color);

	 void ShowAll(FileManager& fileManager, int select = -1);

	 void Play(string music, std::filesystem::directory_iterator files);

	 wchar_t* Length();
	 int Position();

	 void UpdatePosition(int seconds);

	 void Seek(int seconds);

	 string GetCurrentMusic();

	 void Pause();
	 void Resume();
	 void Stop();
	 void Close();

	 bool IsPlaying();
	 bool IsPause();
};

