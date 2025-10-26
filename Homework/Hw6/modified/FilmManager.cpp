#include "Film.h"
#include "ForeignFilm.h"
#include "DirectorCut.h"
#include "Comment.h"
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class FilmManager {
private:
    vector<unique_ptr<Film>> films;

public:
    // 显示所有电影
    void display_films() const {
        if (films.empty()) {
            cout << "暂无电影信息！" << endl;
            return;
        }
        
        cout << "=== 电影列表 ===" << endl;
        for (size_t i = 0; i < films.size(); i++) {
            cout << "\n[" << i + 1 << "] ";
            films[i]->display();
            cout << endl;
            cout << endl;
        }
    }
    
    // 添加电影
    void add_film() {
        cout << "选择电影类型:" << endl;
        cout << "1. 普通电影" << endl;
        cout << "2. 外语电影" << endl;
        cout << "3. 导演剪辑版" << endl;

        int choice;
        cin >> choice;
        cin.ignore(); // 清除换行符

        string title, director;
        int time;

        cout << "请输入电影标题: ";
        getline(cin, title);
        cout << "请输入导演: ";
        getline(cin, director);
        cout << "请输入片长(分钟): ";
        cin >> time;
        cin.ignore();

        switch (choice) {
            case 1: {
                films.push_back(make_unique<Film>(title, director, time));
                break;
            }
            case 2: {
                string language, country;
                cout << "请输入原始语言: ";
                getline(cin, language);
                cout << "请输入国家: ";
                getline(cin, country);
                films.push_back(make_unique<ForeignFilm>(title, director, time, language, country));
                break;
            }
            case 3: {
                int addTime;
                string changes, notes;
                cout << "请输入增加的片长(分钟): ";
                cin >> addTime;
                cin.ignore();
                cout << "请输入修改内容: ";
                getline(cin, changes);
                cout << "请输入导演说明: ";
                getline(cin, notes);
                films.push_back(make_unique<DirectorCut>(title, director, time, addTime, changes, notes));
                break;
            }
            default:
                cout << "无效选择！" << endl;
                return;
        }

        cout << "电影添加成功！" << endl;
    }
    
    // 修改电影
    void modify_film() {
        display_films();
        if (films.empty()) return;
        
        cout << "请选择要修改的电影编号: ";
        int index;
        cin >> index;
        cin.ignore();
        
        if (index < 1 || index > films.size()) {
            cout << "无效编号！" << endl;
            return;
        }
        
        Film* film = films[index - 1].get();
        
        string title, director;
        int time;
        
        cout << "请输入新标题(当前: " << film->getTitle() << "): ";
        getline(cin, title);
        cout << "请输入新导演(当前: " << film->getDirector() << "): ";
        getline(cin, director);
        cout << "请输入新片长(当前: " << film->getTime() << "): ";
        cin >> time;
        cin.ignore();
        
        film->setTitle(title);
        film->setDirector(director);
        film->setTime(time);
        
        // 特殊类型电影的额外修改
        if (auto foreignFilm = dynamic_cast<ForeignFilm*>(film)) {
            string language, country;
            cout << "请输入新语言(当前: " << foreignFilm->getLanguage() << "): ";
            getline(cin, language);
            cout << "请输入新国家(当前: " << foreignFilm->getCountry() << "): ";
            getline(cin, country);
            foreignFilm->setLanguage(language);
            foreignFilm->setCountry(country);
        }
        else if (auto directorCut = dynamic_cast<DirectorCut*>(film)) {
            int addTime;
            string changes, notes;
            cout << "请输入新增加片长(当前: " << directorCut->getAdditionalTime() << "): ";
            cin >> addTime;
            cin.ignore();
            cout << "请输入新修改内容(当前: " << directorCut->getChanges() << "): ";
            getline(cin, changes);
            getline(cin, notes);
            directorCut->setAdditionalTime(addTime);
            directorCut->setChanges(changes);
        }
        
        cout << "电影修改成功！" << endl;
    }
    
    // 删除电影
    void delete_film(const string& name) {
        auto it = find_if(films.begin(), films.end(),
            [&](const unique_ptr<Film>& film) {
                return film->getTitle() == name;
            });
        
        if (it != films.end()) {
            films.erase(it);
            cout << "电影 '" << name << "' 删除成功！" << endl;
        } else {
            cout << "未找到电影 '" << name << "'！" << endl;
        }
    }
    
    // 显示评论
    void display_comments(const string& film_name) {
        auto it = find_if(films.begin(), films.end(),
            [&](const unique_ptr<Film>& film) {
                return film->getTitle() == film_name;
            });
        
        if (it != films.end()) {
            cout << "=== 电影 '" << film_name << "' 的评论 ===" << endl;
            (*it)->displayComments();
        } else {
            cout << "未找到电影 '" << film_name << "'！" << endl;
        }
    }
    
    // 删除评论
    void delete_comment(const string& film_name, int com_num) {
        auto it = find_if(films.begin(), films.end(),
            [&](const unique_ptr<Film>& film) {
                return film->getTitle() == film_name;
            });
        
        if (it != films.end()) {
            if (com_num >= 1 && com_num <= (*it)->getCommentCount()) {
                (*it)->removeComment(com_num - 1);
                cout << "评论删除成功！" << endl;
            } else {
                cout << "无效的评论编号！" << endl;
            }
        } else {
            cout << "未找到电影 '" << film_name << "'！" << endl;
        }
    }
    
    // 添加评论
    void add_comment(const string& film_name) {
        auto it = find_if(films.begin(), films.end(),
            [&](const unique_ptr<Film>& film) {
                return film->getTitle() == film_name;
            });
        
        if (it != films.end()) {
            string reviewer, content, date;
            int rating;
            
            cout << "请输入评论者姓名: ";
            getline(cin, reviewer);
            cout << "请输入评分(1-5): ";
            cin >> rating;
            cin.ignore();
            cout << "请输入评论内容: ";
            getline(cin, content);
            cout << "请输入日期(YYYY-MM-DD): ";
            getline(cin, date);
            
            Comment comment(reviewer, rating, content, date);
            (*it)->addComment(comment);
            cout << "评论添加成功！" << endl;
        } else {
            cout << "未找到电影 '" << film_name << "'！" << endl;
        }
    }
    
    // 统计信息
    void display_stats() const {
        if (films.empty()) {
            cout << "暂无电影信息！" << endl;
            return;
        }
        
        cout << "=== 统计信息 ===" << endl;
        cout << "电影总数: " << films.size() << endl;
        
        int totalComments = 0;
        double totalRating = 0.0;
        int ratedFilms = 0;
        
        for (const auto& film : films) {
            totalComments += film->getCommentCount();
            if (film->getCommentCount() > 0) {
                totalRating += film->getAverageRating();
                ratedFilms++;
            }
        }
        
        cout << "评论总数: " << totalComments << endl;
        if (ratedFilms > 0) {
            cout << "平均评分: " << totalRating / ratedFilms << "/5" << endl;
        }
    }
};

// 主函数
int main() {
    system("chcp 65001");
    FilmManager manager;
    int choice;
    
    do {
        cout << "\n=== 电影评论管理系统 ===" << endl;
        cout << "1. 显示所有电影" << endl;
        cout << "2. 添加电影" << endl;
        cout << "3. 修改电影" << endl;
        cout << "4. 删除电影" << endl;
        cout << "5. 显示电影评论" << endl;
        cout << "6. 添加评论" << endl;
        cout << "7. 删除评论" << endl;
        cout << "8. 统计信息" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                manager.display_films();
                break;
            case 2:
                manager.add_film();
                break;
            case 3:
                manager.modify_film();
                break;
            case 4: {
                string name;
                cout << "请输入要删除的电影名称: ";
                getline(cin, name);
                manager.delete_film(name);
                break;
            }
            case 5: {
                string name;
                cout << "请输入电影名称: ";
                getline(cin, name);
                manager.display_comments(name);
                break;
            }
            case 6: {
                string name;
                cout << "请输入电影名称: ";
                getline(cin, name);
                manager.add_comment(name);
                break;
            }
            case 7: {
                string name;
                int comNum;
                cout << "请输入电影名称: ";
                getline(cin, name);
                cout << "请输入评论编号: ";
                cin >> comNum;
                cin.ignore();
                manager.delete_comment(name, comNum);
                break;
            }
            case 8:
                manager.display_stats();
                break;
            case 0:
                cout << "感谢使用！" << endl;
                break;
            default:
                cout << "无效选择！" << endl;
        }
    } while (choice != 0);
    
    return 0;
}