#include <CQEVE.h>
#include <CQMsgCode.h>
#include <CQAPI_EX.h>

#include <string>
#include<thread>

using namespace std;
using namespace CQ;

//��������Ҫ��ȷ����ĺ�������
//����Ҫ��дһ����è���
//�ﵽ���¼���:

//�û�����[����+����]������Ӧ����
//����[ιʳ]�Գ���ιʳ,
//�����м�������
//���ͺ������

//д��������Ŀ���������õ�ʹ��

//����Ҫ���������ļ���ͷ�ļ�
#include<INItool.h>
//Ȼ�����ö�Ӧ�����ֿռ�
using namespace ini;

//����һ��ȫ������.
INItool pz;
int ��־;
thread*saveThread;
EVE_Enable(load) {
	//����Ӧ���ڲ�����ص�ʱ�������
	pz = INItool(string(getAppDirectory()) + "data.ini");
	//Ȼ������ÿ5���ӱ���һ��
	saveThread = new thread([] {
		while () {//�����ȷ��Ű�
			Sleep(5 * 60 * 1000);
			pz.save();
		}
	});
	saveThread->detach();

	return 0;
}
EVE_Disable(save) {
	//Ȼ�����رյ�ʱ���ٱ���һ��.����ͣ���߳�
	pz.save();
}