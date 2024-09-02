#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(Color color) {
    this->color = color;
    this->seconds = 0;
    this->playlistSize = 0;
}

void Player::ShowAll(FileManager& fileManager, int select)
{
    int i = 0;

    color.SetColor(color.Yellow);
    cout << "\n\nDir -> " << fileManager.GetPath() << endl << endl;
    color.ResetColor();

    for (const auto& entry : fileManager.GetFiles()) {

        if ((select <= -1 && i < maxFileView) || (i >= (select / maxFileView) * maxFileView && i <= (1 + (select / maxFileView)) * maxFileView)) {
            if (entry.path().filename().string().find(".mp3") != -1) color.SetColor(color.Cyan);

            if (i == select) {
                color.SetColor(color.White, color.Green);

                cout << "> " << i << ": " << entry.path().filename().string() << endl;
            }
            else cout << i << ": " << entry.path().filename().string() << endl;

            color.ResetColor();
        }

        i++;
    }

    if (!i) {
        color.SetColor(color.Brown);
        cout << "\n\tEMPTY\n";
    }

    if (fileManager.InMainDir()) {
        color.SetColor(color.Green);
        cout << "\n\tEnter - Select dir     ";

        color.SetColor(color.Yellow);
        cout << "C - Create dir    ";

        color.SetColor(color.Red);
        cout << "Delete - remove dir\n";
    }
    else {
        color.SetColor(color.LightMagenta);
        cout << "\n\tEnter - Play one     ";

        color.SetColor(color.Blue);
        cout << "I - Play playlist from    ";

        color.SetColor(color.Red);
        cout << "Delete - remove music      ";

        color.SetColor(color.Magenta);
        cout << "Backspace - back\n";
    }

    color.ResetColor();
    cout << endl;
}

void Player::Play(string music, std::filesystem::directory_iterator files)
{
    if (music.find(".mp3") != -1 || music.find(".wav") != -1) {
        string str = "open " + music + " alias MY_SND";

        wstring widestr = std::wstring(str.begin(), str.end());

        Close();

        mciSendString(widestr.c_str(), NULL, 0, NULL);
        mciSendString(TEXT("play MY_SND"), NULL, 0, NULL);

        wchar_t* dur = new wchar_t[128];
        mciSendString(L"status MY_SND length", dur, 128, 0);

        w_length = dur;

        currentMusic = music;
        isPlay = true;
    }
}


wchar_t* Player::Length()
{
    return w_length;
}

int Player::Position()
{
    return seconds;
}

string Player::GetCurrentMusic()
{
    return currentMusic;
}

void Player::Pause() {
    if (isPlay) {
        mciSendString(TEXT("pause MY_SND"), NULL, 0, NULL);
        isPlay = false;
        isPause = true;
    }
}

void Player::Resume(){
    if (!isPlay) {
        mciSendString(TEXT("resume MY_SND"), NULL, 0, NULL);
        isPlay = true;
        isPause = false;
    }
}

void Player::Stop()
{
    mciSendString(L"stop MY_SND", NULL, 0, NULL);
    isPlay = false;
    isPause = false;
}

void Player::Close()
{
    Stop();
    seconds = 0;
    w_length = 0;
    mciSendString(L"close MY_SND", NULL, 0, NULL);
}

bool Player::IsPlaying() { return isPlay; }

void Player::UpdatePosition(int seconds)
{
    if (seconds * 1000 >= _wtoi(w_length)) {
        Close();
    }
    else this->seconds = seconds;
}

void Player::Seek(int seconds)
{
    if (seconds < 0 || seconds * 1000 >= _wtoi(w_length)) Close();

    string str = "play MY_SND from " + to_string(seconds*1000);
    wstring widestr = std::wstring(str.begin(), str.end());

    mciSendString(widestr.c_str(), NULL, 0, 0);
    this->seconds = seconds;
}

bool Player::IsPause()
{
    return isPause;
}