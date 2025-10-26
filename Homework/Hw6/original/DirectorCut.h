#pragma once
#include "Film.h"

class DirectorCut : public Film {
public:
    DirectorCut(){
        store_rev_time();
        store_changes();
    }
    void store_rev_time(int t = 0){rev_time = t;}
    void store_changes(const string& c){changes = c;}
    void store_changes(const char* c = ""){changes = c;}
    virtual void output();
    virtual void input(ifstream&);

private:
    int rev_time = 0; //剪辑时间
    string changes; //更改内容

};

inline void DirectorCut::input(ifstream& fin){
    Film::input(fin);
    string in_buffer;
    getline(fin,in_buffer);
    store_rev_time(stoi(in_buffer));
    getline(fin,in_buffer);
    store_changes(in_buffer);
}

inline void DirectorCut::output(){
    Film::output();
    cout << "Revised time: " << rev_time << "mins\n";
    cout << "Changes: " << changes << endl;
}