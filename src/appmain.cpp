#include <CQEVE.h>
#include <CQLogger.h>

#include "APPINFO.h"

#include <string>
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("��Q����Ӧ��");

EVE_Enable(Enable)
{
	logger.Info("Ӧ�ñ�����");
	return 0;
}

EVE_Disable(Disable)
{
	logger.Info("Ӧ�ñ�ͣ��");
	return 0;
}

MUST_AppInfo_RETURN(CQAPPID)