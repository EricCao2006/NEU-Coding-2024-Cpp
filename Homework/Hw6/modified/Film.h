#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Comment.h"

using namespace std;

class Film {
public:
    Film(const string& t = "", const string& d = "", int tm = 0);
    virtual ~Film() = default;

    virtual void display() const;
    virtual void input(ifstream& fin);
    virtual void output(ofstream& fout) const;
    virtual string getType() const { return "Film"; }

    // 评论管理
    void addComment(const Comment& comment);
    void removeComment(int index);
    void displayComments() const;
    double getAverageRating() const;
    int getCommentCount() const { return comments.size(); }
    vector<Comment> getComments() const { return comments; }

    // 基本信息
    void setTitle(const string& t) { title = t; }
    void setDirector(const string& d) { director = d; }
    void setTime(int t) { time = t; }

    string getTitle() const { return title; }
    string getDirector() const { return director; }
    int getTime() const { return time; }

protected:
    string title;
    string director;
    int time;
    vector<Comment> comments;
};

// Film 类的实现
inline Film::Film(const string& t, const string& d, int tm)
    : title(t), director(d), time(tm) {}

inline void Film::display() const {
    cout << "类型: " << getType() << endl;
    cout << "标题: " << title << endl;
    cout << "导演: " << director << endl;
    cout << "片长: " << time << " 分钟" << endl;
    cout << "评论数量: " << comments.size() << endl;
    if (!comments.empty())
        cout << "平均评分: " << getAverageRating() << "/5" << endl;
    cout << "评论数量: " << comments.size() << " 条评论" << endl;
}

inline void Film::addComment(const Comment& comment) {
    comments.push_back(comment);
}

inline void Film::removeComment(int index) {
    if (index >= 0 && index < comments.size()) {
        comments.erase(comments.begin() + index);
    }
}

inline void Film::displayComments() const {
    if (comments.empty()) {
        cout << "暂无评论" << endl;
        return;
    }

    for (size_t i = 0; i < comments.size(); i++) {
        cout << "评论 " << i + 1 << ":" << endl;
        comments[i].display();
    }
}

inline double Film::getAverageRating() const {
    if (comments.empty()) return 0.0;

    double sum = 0.0;
    for (const auto& comment : comments) {
        sum += comment.rating;
    }
    return sum / comments.size();
}

inline void Film::input(ifstream& fin) {
    getline(fin, title);
    getline(fin, director);

    string buffer;
    getline(fin, buffer);
    time = stoi(buffer);
}

inline void Film::output(ofstream& fout) const {
    fout << getType() << endl;
    fout << title << endl;
    fout << director << endl;
    fout << time << endl;
}