// CarbonRankList.h
#ifndef CARBONRANKLIST_H
#define CARBONRANKLIST_H

#include "SortedSeq.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

struct Company {
    string name;
    double emission;      // 碳排放量（吨）
    double tradeVolume;   // 交易额（万元）
    
    Company(const string& n = "", double e = 0.0, double t = 0.0) 
        : name(n), emission(e), tradeVolume(t) {}
};

class CarbonRankList : public SortedSeq {
public:
    bool addCompany(const string& name, double emission, double tradeVolume) {
        // 检查是否已存在
        if (findCompanyIndex(name) != -1) {
            cout << "公司 " << name << " 已存在！" << endl;
            return false;
        }
        
        Company comp(name, emission, tradeVolume);
        companies.push_back(comp);
        
        // 格式：名称|排放量|交易额
        string entry = name + "|" + to_string(emission) + "|" + to_string(tradeVolume);
        return addSS(entry); // 使用基类排序插入
    }

    bool updateEmission(const string& name, double newEmission) {
        int index = findCompanyIndex(name);
        if (index == -1) {
            cout << "公司 " << name << " 不存在！" << endl;
            return false;
        }
        companies[index].emission = newEmission;
        
        // 更新基类中的字符串数据 - 重新添加所有公司
        // 先清空基类数据
        for (int i = last; i >= 0; i--) {
            del(i);
        }
        
        // 重新添加所有公司
        for (const auto& company : companies) {
            string entry = company.name + "|" + to_string(company.emission) + "|" + to_string(company.tradeVolume);
            addSS(entry);
        }
        
        return true;
    }

    bool updateTradeVolume(const string& name, double newVolume) {
        int index = findCompanyIndex(name);
        if (index == -1) {
            cout << "公司 " << name << " 不存在！" << endl;
            return false;
        }
        companies[index].tradeVolume = newVolume;
        
        // 更新基类中的字符串数据 - 重新添加所有公司
        // 先清空基类数据
        for (int i = last; i >= 0; i--) {
            del(i);
        }
        
        // 重新添加所有公司
        for (const auto& company : companies) {
            string entry = company.name + "|" + to_string(company.emission) + "|" + to_string(company.tradeVolume);
            addSS(entry);
        }
        
        return true;
    }

    bool removeCompany(const string& name) {
        int index = findCompanyIndex(name);
        if (index == -1) {
            cout << "公司 " << name << " 不存在！" << endl;
            return false;
        }
        
        // 从vector中删除
        companies.erase(companies.begin() + index);
        
        // 从基类中删除 - 重新添加所有公司
        // 先清空基类数据
        for (int i = last; i >= 0; i--) {
            del(i);
        }
        
        // 重新添加所有公司
        for (const auto& company : companies) {
            string entry = company.name + "|" + to_string(company.emission) + "|" + to_string(company.tradeVolume);
            addSS(entry);
        }
        
        return true;
    }

    void printRankByEmission() {
        vector<Company> sorted = companies;
        std::sort(sorted.begin(), sorted.end(), [](const Company& a, const Company& b) {
            return a.emission < b.emission; // 排放量从小到大
        });
        
        cout << "=== 碳排放量排名（从低到高）===" << endl;
        for (size_t i = 0; i < sorted.size(); ++i) {
            cout << i + 1 << ". " << sorted[i].name 
                 << " | 排放量: " << fixed << setprecision(2) << sorted[i].emission << " 吨" << endl;
        }
    }

    void printRankByTradeVolume() {
        vector<Company> sorted = companies;
        std::sort(sorted.begin(), sorted.end(), [](const Company& a, const Company& b) {
            return a.tradeVolume > b.tradeVolume; // 交易额从高到低
        });
        
        cout << "=== 交易额排名（从高到低）===" << endl;
        for (size_t i = 0; i < sorted.size(); ++i) {
            cout << i + 1 << ". " << sorted[i].name 
                 << " | 交易额: " << fixed << setprecision(2) << sorted[i].tradeVolume << " 万元" << endl;
        }
    }

    void printRankByName() {
        vector<Company> sorted = companies;
        std::sort(sorted.begin(), sorted.end(), [](const Company& a, const Company& b) {
            return a.name < b.name; // 公司名按字母顺序排序
        });
        
        cout << "=== 按公司名称排序 ===" << endl;
        for (size_t i = 0; i < sorted.size(); ++i) {
            cout << i + 1 << ". " << sorted[i].name 
                 << " | 排放量: " << fixed << setprecision(2) << sorted[i].emission << " 吨"
                 << " | 交易额: " << fixed << setprecision(2) << sorted[i].tradeVolume << " 万元" << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "无法打开文件: " << filename << endl;
            return;
        }
        
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            
            if (pos1 != string::npos && pos2 != string::npos) {
                string name = line.substr(0, pos1);
                double emission = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
                double tradeVolume = stod(line.substr(pos2 + 1));
                
                addCompany(name, emission, tradeVolume);
            }
        }
        inFile.close();
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "无法创建文件: " << filename << endl;
            return;
        }
        
        for (const auto& company : companies) {
            outFile << company.name << "|" << company.emission << "|" << company.tradeVolume << endl;
        }
        outFile.close();
    }

private:
    vector<Company> companies;
    
    int findCompanyIndex(const string& name) const {
        for (size_t i = 0; i < companies.size(); ++i) {
            if (companies[i].name == name) {
                return i;
            }
        }
        return -1;
    }

    void sortByEmission() {
        std::sort(companies.begin(), companies.end(), [](const Company& a, const Company& b) {
            return a.emission < b.emission;
        });
    }

    void sortByTradeVolume() {
        std::sort(companies.begin(), companies.end(), [](const Company& a, const Company& b) {
            return a.tradeVolume > b.tradeVolume;
        });
    }

    void sortByName() {
        std::sort(companies.begin(), companies.end(), [](const Company& a, const Company& b) {
            return a.name < b.name;
        });
    }
};

#endif