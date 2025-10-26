#pragma once
#include "Film.h"

class ForeignFilm : public Film {
public:
    ForeignFilm(){store_language();}
    void store_language(const string& l){language = l;}
    void store_language(const char* l = ""){language = l;}
    virtual void output();
    virtual void input(ifstream&);

private:
    string language;
};

inline void ForeignFilm::input(ifstream& fin){
    Film::input(fin);
    string in_buffer;
    getline(fin, in_buffer);
    store_language(in_buffer);
}
inline void ForeignFilm::output(){
    Film::output();
    cout << "Language: " << language << endl;
}