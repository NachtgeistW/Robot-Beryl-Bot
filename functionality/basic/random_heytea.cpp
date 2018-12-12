#include "random_heytea.h"
#include <algorithm>
bool Heytea::LoadTeaList(const string path)
{
	string line, kind;
	std::vector<string> temp;
	std::ifstream input(path);
	if (!input.good())
	{
		CQ::sendPrivateMsg(util::Master, "我连喜茶的菜单都找不到……");
		return false;
	}
	try {
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
	}
	catch (std::exception exc)
	{
		std::string to_be_send = "那个……你确定你给我的喜茶菜单没错吗？你看看这里：\n";
		to_be_send += exc.what();
		CQ::sendPrivateMsg(util::Master, to_be_send);
		return false;
	}
	return true;
}

void Heytea::ShowHelpInfo(int64_t qq, string msg)
{
	std::regex reg("(help )(喜茶|heytea)");
	if (std::regex_match(msg, reg) == true)
		CQ::sendPrivateMsg(qq, help_info_);
}

void Heytea::ShowTeaType(int64_t qq, string msg)
{
	std::regex reg("(help )(喜茶种类)");
	if (std::regex_match(msg, reg) == true)
	{
		string reply;
		for (auto it : tea_type_)
			reply = reply + it + '\n';
		CQ::sendPrivateMsg(qq, string("你好！现有喜茶的种类如下：\n" + reply).c_str());
	}
}

string Heytea::GetTea(void)
{
	int type = util::RandInt_uniform(0, tea_list_.size() - 1);
	int tea = util::RandInt_uniform(0, tea_list_[tea_type_[type]].size() - 1);
	return string(tea_type_[type] + "分类下的" + tea_list_[tea_type_[type]][tea]);
}

string Heytea::GetTea(string str)
{
	int tea = util::RandInt_uniform(0, tea_list_[str].size() - 1);
	return string(tea_list_[str][tea]);
}

void Heytea::ShowTea(int64_t group, int64_t qq, string msg)
{
	string reply;
	std::regex reg("(\\[CQ:at,qq=)(" + std::to_string(util::Beryl) + ")(\\])(.*)(抽)(.*)");
	std::smatch match;
	if (msg.find("抽签") == msg.npos && std::regex_match(msg, match, reg) == true)
	{
		if (match[6] == "喜茶")
			reply = "[CQ:at,qq=" + std::to_string(qq) + "] 嘛，来试试"
			+ GetTea() + "呗？";
		else if (std::find(tea_type_.begin(), tea_type_.end(), match[6]) != tea_type_.end())
			reply = "[CQ:at,qq=" + std::to_string(qq) + "] 嘛，来试试"
			+ GetTea(match[6]) + "呗？";
		CQ::sendGroupMsg(group, reply);
	}
}

void Heytea::ShowTea(int64_t qq, string msg)
{
	string reply;
	std::regex reg("(抽)(.*)");
	std::smatch match;
	if (msg.find("抽签") == msg.npos && std::regex_match(msg, match, reg) == true)
	{
		if (match[2] == "喜茶")
			reply = "嘛，来试试" + GetTea() + "呗？";
		else if (std::find(tea_type_.begin(), tea_type_.end(), match[2]) != tea_type_.end())
			reply = "嘛，来试试" + GetTea(match[2]) + "呗？";
	}
	CQ::sendPrivateMsg(qq, reply);
}
