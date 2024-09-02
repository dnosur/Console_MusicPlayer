#pragma once
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class FileManager {
private:
	fs::path mainPath;
	char* currentDir;

public:
	FileManager();

	fs::directory_iterator GetFiles();

	fs::directory_iterator GetFiles(char* dir);

	fs::directory_entry GetFileBy(int id);

	fs::directory_entry GetFileBy(int id, char* dir);

	fs::directory_entry GetFileBy(char* file);

	fs::directory_entry GetFileBy(char* file, char* dir);

	int GetFilesCount();

	int GetFilesCount(char* dir);

	void SetMainPath();

	void SetDir(char* dir);

	char* GetDir();

	fs::path GetPath();

	bool CreateDir(char* dir);
	bool RemoveDir(char* dir);
	bool RenameDir(char* dir, char* newName);

	bool InMainDir();
};