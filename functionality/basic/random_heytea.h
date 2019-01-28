#pragma once
#include "../../util/util.h"
class Heytea 
{
	std::map<string, std::vector<string>> tea_list_;
	std::vector<string> tea_type_;
	string GetTea(void);
	string GetTea(const string str);
	string help_info_ =
		"你好，来一杯喜茶吗？机绿现在可以抽喜茶所有的饮品了！\n"
		"指令是“@机绿 抽喜茶”。如果你想抽一个特定的种类（比如说芝士茗茶），那么指令是“@机绿 抽芝士茗茶”。\n"
		"具体有什么种类请私聊发送指令“help 喜茶种类”查看。当然，私聊也是可以抽的，只要把艾特去掉就好。\n"
		"注意噢，机绿是以江门地区+北京新中关DP店+广州中华广场店的饮品为基准的。如果有遗漏的饮品，请用反馈功能告诉开发者。\n"
		"说了这么多，不来一杯吗？";
public:
	Heytea() = default;
	~Heytea() = default;
	bool LoadTeaList(const string path);
	void ShowHelpInfo(int64_t qq, string msg);
	void ShowTeaType(int64_t qq, string msg);
	void ShowTea(const int64_t group, const int64_t qq, const string msg);
	void ShowTea(int64_t qq, string msg);
};
