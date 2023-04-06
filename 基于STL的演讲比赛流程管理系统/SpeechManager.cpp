#include "SpeechManager.h"

//构造函数
SpeechManager::SpeechManager() {
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();
}
//析构函数
SpeechManager::~SpeechManager() {

}
//展示菜单
void SpeechManager::showMeun() {
    cout << "****************************************************" << endl;
    cout << "******************** 欢迎参加演讲比赛 *****************" << endl;
    cout << "******************** 1.开始演讲比赛 ******************" << endl;
    cout << "******************** 2.查看往届记录 ******************" << endl;
    cout << "******************** 3.清空比赛记录 ******************" << endl;
    cout << "******************** 0.退出比赛程序 ******************" << endl;
    cout << endl;
}
//退出系统
void SpeechManager::exitSystem() {
    cout << "^^^^^^^欢迎下次使用！^^^^^^^" << endl;
    system("pause");
    exit(0);
}
//初始化比赛函数
void SpeechManager::initSpeech() {
    this->v1.clear();
    this->v2.clear();
    this->vWinner.clear();
    this->speakers.clear();
    this->index = 1;
    this->record.clear();
}
//创建选手
void SpeechManager::creatSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < 12; ++i) {
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.name = name;
        sp.score[0] = 0.f;
        sp.score[1] = 0.f;

        this->v1.push_back(10001 + i);

        this->speakers.insert(make_pair(10001 + i, sp));
    }
}
//开始比赛
void SpeechManager::startSpeech() {
    //第一轮比赛
    //1.抽签
    this->speechBallot();
    //2.比赛
    this->speechContest();
    //3.显示晋级结果
    this->showScore();
    //第二轮比赛
    ++(this->index);
    //1.抽签
    this->speechBallot();
    //2.比赛
    this->speechContest();
    //3.显示比赛结果
    this->showScore();
    //4.保存分数
    this->saveRecord();

    //重置比赛
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();

    cout << "-------------------------本届比赛完毕-------------------------" << endl;
    system("pause");
    system("cls");
}
//抽签
void SpeechManager::speechBallot() {
    cout << "---------------------------------------------------------" << endl;
    cout << "第" << this->index << "轮比赛抽签结果如下：" << endl;

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
//比赛
void SpeechManager::speechContest() {
    cout << "-----------第" << this->index << "轮比赛正式开始-----------------------------" << endl;

    //准备临时容器，存放小组成绩
    multimap<double, int, greater<double>> groupScore;

    //统计选手人数
    int num = 0;

    //比赛选手容器
    vector<int> vSrc;
    if (this->index == 1) {
        vSrc = v1;
    } else if (this->index == 2) {
        vSrc = v2;
    }

    //遍历所有选手进行比赛
    for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); ++it) {
        
        num++;
        //评委打分
        deque<double> d;
        for (int i = 0; i < 10; ++i) {
            double score = (rand() % 401 + 600) / 10.f;
            d.push_back(score);
            //cout << score << "\t";
        }

        //去除最高分和最低分
        sort(d.begin(), d.end(), greater<double>());
        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0);
        double avg = sum / d.size();


        //将平均分放入map
        this->speakers[*it].score[this->index - 1] = avg;

        groupScore.insert(make_pair(avg, *it));

        //每六人取出前三名
        if (num % 6 == 0) {
            cout << "第" << num / 6 << "组比赛成绩为：" << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
                it != groupScore.end(); ++it) {
                cout << "编号：" << it->second
                    << "\t姓名" << speakers[it->second].name
                    << "\t成绩" << speakers[it->second].score[this->index - 1]
                    << endl;
            }
            //取走前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
                it != groupScore.end() && count++ < 3; ++it) {
                if (this->index == 1) {
                    v2.push_back(it->second);
                    //cout << "有人晋级啦！" << endl;
                } else if (this->index == 2) {
                    vWinner.push_back(it->second);
                }
            }

            groupScore.clear();
            cout << endl;
        }
    }
    cout << "-----------第" << this->index << "轮比赛完毕-------------------------------" << endl;
    system("pause");
}

//显示晋级成员分数
void SpeechManager::showScore() {
    cout << "---------------------------------------------------------" << endl;
    cout << "第" << this->index << "轮比赛晋级选手为：" << endl;

    vector<int> vSrc;
    if (this->index == 1) {
        vSrc = v2;
    } else if (this->index == 2) {
        vSrc = vWinner;
    }

    for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); ++it) {
        cout << "编号：" << *it
            << "\t姓名" << speakers[*it].name
            << "\t成绩" << speakers[*it].score[this->index - 1]
            << endl;
    }
    cout << "---------------------------------------------------------" << endl;
    cout << endl;

    system("pause");
    system("cls");
    this->showMeun();
}

//保存记录
void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); ++it) {
        ofs << *it << "," << speakers[*it].score[1] << ",";
    }
    ofs << endl;
    
    ofs.close();

    cout << "-------------------------文件记录已经保存！-----------------------" << endl;
    this->fileIsEmpty = false;
}

//读取文件
void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv", ios::in);

    //文件不存在
    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
        //cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    //文件为空 
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        //cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;
    ifs.putback(ch);//将上面读取的字符放回来
    
    string data;
    int index = 0;
    while (ifs >> data) {
        //cout << data << endl;
        
        ++index;
        vector<string> v;
        int pos = -1;//逗号位置
        int start = 0;

        while (true) {
            
            pos = data.find(",", start);

            if (pos == -1) {
                //没有找到逗号情况
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

//打印记录
void SpeechManager::showRecord() {
    if (this->fileIsEmpty) {
        cout << "文件不存在或者为空" << endl;
    } else {
        for (int i = 1; i <= this->record.size(); i++) {
            cout << "第" << i << "届"
                << "冠军编号=" << this->record[i][0] << "\t得分=" << this->record[i][1]
                << "\t亚军编号=" << this->record[i][2] << "\t得分=" << this->record[i][3]
                << "\t季军编号=" << this->record[i][4] << "\t得分=" << this->record[i][5]
                << endl;
        }
    }
    system("pause");
    system("cls");
}

//清空记录
void SpeechManager::clearRecord() {
    ofstream ofs("speech.csv", ios::trunc);
    ofs.close();
    this->initSpeech();
    this->creatSpeaker();
    this->loadRecord();
    cout << "清空成功" << endl;
    system("pause");
    system("cls");
}