#pragma once
#include "Film.h"

class ForeignFilm : public Film {
private:
    string language;
    string country;

public:
    ForeignFilm(const string& t = "", const string& d = "", int tm = 0,
                const string& lang = "", const string& cntry = "");

    void display() const override;
    void input(ifstream& fin) override;
    void output(ofstream& fout) const override;
    string getType() const override { return "ForeignFilm"; }

    void setLanguage(const string& lang) { language = lang; }
    void setCountry(const string& cntry) { country = cntry; }

    string getLanguage() const { return language; }
    string getCountry() const { return country; }
};

// ForeignFilm 实现
inline ForeignFilm::ForeignFilm(const string& t, const string& d, int tm,
                               const string& lang, const string& cntry)
    : Film(t, d, tm), language(lang), country(cntry) {}

inline void ForeignFilm::display() const {
    Film::display();
    cout << "此影片来自 " << country << " \n";
}

inline void ForeignFilm::input(ifstream& fin) {
    Film::input(fin);
    getline(fin, language);
    getline(fin, country);
}

inline void ForeignFilm::output(ofstream& fout) const {
    Film::output(fout);
    fout << language << endl;
    fout << country << endl;
}