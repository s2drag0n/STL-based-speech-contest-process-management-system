#include <iostream>
#include "SpeechManager.h"
#include <ctime>
using namespace std;

int main() {

    srand((unsigned int)time(NULL));

    SpeechManager sm;

    //����ѡ�ִ����Ƿ�ɹ�
    for (map<int, Speaker>::iterator it = sm.speakers.begin(); it != sm.speakers.end(); ++it) {
        cout << "��ţ�" << it->first
            <<"\t������" << it->second.name
            << "\t������" << it->second.score << endl;
    }

    int choice = 0;

    while (true) {

        sm.showMeun();
        cout << "���������ѡ��" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            //������ʼ
            sm.startSpeech();
            break;
        case 2:
            //�����¼
            sm.showRecord();
            break;
        case 3:
            //��ռ�¼
            sm.clearRecord();
            break;
        case 0:
            //�˳�����
            sm.exitSystem();
            break;
        default:
            system("cls");
            break;
        }
    }
    

    return 0;
}