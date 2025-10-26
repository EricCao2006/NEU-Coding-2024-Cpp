#pragma once
#include "Film.h"

class DirectorCut : public Film {
private:
    int additionalTime;
    string changes;

public:
    DirectorCut(const string& t = "", const string& d = "", int tm = 0,
                int addTime = 0, const string& ch = "", const string& notes = "");

    void display() const override;
    void input(ifstream& fin) override;
    void output(ofstream& fout) const override;
    string getType() const override { return "DirectorCut"; }

    void setAdditionalTime(int time) { additionalTime = time; }
    void setChanges(const string& ch) { changes = ch; }

    int getAdditionalTime() const { return additionalTime; }
    string getChanges() const { return changes; }

};

// DirectorCut 实现
inline DirectorCut::DirectorCut(const string& t, const string& d, int tm,
                               int addTime, const string& ch, const string& notes)
    : Film(t, d, tm), additionalTime(addTime), changes(ch){}

inline void DirectorCut::display() const {
    Film::display();
    cout << "本影片为导演剪辑版，" << endl
         << "片长增加了" << additionalTime << " 分钟" << endl
         << "修改内容如下：" << endl
         << changes;
}

inline void DirectorCut::input(ifstream& fin) {
    Film::input(fin);

    string buffer;
    getline(fin, buffer);
    additionalTime = stoi(buffer);
    getline(fin, changes);
}

inline void DirectorCut::output(ofstream& fout) const {
    Film::output(fout);
    fout << additionalTime << endl;
    fout << changes << endl;
}