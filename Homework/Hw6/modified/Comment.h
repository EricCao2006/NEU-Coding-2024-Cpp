#pragma once
#include <string>
#include <iostream>

using namespace std;

struct Comment {
    string reviewer;
    int rating; // 1-5分
    string content;
    string date;
    
    Comment(const string& rvr = "", int rt = 0, 
            const string& cnt = "", const string& dt = "")
        : reviewer(rvr), rating(rt), content(cnt), date(dt) {}
    
    void display() const {
        cout << "评论者: " << reviewer << " | 评分: " << rating << "/5" << endl;
        cout << "日期: " << date << endl;
        cout << "内容: " << content << endl;
        cout << "----------------------------------------" << endl;
    }
};