#include <CQEVE_GroupMsg.h>
#include <CQEVE_PrivateMsg.h>
#include <CQMsgSend.h>
#include <CQAPI_EX.h>
#include <INItool.h>

#include <string>
using namespace std;
using namespace CQ;

int  Thesaurus(�ı��� msg, MsgSend send) {
	return 0;
}

EVE_Enable(ThesaurusE) {
	auto file = string(getAppDirectory()) + "Thesaurus.ini";
	return 0;
}

EVE_PrivateMsg(ThesaurusP) {
	return Thesaurus(msg, MsgSend(fromQQ, msgtype::����));
}
EVE_GroupMsg(ThesaurusG) {
	return Thesaurus(msg, MsgSend(fromGroup, msgtype::Ⱥ));
}