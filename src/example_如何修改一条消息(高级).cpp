#include <CQEVE_PrivateMsg.h>
#include <CQLogger.h>

#include <string>
using namespace std;
using namespace CQ;

//
//����ʵ��,�˹����޷�ʵ��
//
//
//
//

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("ChangMsg");

static bool Chang = false;
EVE_PrivateMsg_EX(ChangMsg) {
	if (!eve.message.compare("CQ:ChangMsg")) {
		eve.messageRAW[0] = 'Q';
		Chang = true;
	}
}
EVE_PrivateMsg_EX(ChangMsg2) {
	static Logger logger("ChangMsg");
	if (Chang) {
		logger.Info(eve.message);
		Chang = false;
	}
}