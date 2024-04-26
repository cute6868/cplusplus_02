#pragma once
#include"speaker.h"
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include<ctime>


// �ݽ�����������
class SpeechManager
{
public:
	// ��Ա����:
	// ��� ��һ�ֱ���ѡ�ֱ�� ������
	std::vector<int> v1;

	// ��� ��һ�ֽ���ѡ�ֱ�� ������
	std::vector<int> v2;

	// ��� ʤ��ǰ����ѡ�ֱ�� ������
	std::vector<int> v3;

	// ��� ��źͶ�Ӧ����ѡ�� ������
	std::map<int, Speaker> m1;

	// ��� ����������
	int round;

	// ��־�ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	// ��������¼������
	std::map<int, std::vector<std::string>> record;

	// ���캯��-����
	SpeechManager();

	// ��������-����
	~SpeechManager();

	// ��ʾ�˵�-���� {����}
	void Show_Menu();

	// �˳�ϵͳ-���� {����}
	void ExitSystem();

	// ��ʼ������������-����
	void initSpeech();

	// ����12��ѡ��-����
	void createSpeaker();

	// ��ǩ-����
	void speechDraw();

	// ����-����
	void speechContest();

	// ��ʾ��������-����
	void showScore();

	// �����¼-����
	void saveRecord();

	// ������ʼ��-����
	void init();

	// ��ʼ����-����
	void StartSpeech();

	// ���ؼ�¼-����
	void loadRecord();

	// �鿴��¼-���� {����}
	void ShowRecord();

	// ��ռ�¼-���� {����}
	void ClearRecord();
};