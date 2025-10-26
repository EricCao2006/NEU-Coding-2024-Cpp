#pragma once
#include "DirectorCut.h"
#include "ForeignFilm.h"
#include <string>
#include <fstream>
#include <iostream>
using std::string;
using std::ifstream;
using std::cout, std::endl, std::getline;

class Film {
public:
    Film() {
        store_title();
        store_director();
        store_time();
        store_quality();
    }
    void store_title(const string& t){title = t;}
    void store_title(const char* t = ""){title = t;}
    void store_director(const string& d){director = d;}
    void store_director(const char* d = ""){director = d;}
    void store_time(int t = 0){time = t;}
    void store_quality(int q = 0){quality = q;}
    virtual void output();
    virtual void input(ifstream& );
    static bool read_input(const char*, Film*[], int);

private:
    string title;
    string director;
    int time = 0; //以分钟为单位
    int quality = 4; //0(极差)~4(极好)
};

/**
 * @brief 输入文件
 * @param fin 输入缓存区
 */
inline void Film::input(ifstream& fin) {
    string in_buffer; //输入缓存
    getline(fin, in_buffer);
    store_title(in_buffer);
    getline(fin,in_buffer);
    store_director(in_buffer);
    getline(fin,in_buffer);
    //这里先用c_str()转换成char*，再使用atoi()转换成int
    store_time(stoi(in_buffer));
    getline(fin,in_buffer);
    store_quality(stoi(in_buffer));
}

inline void Film::output() {
    cout << "Title: " << title << endl;
    cout << "Director: " << director << endl;
    cout << "Time: " << time << "mins" << endl;
    cout << "Quality: ";
    for (int i = 0; i < quality; i++)
        cout << '*';
    cout << endl;
}

inline bool Film::read_input(const char* file, Film* films[], int n) {
    string in_buffer;
    ifstream fin(file);
    if (!fin) //文件打开失败
        return false;
    int next = 0;
    while (next < n && getline(fin, in_buffer)) {
        if (in_buffer == "Film")
            films[next] = new Film;
        else if (in_buffer == "ForeignFilm")
            films[next] = new ForeignFilm;
        else if (in_buffer == "DirectorCut")
            films[next] = new DirectorCut;
        else //不支持的电影类型
            continue;\
        films[next++]->input(fin);
    }
    fin.close();
    return true;
}
