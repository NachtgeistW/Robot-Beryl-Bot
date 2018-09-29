#include "../../util/functionality.h"

void UBSongInfo::initialize(int64_t qq)
{
	try	{
		if (!load_song_list(util::path + "song list.txt"))
			throw std::runtime_error("我找不到Jubeat曲目列表的文件路径了……");
	}
	catch (std::runtime_error file_does_not_find){
		CQ::sendPrivateMsg(qq, file_does_not_find.what());
	}

}

bool UBSongInfo::load_local_memo(const string name, int64_t group)
{
	std::string Title, CurLine, FolLine, ToBePush;
	std::vector<string> tempmemo;

	std::regex digit(std::string("\\d+"));
	std::smatch line_num;
	std::ifstream input(util::path + name);
	if (!input.good())
		return false;

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
	if (!Memo.insert(std::make_pair(Title, tempmemo)).second)
		return false;
	return true;
}

bool UBSongInfo::load_song_list(const string path)
{
	string line, temp_name;
	unsigned int level;
	std::ifstream input(path);
	if (!input.good())
		return false;
	while (std::getline(input, line))
	{
		std::istringstream record(line);
		record >> temp_name;
		while (record >> level)
			SongList.insert(std::make_pair(temp_name, level));
	}
	SongList.insert(std::make_pair(temp_name, level));
	input.close();
	return true;
}

bool UBSongInfo::search_song_list(const string name)
{
	for (auto begin = SongList.begin(); begin != SongList.end(); begin++)
		if ((*begin).first == name)
			return true;
	return false;
}

bool UBSongInfo::load_alias_list(const string path)
{
	std::regex reg(string("(.*+)"));
	string line, temp_name;
	std::ifstream input(path);
	if (!input.good())
		return false;
	while (std::getline(input, line))
	{
		std::istringstream record(line);
		record >> temp_name;
		while (record >> level)
			SongList.insert(std::make_pair(temp_name, level));
	}
	SongList.insert(std::make_pair(temp_name, level));
	input.close();
	return true;
}

bool UBSongInfo::search_alias_list(string name)
{
	for (auto begin = AliasList.begin(); begin != AliasList.end(); begin++)
		if ((*begin).first == name)
		{
			name = (*begin).second;
			return true;
		}
	return false;

}
