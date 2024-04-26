#include "speechManager.h"
using namespace std;

// ���캯��-ʵ��
SpeechManager::SpeechManager()
{
	// ��ʼ������Ҫ�õĶ���
	init();
}


// ��������-ʵ��
SpeechManager::~SpeechManager()
{

}


// ��ʾ�˵�-ʵ�� {����}
void SpeechManager::Show_Menu()
{
	cout << "********************************" << endl;
	cout << "*****   ��ӭ�μ��ݽ�����   *****" << endl;
	cout << "******  1. ��ʼ�ݽ�����  *******" << endl;
	cout << "******  2. �鿴�����¼  *******" << endl;
	cout << "******  3. ��ձ�����¼  *******" << endl;
	cout << "******  0. �˳���������  *******" << endl;
	cout << endl;
}


// �˳�ϵͳ-ʵ�� {����}
void SpeechManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


// ��ʼ������������-ʵ��
void SpeechManager::initSpeech()
{
	// �������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m1.clear();
	this->record.clear();

	// ��ʼ������������
	this->round = 1;
}


// ����12��ѡ��-ʵ��
void SpeechManager::createSpeaker()
{
	// 12��ѡ�֣��ֱ�� ѡ��A��ѡ��b��ѡ��c......
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		// ƴ�ӳ�ѡ�ֵ�����
		string name = "ѡ��";
		name += nameSeed[i];

		// ʵ����һ��ѡ��
		Speaker s;

		// ��ʼ��ѡ�ֵ�����
		s.m_Name = name;

		// ��ʼ��ѡ�����ֵķ���
		for (int i = 0; i < 2; i++)
		{
			s.m_Score[i] = 0;
		}

		// ����ѡ�ֶ���һ����ţ������ñ�ŷŵ� v1 ������
		int id = i + FirstSpeakerID;
		this->v1.push_back(id);

		// ��ѡ���Լ��������ı�ţ�һ���ŵ� map �����У� ����this->m1 ��
		this->m1.insert(make_pair(id, s));
	}
}


// ��ǩ-ʵ��
void SpeechManager::speechDraw()
{
	cout << endl << endl;
	cout << "�� << " << this->round << " >> �ֱ���ѡ�����ڳ�ǩ" << endl << endl;
	cout << "----------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;


	if (this->round == 1)
	{
		// ��һ�ֱ���������v1������
		// ������Һ����������
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator iterator = v1.begin(); iterator != v1.end(); iterator++)
		{
			cout << *iterator << " ";
		}
		cout << endl;
	}
	else
	{
		// �ڶ��ֱ���������v2������
		random_shuffle(v2.begin(), v2.end());
		// ������Һ����������
		for (vector<int>::iterator iterator = v2.begin(); iterator != v2.end(); iterator++)
		{
			cout << *iterator << " ";
		}
		cout << endl;
	}

	cout << "----------------------------------------------" << endl << endl;
	system("pause");
	cout << endl;
}


// ����-ʵ��
void SpeechManager::speechContest()
{
	cout << "------------��" << this->round << "�ֱ�����ʽ��ʼ------------" << endl << endl;

	// ��ʱ��С�����������������ѡ�ֱ��
	multimap<double, int, greater<double>> groupScore;

	// ��¼��ǰ�ǵڼ���ѡ��
	int num = 0;

	// װ��������Ա����
	vector<int> v;
	if (this->round == 1) { v = v1; }
	else { v = v2; }

	// �������в���ѡ��
	for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++)
	{
		// ��¼��ǰ�ǵڼ���ѡ��
		num++;

		// ��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;		// 600 ~ 1000
			d.push_back(score);
		}

		// ����ƽ����
		sort(d.begin(), d.end(), greater<double>());	// ��������
		d.pop_front();	// ȥ����߷�
		d.pop_back();	// ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0f);	// �ܷ�
		double avg = sum / (double)d.size();	// ƽ����

		// ��ƽ���ִ浽map������
		this->m1[*iterator].m_Score[this->round - 1] = avg;

		// ��������� ���뵽��ʱС��������
		groupScore.insert(make_pair(avg, *iterator));

		// ÿ6����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������:" << endl << endl;

			// ���С��������ѡ�ֵĵ÷���Ϣ
			for (multimap<double, int, greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end(); iterator++)
			{
				cout << "��ţ�" << iterator->second << " ������" << this->m1[iterator->second].m_Name
					<< " �÷֣�" << this->m1[iterator->second].m_Score[this->round - 1] << endl;
			}
			cout << endl;

			// ȡ��ÿ��С����ǰ������ѡ��
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end() && count < 3; iterator++)
			{
				if (this->round == 1)
				{
					v2.push_back(iterator->second);
				}
				else
				{
					v3.push_back(iterator->second);
				}
				count++;
			}

			// ����������Ѿ��������Ϣ��С��ѡ��
			groupScore.clear();
		}
	}

	cout << "------------��" << this->round << "�ֱ�������------------" << endl << endl;
	system("pause");
	cout << endl;
}


// ��ʾ��������-ʵ��
void SpeechManager::showScore()
{
	cout << "-----------��" << this->round << "�ֽ���ѡ����Ϣ-----------" << endl << endl;
	vector<int> v;
	if (this->round == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++)
	{
		cout << "ѡ�ֱ�ţ�" << *iterator << " ������" << this->m1[*iterator].m_Name
			<< " �÷֣�" << this->m1[*iterator].m_Score[this->round - 1] << endl;
	}
	cout << endl;
	system("pause");
	cout << endl;
}


// �����¼-ʵ��
void SpeechManager::saveRecord()
{
	ofstream file;
	file.open("speech.csv", ios::out | ios::app);	// ������ķ�ʽ���ļ�

	// ��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator iterator = v3.begin(); iterator != v3.end(); iterator++)
	{
		file << *iterator << "," << this->m1[*iterator].m_Score[1] << ",";
	}
	file << endl;

	// �ر��ļ�
	file.close();

	cout << "\n��¼���Զ�����" << endl << endl;
}


// ������ʼ��-ʵ��
void SpeechManager::init()
{
	// ��ʼ������������
	initSpeech();

	// ����12��ѡ��
	createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();
}


// ��ʼ����-ʵ�� {����}
void SpeechManager::StartSpeech()
{	
	// ��һ�ֱ���
	// 1.��ǩ
	speechDraw();

	// 2.����
	speechContest();

	// 3.��ʾ���
	showScore();

	// �ڶ��ֱ���
	this->round++;

	// 1.��ǩ
	speechDraw();

	// 2.����
	speechContest();

	// 3.��ʾ���
	showScore();

	// 4.�������
	saveRecord();

	// ���ã�ʵ�����ݵĸ���
	init();
}


// ���ؼ�¼-ʵ��
void SpeechManager::loadRecord()
{
	ifstream file("speech.csv", ios::in);
	
	// �ļ������ڵ����
	if (!file.is_open())
	{
		this->fileIsEmpty = true;
		file.close();
		return;
	}

	// �ļ�����Ϊ�յ����
	char ch;
	file >> ch;
	if (file.eof())		// EOF: End Of File
	{
		this->fileIsEmpty = true;
		file.close();
		return;
	}

	// �ļ���Ϊ��
	this->fileIsEmpty = false;

	file.putback(ch);	// �������ȡ�ĵ����ַ� �Ż���
	string data;
	int index = 0;		// ������־�ǵڼ���

	while (file >> data)
	{
		//cout << data << endl;		// ���������10002,86.675,10009,81.3,10007,78.55,

		vector<string> v;	// ���6��string�ַ���
		
		int pos = -1;	// ���ŵ�λ��
		int start = 0;	// ���ҵ���ʼλ��

		while (true)
		{
			// ���Ҷ��ţ�������Ҳ���Ĭ�Ϸ���-1��������ҵõ����������Ӧ��λ��
			pos = data.find(",", start);

			// û���ҵ����ŵ����
			if (pos == -1)
			{
				break;
			}

			// �ҵ����ŵ��������ȡ�Ӵ�
			string temp = data.substr(start, pos - start);

			// �ŵ�ר�Ŵ����һ�����ݵ�������
			v.push_back(temp);

			// ���¿�ʼ��λ��
			start = pos + 1;
		}

		// ���������з��룬װ������һ�����ݵ�С����
		this->record.insert(make_pair(index, v));

		// ������һ�������
		index++;
	}
	file.close();
}


// �鿴��¼-ʵ�� {����}
void SpeechManager::ShowRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
		return;
	}

	// ��ȡÿһ��Ĺھ����Ǿ�����������
	for (int i = 0; i < this->record.size(); i++)
	{
		cout << "��" << i + 1 << "��\t"
			<< "  | �ھ���ţ�" << this->record[i][0] << "  �÷֣�" << this->record[i][1]
			<< "  | �Ǿ���ţ�" << this->record[i][0] << "  �÷֣�" << this->record[i][1]
			<< "  | ������ţ�" << this->record[i][0] << "  �÷֣�" << this->record[i][1] << endl;
	}
}


// ��ռ�¼-���� {����}
void SpeechManager::ClearRecord()
{
	int select;
	cout << endl;
	cout << "ȷ����գ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ȡ��" << endl;
	cout << ">>> ";
	cin >> select;

	if (select == 1)
	{
		// ��ģʽ ios::trunc ~~~ ����ļ����ڣ���ɾ���ļ������´���
		ofstream file("speech.csv", ios::trunc);
		file.close();

		// ˢ�����ݣ���ʼ������
		init();

		// �����ʾ��Ϣ
		cout << "����ɹ���" << endl;
	}
}
