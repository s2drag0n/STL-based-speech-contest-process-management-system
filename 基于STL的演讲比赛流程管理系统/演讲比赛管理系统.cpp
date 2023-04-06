#include <iostream>
#include "SpeechManager.h"
#include <ctime>
using namespace std;

int main() {

    srand((unsigned int)time(NULL));

    SpeechManager sm;

    //测试选手创建是否成功
    for (map<int, Speaker>::iterator it = sm.speakers.begin(); it != sm.speakers.end(); ++it) {
        cout << "编号：" << it->first
            <<"\t姓名：" << it->second.name
            << "\t分数：" << it->second.score << endl;
    }

    int choice = 0;

    while (true) {

        sm.showMeun();
        cout << "请输入你的选择：" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            //比赛开始
            sm.startSpeech();
            break;
        case 2:
            //往届记录
            sm.showRecord();
            break;
        case 3:
            //清空记录
            sm.clearRecord();
            break;
        case 0:
            //退出程序
            sm.exitSystem();
            break;
        default:
            system("cls");
            break;
        }
    }
    

    return 0;
}