#include "FileManager.h"

FileManager::FileManager() {
	SetDir((char*)"Playlists");
	mainPath = GetPath();
}

fs::directory_iterator FileManager::GetFiles() {
		return fs::directory_iterator(GetPath());
}

fs::directory_iterator FileManager::GetFiles(char* dir) {
	if (!fs::exists(dir)) 
		throw std::invalid_argument("Папки не существует!");
	return fs::directory_iterator(dir);
}

fs::directory_entry FileManager::GetFileBy(int id) {
	int i = 0;

	for (const auto& entry : fs::directory_iterator(GetPath())) {
		if (i > id) throw std::out_of_range("Индекс за пределами диапазона массива!");
		if (i == id) return entry;

		i++;
	}

	throw std::invalid_argument("Файл не найден!");
}

fs::directory_entry FileManager::GetFileBy(int id, char* dir) {
	if (!fs::exists(dir)) throw std::invalid_argument("Папки не существует!");;
	int i = 0;

	for (const auto& entry : fs::directory_iterator(dir)) {
		if (i > id) throw std::out_of_range("Индекс за пределами диапазона массива!");
		if (i == id) return entry;

		i++;
	}
}

fs::directory_entry FileManager::GetFileBy(char* file) {
		
	int i = 0;

	for (const auto& entry : fs::directory_iterator(GetPath())) {
		if (strcmp(entry.path().filename().string().c_str(), file) == 0 ) return entry;

		i++;
	}

	throw std::invalid_argument("Файл не найден!");
}

fs::directory_entry FileManager::GetFileBy(char* file, char* dir) {
	if (!fs::exists(dir)) throw std::invalid_argument("Папки не существует!");;
	int i = 0;

	for (const auto& entry : fs::directory_iterator(dir)) {
		if (strcmp(entry.path().filename().string().c_str(), file) == 0) return entry;

		i++;
	}

	throw std::invalid_argument("Файл не найден!");
}

int FileManager::GetFilesCount() {
		
	int count = 0;
	for (const auto& entry : fs::directory_iterator(GetPath())) count++;

	return count;
}

int FileManager::GetFilesCount(char* dir) {
	if (!fs::exists(dir)) throw std::invalid_argument("Папки не существует!");;
	int count = 0;
	for (const auto& entry : fs::directory_iterator(dir)) count++;

	return count;
}

void FileManager::SetMainPath() {
	fs::current_path(mainPath);
	currentDir = (char*)"Playlists";
}

void FileManager::SetDir(char* dir) {
	fs::current_path(dir);
	currentDir = dir;
}

char* FileManager::GetDir() { return currentDir; }

fs::path FileManager::GetPath() {
	return fs::current_path();
}

bool FileManager::CreateDir(char* dir) {
	std::error_code err;

	if (fs::exists(dir)) return false;
	if (!fs::create_directories(dir, err)) {
		if (fs::exists(dir)) return true;

		printf("CreateDirectoryRecuresive: FAILED to create [%s], err:%s\n", dir, err.message().c_str());
		return false;
	}

	return true;
}

bool FileManager::RemoveDir(char* dir)
{
	if (!fs::exists(dir)) return true;
	
	fs::remove(dir);
	return true;
}

bool FileManager::RenameDir(char* dir, char* newName)
{
	if (!fs::exists(dir) && fs::exists(newName)) return false;
	fs::rename(dir, newName);

	return true;
}

bool FileManager::InMainDir()
{
	//std::cout << std::endl << currentDir << std::endl << mainPath.filename().string().c_str();
	return strcmp(currentDir, mainPath.filename().string().c_str()) == 0;
}
