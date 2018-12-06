#include "random_heytea.h"
#include <algorithm>
bool Heytea::LoadTeaList(const string path)
{
	string line, kind;
	std::vector<string> temp;
	std::ifstream input(path);
	if (!input.good())
		return false;
	while (std::getline(input, line))
	{
		if (line.find("#") != line.npos)
		{
			line.erase(line.begin());
			kind = line;
			tea_type_.push_back(kind);
		}
		else if (line == "-")
		{
			tea_list_.insert(std::make_pair(kind, temp));
			temp.clear();
		}
		else
			temp.push_back(line);
	}
	return true;
}

void Heytea::ShowHelpInfo(int64_t qq, string msg)
{
	std::regex reg("(help )(Ï²²è|heytea)");
	if (std::regex_match(msg, reg) == true)
		CQ::sendPrivateMsg(qq, help_info_);
}

void Heytea::ShowTeaType(int64_t qq, string msg)
{
	std::regex reg("(help )(Ï²²èÖÖÀà)");
	if (std::regex_match(msg, reg) == true)
	{
		string reply;
		for (auto it : tea_type_)
			reply = reply + it + '\n';
		CQ::sendPrivateMsg(qq, string("ÄãºÃ£¡ÏÖÓĞÏ²²èµÄÖÖÀàÈçÏÂ£º\n" + reply).c_str());
	}
}

string Heytea::GetTea(void)
{
	int type = util::RandInt_uniform(0, tea_list_.size() - 1);
	int tea = util::RandInt_uniform(0, tea_list_[tea_type_[type]].size() - 1);
	return string(tea_type_[type] + "·ÖÀàÏÂµÄ" + tea_list_[tea_type_[type]][tea]);
}

string Heytea::GetTea(string str)
{
	int tea = util::RandInt_uniform(0, tea_list_[str].size() - 1);
	return string(tea_list_[str][tea]);
}

void Heytea::ShowTea(int64_t group, int64_t qq, string msg)
{
	string reply;
	std::regex reg("(\\[CQ:at,qq=)(" + std::to_string(util::Beryl) + ")(\\])(.*)(³é)(.*)");
	std::smatch match;
	if (msg.find("³éÇ©") == msg.npos && std::regex_match(msg, match, reg) == true)
	{
		if (match[6] == "Ï²²è")
			reply = "[CQ:at,qq=" + std::to_string(qq) + "] Âï£¬À´ÊÔÊÔ"
			+ GetTea() + "ßÂ£¿";
		else if (std::find(tea_type_.begin(), tea_type_.end(), match[6]) != tea_type_.end())
			reply = "[CQ:at,qq=" + std::to_string(qq) + "] Âï£¬À´ÊÔÊÔ"
			+ GetTea(match[6]) + "ßÂ£¿";
		CQ::sendGroupMsg(group, reply);
	}
}

void Heytea::ShowTea(int64_t qq, string msg)
{
	string reply;
	std::regex reg("(³é)(.*)");
	std::smatch match;
	if (msg.find("³éÇ©") == msg.npos && std::regex_match(msg, match, reg) == true)
	{
		if (match[2] == "Ï²²è")
			reply = "Âï£¬À´ÊÔÊÔ" + GetTea() + "ßÂ£¿";
		else if (std::find(tea_type_.begin(), tea_type_.end(), match[2]) != tea_type_.end())
			reply = "Âï£¬À´ÊÔÊÔ" + GetTea(match[2]) + "ßÂ£¿";
	}
	CQ::sendPrivateMsg(qq, reply);
}
