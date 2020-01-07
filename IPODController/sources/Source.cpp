
    // includes
#include "MP3FileInfo.h"
#include <stdio.h>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace fs = std::experimental::filesystem;

int isEmpty(char* str)
{
	return (str == NULL || strlen(str) == 0);
}
std::ofstream& operator << (std::ofstream& in, const MP3FileInfo& mp3Info)
{
	if (mp3Info.bHasV1Tag || mp3Info.bHasV2Tag)
	{
		//heading("ID3V1 Tag (and up)");
		if (!isEmpty(mp3Info.szArtist))
			in << std::left << std::setw(20) << "Artist :" << mp3Info.szArtist << std::endl;
		 
		if (!isEmpty(mp3Info.szTitle))
		{
			in << std::left << std::setw(20) << "Title :" << mp3Info.szTitle << std::endl;
		}


		if (!isEmpty(mp3Info.szAlbum))
			in << std::left << std::setw(20) << "Album :" << mp3Info.szAlbum << std::endl;

		if(mp3Info.nYear > 0)
		in << std::left << std::setw(20) << "Year :" << mp3Info.nYear << std::endl;

		if (!isEmpty(mp3Info.szGenre) )
			in << std::left << std::setw(20) << "Genre :" << mp3Info.szGenre << std::endl;
	}

	if (mp3Info.bHasV2Tag)
	{
		if (!isEmpty(mp3Info.szComposer))
			in << std::left << std::setw(20) << "Composer :" << mp3Info.szComposer << std::endl;

		if (!isEmpty(mp3Info.szOriginalArtist))
			in << std::left << std::setw(20) << "Original Artist :" << mp3Info.szOriginalArtist << std::endl;
	}
	return in;
}

int main(int argc, char** argv)
{
	SetConsoleTitle("MP3FileInfo.exe");
	if (argc < 3)
	{
		printf("Not enough parameters.\n\n");
		printf("USAGE: MP3FileInfo.exe {parent Directory of mp3 files} {outputFile}\n\n");
		printf("Press any key to continue\n");
		system("pause");
		return 1;
	}
	
	std::ofstream fs;
	fs.open(argv[2]);
	auto count = 0;
	for (auto& dir : fs::recursive_directory_iterator(argv[1]))
	{
		std::cout << " processing : " << dir << std::endl;
		if (! fs::is_directory(dir.path()))
		{
			MP3FileInfo mp3fi;
			std::wstring str(dir.path().c_str());
			std::string child(str.begin(),str.end());
			//bool canprocess = dir.path().extension() == ".mp3" || dir.path().extension() == ".mp4";
			if (/*canprocess && */mp3fi.Init(child.c_str()))
			{
				fs << child.c_str() << std::endl;
				fs << mp3fi;
				count++;
			}
			else
			{
				std::cout << " Not Redable Format Skipping: " << child.c_str() << std::endl;
			}
		}
	}
	char buff[100];
	snprintf(buff, sizeof(buff), "\n  Number of proceessed files: %d\n", count);
	fs << buff;
	std::cout << buff;
	fs.close();
	system("pause");
    return 0;
}

