#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>
#include <CQEVE_ALL.h>

#include <string>
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("SendMsg");

EVE_PrivateMsg_EX(SendMsg) {
	logger.Debug() << DEBUGINFO << eve.message;

	// ���һ�����¼��йص���Ϣ����
	// �����Ϣ�����Ѿ��Զ������¼���Ӧ��Ⱥ���ߺ���
	auto msg = eve.sendMsg();
	// ���������ض����˷�����Ϣ,�������123456
	// ������ֱ�ӵ���API
	//sendPrivateMsg(123456, "���");
	// ����ʹ��MsgSend
	//MsgSend P123456(123456, msgtype::����);
	//P123456 << "���" << send;

	auto message = eve.message;

	// ��ͨ�ķ���һ����Ϣ
	if (!message.compare("CQ:msg1"))
		eve.sendMsg("�յ���Ϣ��!");

	// ʹ��<<��������Ϣ
	if (!message.compare("CQ:msg2"))
		//һ��Ҫĩβ����<<send�Żᷢ�ͳ�ȥ
		msg << "�յ���Ϣ��!" << send;

	// ǿ�����Ϣ���ͷ�ʽ
	if (!message.compare("CQ:msg3"))
		// ���������ɶ���������
		msg
		<< "������Ϊ:" << eve.fromQQ
		<< ",��ϢΪ:" << eve.message
		<< send;

	if (!message.compare("CQ:image")) {
		logger.Debug() << "rawģʽ:" << msg.isRAW() << send;
		// ����һ��ͼƬ
		msg << code::image("123.png") << send;
	}

	if (!message.compare("CQ:face"))
		//����һ������
		msg << code::face(face::����) << send;

	if (!message.compare("CQ:raw"))
		msg
		// RAW ��ʾ�������Ϣ����ԭ������
		// �����ǽ�����CQ��,���������й���,���緢��ͼƬ
		<< CODE << code::at(eve.fromQQ)
		// CODE ��ʾ�������Ϣ��������ΪCQ��
		// Ĭ�Ͻ���
		<< RAW << code::face(face::����)
		<< send;

	if (!message.compare("CQ:effect"))
		// ����һ��ħ������,��CQ����뵥��һ����Ϣ
		eve.sendMsg(code::effect("art", 2003, "ħ����Ϣ"));
}