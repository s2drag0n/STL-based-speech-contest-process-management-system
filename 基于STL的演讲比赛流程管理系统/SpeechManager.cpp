#include "SpeechManager.h"

//���캯��
SpeechManager::SpeechManager() {
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();
}
//��������
SpeechManager::~SpeechManager() {

}
//չʾ�˵�
void SpeechManager::showMeun() {
    cout << "****************************************************" << endl;
    cout << "******************** ��ӭ�μ��ݽ����� *****************" << endl;
    cout << "******************** 1.��ʼ�ݽ����� ******************" << endl;
    cout << "******************** 2.�鿴�����¼ ******************" << endl;
    cout << "******************** 3.��ձ�����¼ ******************" << endl;
    cout << "******************** 0.�˳��������� ******************" << endl;
    cout << endl;
}
//�˳�ϵͳ
void SpeechManager::exitSystem() {
    cout << "^^^^^^^��ӭ�´�ʹ�ã�^^^^^^^" << endl;
    system("pause");
    exit(0);
}
//��ʼ����������
void SpeechManager::initSpeech() {
    this->v1.clear();
    this->v2.clear();
    this->vWinner.clear();
    this->speakers.clear();
    this->index = 1;
    this->record.clear();
}
//����ѡ��
void SpeechManager::creatSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < 12; ++i) {
        string name = "ѡ��";
        name += nameSeed[i];

        Speaker sp;
        sp.name = name;
        sp.score[0] = 0.f;
        sp.score[1] = 0.f;

        this->v1.push_back(10001 + i);

        this->speakers.insert(make_pair(10001 + i, sp));
    }
}
//��ʼ����
void SpeechManager::startSpeech() {
    //��һ�ֱ���
    //1.��ǩ
    this->speechBallot();
    //2.����
    this->speechContest();
    //3.��ʾ�������
    this->showScore();
    //�ڶ��ֱ���
    ++(this->index);
    //1.��ǩ
    this->speechBallot();
    //2.����
    this->speechContest();
    //3.��ʾ�������
    this->showScore();
    //4.�������
    this->saveRecord();

    //���ñ���
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();

    cout << "-------------------------����������-------------------------" << endl;
    system("pause");
    system("cls");
}
//��ǩ
void SpeechManager::speechBallot() {
    cout << "---------------------------------------------------------" << endl;
    cout << "��" << this->index << "�ֱ�����ǩ������£�" << endl;

    if (this->index == 1) {
        random_shuffle(v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
            cout << *it << "\t";
        }
        cout << endl;
    }

    if (this->index == 2) {
        random_shuffle(v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
            cout << *it << "\t";
        }
        cout << endl;
    }
    cout << "---------------------------------------------------------" << endl;
    system("pause");
    cout << endl;
}
//����
void SpeechManager::speechContest() {
    cout << "-----------��" << this->index << "�ֱ�����ʽ��ʼ-----------------------------" << endl;

    //׼����ʱ���������С��ɼ�
    multimap<double, int, greater<double>> groupScore;

    //ͳ��ѡ������
    int num = 0;

    //����ѡ������
    vector<int> vSrc;
    if (this->index == 1) {
        vSrc = v1;
    } else if (this->index == 2) {
        vSrc = v2;
    }

    //��������ѡ�ֽ��б���
    for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); ++it) {
        
        num++;
        //��ί���
        deque<double> d;
        for (int i = 0; i < 10; ++i) {
            double score = (rand() % 401 + 600) / 10.f;
            d.push_back(score);
            //cout << score << "\t";
        }

        //ȥ����߷ֺ���ͷ�
        sort(d.begin(), d.end(), greater<double>());
        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0);
        double avg = sum / d.size();


        //��ƽ���ַ���map
        this->speakers[*it].score[this->index - 1] = avg;

        groupScore.insert(make_pair(avg, *it));

        //ÿ����ȡ��ǰ����
        if (num % 6 == 0) {
            cout << "��" << num / 6 << "������ɼ�Ϊ��" << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
                it != groupScore.end(); ++it) {
                cout << "��ţ�" << it->second
                    << "\t����" << speakers[it->second].name
                    << "\t�ɼ�" << speakers[it->second].score[this->index - 1]
                    << endl;
            }
            //ȡ��ǰ����
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
                it != groupScore.end() && count++ < 3; ++it) {
                if (this->index == 1) {
                    v2.push_back(it->second);
                    //cout << "���˽�������" << endl;
                } else if (this->index == 2) {
                    vWinner.push_back(it->second);
                }
            }

            groupScore.clear();
            cout << endl;
        }
    }
    cout << "-----------��" << this->index << "�ֱ������-------------------------------" << endl;
    system("pause");
}

//��ʾ������Ա����
void SpeechManager::showScore() {
    cout << "---------------------------------------------------------" << endl;
    cout << "��" << this->index << "�ֱ�������ѡ��Ϊ��" << endl;

    vector<int> vSrc;
    if (this->index == 1) {
        vSrc = v2;
    } else if (this->index == 2) {
        vSrc = vWinner;
    }

    for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); ++it) {
        cout << "��ţ�" << *it
            << "\t����" << speakers[*it].name
            << "\t�ɼ�" << speakers[*it].score[this->index - 1]
            << endl;
    }
    cout << "---------------------------------------------------------" << endl;
    cout << endl;

    system("pause");
    system("cls");
    this->showMeun();
}

//�����¼
void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); ++it) {
        ofs << *it << "," << speakers[*it].score[1] << ",";
    }
    ofs << endl;
    
    ofs.close();

    cout << "-------------------------�ļ���¼�Ѿ����棡-----------------------" << endl;
    this->fileIsEmpty = false;
}

//��ȡ�ļ�
void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv", ios::in);

    //�ļ�������
    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
        //cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    //�ļ�Ϊ�� 
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        //cout << "�ļ�Ϊ��" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;
    ifs.putback(ch);//�������ȡ���ַ��Ż���
    
    string data;
    int index = 0;
    while (ifs >> data) {
        //cout << data << endl;
        
        ++index;
        vector<string> v;
        int pos = -1;//����λ��
        int start = 0;

        while (true) {
            
            pos = data.find(",", start);

            if (pos == -1) {
                //û���ҵ��������
                break;
            }

            string temp = data.substr(start, pos - start);
            //cout << temp << endl;
            v.push_back(temp);
            start = pos + 1;
        }
        this->record.insert(make_pair(index, v));

    }
    ifs.close();
}

//��ӡ��¼
void SpeechManager::showRecord() {
    if (this->fileIsEmpty) {
        cout << "�ļ������ڻ���Ϊ��" << endl;
    } else {
        for (int i = 1; i <= this->record.size(); i++) {
            cout << "��" << i << "��"
                << "�ھ����=" << this->record[i][0] << "\t�÷�=" << this->record[i][1]
                << "\t�Ǿ����=" << this->record[i][2] << "\t�÷�=" << this->record[i][3]
                << "\t�������=" << this->record[i][4] << "\t�÷�=" << this->record[i][5]
                << endl;
        }
    }
    system("pause");
    system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord() {
    ofstream ofs("speech.csv", ios::trunc);
    ofs.close();
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();
    cout << "��ճɹ�" << endl;
    system("pause");
    system("cls");
}