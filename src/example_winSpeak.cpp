#include <CQEVE_GroupMsg.h>
#include <CQcode.h>

#include <string>

using namespace std;
using namespace CQ;

EVE_GroupMsg_EX(Speak) {
	static string msgs("Speak:");

	if (eve.message.compare(0, msgs.size(), msgs)) return;

	auto txt = eve.message.substr(msgs.size());

	//eve.sendMsg() << code::record("out.wav", txt) << send;
	//record �ĵ�һ������ָʾ���������ɵ��ĸ��ļ�(����ڿ�Q������Ŀ¼)
	//record �ĵڶ�������ָʾ��ָ��������������
	//����һЩ����������,�������а汾��window��֧�ִ���Ŀ
}