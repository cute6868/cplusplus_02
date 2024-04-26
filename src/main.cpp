#include "speechManager.h"
using namespace std;


int main()
{
	// ������������
	srand((unsigned int)time(NULL));

	// ����һ��������󣬹��������ݽ�����������
	SpeechManager sm;

	//// ����12��ѡ�ֵĴ���
	//for (map<int, Speaker>::iterator it = sm.m1.begin(); it != sm.m1.end(); it++)
	//{
	//	cout << "��ţ�" << it->first << "������" << it->second.m_Name << "������" << it->second.m_Score[0] << endl;
	//}

	// �洢�û���ѡ��
	int choice = 0;

	while (true)
	{
		// ��ʾ�˵�
		sm.Show_Menu();

		// ��ȡ�û�ѡ��
		cout << "����������ѡ��";
		cin >> choice;

		// �����û���ѡ��ִ�ж�Ӧ�Ĺ���
		switch (choice)
		{
		case 1:	// ��ʼ����
			sm.StartSpeech();
			break;
		case 2:	// �鿴��¼
			sm.ShowRecord();
			break;
		case 3:	// ��ռ�¼
			sm.ClearRecord();
			break;
		case 0:	// �˳�ϵͳ
			sm.ExitSystem();
			break;
		default:
			break;
		}

		system("pause");	// ��ͣ���û��鿴ִ����Ϣ
		system("cls");		// ִ����������
	}

	return 0;
}