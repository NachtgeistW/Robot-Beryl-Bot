#include "store_memo.h"

bool SongInfo::read_chart(string path)
{
	std::string Title, CurLine, FolLine, ToBePush;
	std::vector<string> tempmemo;

	std::regex digit(std::string("\\d+"));
	std::smatch line_num;
	std::ifstream input(path);
	//read the song info
	for (int i = 1; i < 10; i++)
	{
		std::getline(input, CurLine);
		ToBePush = ToBePush + CurLine + '\n';
		if (i == 1)
			Title = CurLine;
	}
	tempmemo.push_back(ToBePush);
	ToBePush = "";

	//read the note info
	while (std::getline(input, CurLine))
	{
		//if it read the BPM
		if (CurLine.find("BPM") != CurLine.npos)
		{
			std::getline(input, FolLine);
			// if it is the beginning
			if (std::regex_match(FolLine, line_num, digit) && line_num.str() == "1")
				ToBePush = CurLine + '\n' + FolLine + '\n';
			else if (std::regex_match(FolLine, line_num, digit) && line_num.str() != "1")
			{
				tempmemo.push_back(ToBePush);
				ToBePush = CurLine + '\n' + FolLine + '\n';
			}
			//if the following line doesn't have bar num
			else if (!std::regex_match(FolLine, line_num, digit))
				ToBePush = ToBePush + '\n' + CurLine + '\n' + FolLine + '\n';
		}
		//if it read the bar num
		else if (std::regex_match(CurLine, line_num, digit))
		{
			//if it isn't the first bar
			if (line_num.str() != "1")
				tempmemo.push_back(ToBePush);
			ToBePush = CurLine + '\n';
		}
		//common
		else
			ToBePush = ToBePush + CurLine + '\n';
	}
	//for the last bar
	tempmemo.push_back(ToBePush);

	input.close();
	if(!Memo.insert(std::make_pair(Title, tempmemo)).second)
		return false;
	return true;
}
