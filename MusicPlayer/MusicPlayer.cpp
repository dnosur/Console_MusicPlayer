// MusicPlayer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Player.h";
#include <thread>

using namespace std;

//Добавлять музыку в папки в Playlist! 
// Музыка должна иметь формат .wav, или .mp3
//В названии не должно быть пробелов!

void Timer(Player& player, Color& color) {
    bool replay = false;

    string musicName;

    int l_seconds = 0;
    int minutes = 0;

    auto showTime = [](Player& player, Color& color) {
        color.SetColor(color.Red);
        if (player.Position() < 60) {
            wcout << trunc((_wtoi(player.Length()) / 1000) / 60) << ":"
                << (_wtoi(player.Length()) / 1000) - trunc((_wtoi(player.Length()) / 1000) / 60) * 60 << "  "
                << player.Position() << endl << endl;
        }
        else {
            wcout << trunc((_wtoi(player.Length()) / 1000) / 60) << ":"
                << (_wtoi(player.Length()) / 1000) - trunc((_wtoi(player.Length()) / 1000) / 60) * 60 << "  "
                << trunc(player.Position() / 60) << ":" << player.Position() - trunc(player.Position() / 60) * 60 << endl << endl;
        }
        color.ResetColor();
        Sleep(1000);
        };

    while (true) {
        if (player.IsPlaying()) {
            gotoxy(0, 0);

            if (musicName != player.GetCurrentMusic()) {
                musicName = player.GetCurrentMusic();
                player.UpdatePosition(0);
            }

            color.SetColor(color.Yellow);
            cout << "Playing -> " << musicName << endl;
            color.ResetColor();

            showTime(player, color);
            player.UpdatePosition(player.Position() + 1);
        }

        if (player.IsPause()) {
            gotoxy(0, 0);

            color.SetColor(color.Cyan);
            cout << "Pause -> " << musicName << endl;
            color.ResetColor();

            showTime(player, color);
        }
    }
}

void menu(FileManager& fileManager, Player& player, Color& color) {
    int press = 0;
    int iterator = 0;
    int exit = false;

    int seconds = 0;

    while (!exit) {

        if (player.IsPlaying()) seconds = player.Position();
        else seconds = 0;

        if (press) {
            switch (press)
            {
            case 72: { // Up
                if (iterator - 1 >= 0) iterator--;
                player.ShowAll(fileManager, iterator);
                break;
            }
            case 75: { //Left
                seconds -= 10;
                player.Seek(seconds);
                update(press);
                continue;
            }
            case 77: { //Right
                seconds += 10;
                player.Seek(seconds);
                update(press);
                continue;
                break;
            }
            case 80: { // Down
                if (iterator + 1 < fileManager.GetFilesCount()) iterator++;
                player.ShowAll(fileManager, iterator);
                break;
            }
            case 8: { //Backspace
                fileManager.SetMainPath();
                iterator = 0;
                update(press);
                clear();
                continue;
            }
            case 13: { //Enter
                if (fileManager.InMainDir()) {
                    fileManager.SetDir((char*)fileManager.GetFileBy(iterator).path().filename().string().c_str());
                    iterator = 0;
                }
                else {
                    player.Play(fileManager.GetFileBy(iterator).path().filename().string(), fileManager.GetFiles());
                    //_getch();
                }

                update(press);
                continue;
            }
            case 27: {
                player.Close();
                exit = true;
                continue;
            }
            case 32: { //Space
                if (player.IsPlaying()) player.Pause();
                else player.Resume();

                update(press);
                continue;
            }
            case 83: { //Delete
                fileManager.RemoveDir((char*)fileManager.GetFileBy(iterator).path().filename().string().c_str());
                update(press);
                continue;
            }
            case 99: { //C
                if (fileManager.InMainDir()) {
                    char* dir = new char[30];
                    int answ;

                    color.SetColor(color.Yellow);
                    cout << "Enter dir name (30 symbols) -> ";
                    cin.getline(dir, 30);

                    color.SetColor(color.Red);
                    cout << "\nCreate dir with name '" << dir << "'? y/n\n";
                    answ = _getch();

                    color.ResetColor();
                    if (answ == 'y') fileManager.CreateDir(dir);
                }
                else {
                    cout << "You should back to the main dir for create a new playlist!\n";
                    pause();
                }

                update(press);
                continue;
            }
            case 105: { //I

                update(press);
                continue;
            }
            case 114: { //R
                char* dir = new char[30];
                int answ;

                color.SetColor(color.Yellow);
                cout << fileManager.GetFileBy(iterator).path().filename().string().c_str() << endl;
                cout << "New name -> ";
                cin.getline(dir, 30);

                color.SetColor(color.Red);
                cout << "Would you like rename '" << fileManager.GetFileBy(iterator).path().filename().string().c_str() << "' to '" << dir << "' ?\n";
                answ = _getch();

                if (answ == 'y') {
                    fileManager.RenameDir((char*)fileManager.GetFileBy(iterator).path().filename().string().c_str(), dir);
                }

                color.ResetColor();
                update(press);
                break;
            }
            default:
                cout << press << endl;
                update(press);
                break;
            }
        }
        else player.ShowAll(fileManager);

        press = _getch();
        clear();

    }
}

int main()
{
    FileManager fileManager = FileManager();
    Color color = Color(GetStdHandle(STD_OUTPUT_HANDLE));
    Player player = Player(color);

    int seconds = 0;

    thread first(Timer, ref(player), ref(color));
    thread second(menu, ref(fileManager), ref(player), ref(color));

    first.join();
    second.join();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
