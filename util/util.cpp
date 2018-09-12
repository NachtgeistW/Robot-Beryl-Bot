#include "functionality.h"

int util::randNum(int n)
{
	static std::uniform_int_distribution<int> dist(0, n);	//�������0��n�����
	static std::random_device device;						//�����������
	static std::mt19937 gen(device());						//��mt�ṩ����
	return dist(gen);
}

//����Ҳû������Ϊʲô���޷�����ء���
/*
bool util::getBot(std::vector<int64_t> &bot)
{
	std::ifstream fstm(path + "robot.txt");
	try
	{
		if (!fstm.good())
			throw std::runtime_error("�ء����Һ���û��������������˺ŵļ����ˡ���");
		std::string temp;
		while (getline(fstm, temp))
			bot.push_back(_atoi64(temp.c_str()));
		fstm.close();
		return true;
	}
	catch (std::runtime_error err) {
		CQ::sendPrivateMsg(Master, err.what());
		return false;
	}
}
*/

bool util::checkBot(int64_t QQID, std::vector<int64_t>bot)
{
	for (auto begin = bot.begin(); begin != bot.end(); begin++)
		if (*begin == QQID)
			return true;
	return false;
}

std::string util::int64_ttos(int64_t num)
{
	std::string result;
	std::stringstream trans;
	trans << num;
	trans >> result;
	return result;
}