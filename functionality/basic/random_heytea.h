#pragma once
#include "../../util/util.h"
class Heytea 
{
	std::map<string, std::vector<string>> tea_list_;
	std::vector<string> tea_type_;
	string GetTea(void);
	string GetTea(string str);
	string help_info_ =
		"��ã���һ��ϲ���𣿻������ڿ��Գ�ϲ�����е���Ʒ�ˣ�\n"
		"ָ���ǡ�@���� ��ϲ�衱����������һ���ض������ࣨ����˵֥ʿ���裩����ôָ���ǡ�@���� ��֥ʿ���衱��\n"
		"������ʲô������˽�ķ���ָ�help ϲ�����ࡱ�鿴����Ȼ��˽��Ҳ�ǿ��Գ�ģ�ֻҪ�Ѱ���ȥ���ͺá�\n"
		"ע���ޣ��������Խ��ŵ������е���ƷΪ��׼�ġ�����н���û�е���Ʒ�����÷������ܸ��߿����ߡ�\n"
		"˵����ô�࣬����һ����";
public:
	Heytea() = default;
	~Heytea() = default;
	bool LoadTeaList(const string path);
	void ShowHelpInfo(int64_t qq, string msg);
	void ShowTeaType(int64_t qq, string msg);
	void ShowTea(int64_t group, int64_t qq, string msg);
	void ShowTea(int64_t qq, string msg);
};
