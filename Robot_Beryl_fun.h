/*
Naming rules
如果是函数，首字母不用大写；
如果是变量，首字母大写
*/
#pragma once
#include <CQEVE_ALL.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>

const char *onlyBeingAt(void);

//Use this function to get the QQID from a message
void getBanID(const std::string message, std::vector<long long>&banid);

void useCmdtoBan(CQ::EVEGroupMsg &eve, CQ::GroupMemberInfo MemberAInfo, CQ::GroupMemberInfo MemberBInfo, int64_t time);



//void throwError(static std::runtime_error err);
