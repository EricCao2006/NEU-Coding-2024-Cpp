// main.cpp
#include "CarbonRankList.h"

// 主菜单显示函数
void displayMenu() {
    cout << "\n=== 碳交易所榜单管理系统 ===" << endl;
    cout << "1. 管理公司" << endl;
    cout << "2. 查看榜单" << endl;
    cout << "3. 退出系统" << endl;
    cout << "请选择操作 (1-3): ";
}

// 管理公司子菜单
void displayManagementMenu() {
    cout << "\n=== 公司管理 ===" << endl;
    cout << "1. 增加公司" << endl;
    cout << "2. 删除公司" << endl;
    cout << "3. 修改公司信息" << endl;
    cout << "4. 返回主菜单" << endl;
    cout << "请选择 (1-4): ";
}

// 修改公司信息子菜单
void displayUpdateMenu() {
    cout << "\n=== 修改公司信息 ===" << endl;
    cout << "1. 修改碳排放量" << endl;
    cout << "2. 修改交易额" << endl;
    cout << "3. 返回管理菜单" << endl;
    cout << "请选择 (1-3): ";
}

// 查看榜单子菜单
void displayRankMenu() {
    cout << "\n=== 查看榜单 ===" << endl;
    cout << "1. 按碳排放量排名" << endl;
    cout << "2. 按交易额排名" << endl;
    cout << "3. 按公司名称排序" << endl;
    cout << "4. 返回主菜单" << endl;
    cout << "请选择 (1-4): ";
}

int main() {
    // 设置中文字符集
    system("chcp 65001");
    
    CarbonRankList rankList;
    int choice = 0;
    int managementChoice = 0;
    int updateChoice = 0;
    int rankChoice = 0;
    
    // 加载初始数据（如果文件存在）
    rankList.loadFromFile("carbon_data.txt");
    
    cout << "=== 碳交易所榜单管理系统 ===" << endl;
    cout << "系统已启动，数据已从文件加载（如果存在）" << endl;
    
    do {
        displayMenu();
        cin >> choice;
        
        // 清除输入缓冲区
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                // 管理公司
                do {
                    displayManagementMenu();
                    cin >> managementChoice;
                    
                    // 清除输入缓冲区
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch(managementChoice) {
                        case 1: {
                            // 增加公司
                            string name;
                            double emission, tradeVolume;
                            
                            cout << "\n=== 增加新公司 ===" << endl;
                            cout << "请输入公司名称: ";
                            getline(cin, name);
                            
                            cout << "请输入碳排放量(吨): ";
                            cin >> emission;
                            
                            cout << "请输入交易额(万元): ";
                            cin >> tradeVolume;
                            
                            // 清除输入缓冲区
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            if (rankList.addCompany(name, emission, tradeVolume)) {
                                cout << "公司 " << name << " 添加成功！" << endl;
                            } else {
                                cout << "添加失败！" << endl;
                            }
                            break;
                        }
                        
                        case 2: {
                            // 删除公司
                            string name;
                            
                            cout << "\n=== 删除公司 ===" << endl;
                            cout << "请输入要删除的公司名称: ";
                            getline(cin, name);
                            
                            if (rankList.removeCompany(name)) {
                                cout << "公司 " << name << " 删除成功！" << endl;
                            } else {
                                cout << "删除失败！" << endl;
                            }
                            break;
                        }
                        
                        case 3: {
                            // 修改公司信息
                            do {
                                displayUpdateMenu();
                                cin >> updateChoice;
                                
                                // 清除输入缓冲区
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                
                                switch(updateChoice) {
                                    case 1: {
                                        // 修改碳排放量
                                        string name;
                                        double newEmission;
                                        
                                        cout << "\n=== 修改碳排放量 ===" << endl;
                                        cout << "请输入公司名称: ";
                                        getline(cin, name);
                                        
                                        cout << "请输入新的碳排放量(吨): ";
                                        cin >> newEmission;
                                        
                                        // 清除输入缓冲区
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        
                                        if (rankList.updateEmission(name, newEmission)) {
                                            cout << "公司 " << name << " 碳排放量更新成功！" << endl;
                                        } else {
                                            cout << "更新失败！" << endl;
                                        }
                                        break;
                                    }
                                    
                                    case 2: {
                                        // 修改交易额
                                        string name;
                                        double newVolume;
                                        
                                        cout << "\n=== 修改交易额 ===" << endl;
                                        cout << "请输入公司名称: ";
                                        getline(cin, name);
                                        
                                        cout << "请输入新的交易额(万元): ";
                                        cin >> newVolume;
                                        
                                        // 清除输入缓冲区
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        
                                        if (rankList.updateTradeVolume(name, newVolume)) {
                                            cout << "公司 " << name << " 交易额更新成功！" << endl;
                                        } else {
                                            cout << "更新失败！" << endl;
                                        }
                                        break;
                                    }
                                    
                                    case 3:
                                        cout << "返回管理菜单..." << endl;
                                        break;
                                        
                                    default:
                                        cout << "无效选择，请重新输入！" << endl;
                                }
                            } while (updateChoice != 3);
                            break;
                        }
                        
                        case 4:
                            cout << "返回主菜单..." << endl;
                            break;
                            
                        default:
                            cout << "无效选择，请重新输入！" << endl;
                    }
                } while (managementChoice != 4);
                break;
            }
            
            case 2: {
                // 查看榜单
                do {
                    displayRankMenu();
                    cin >> rankChoice;
                    
                    // 清除输入缓冲区
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch(rankChoice) {
                        case 1:
                            rankList.printRankByEmission();
                            break;
                        case 2:
                            rankList.printRankByTradeVolume();
                            break;
                        case 3:
                            rankList.printRankByName();
                            break;
                        case 4:
                            cout << "返回主菜单..." << endl;
                            break;
                        default:
                            cout << "无效选择，请重新输入！" << endl;
                    }
                } while (rankChoice != 4);
                break;
            }
            
            case 3: {
                // 退出系统
                cout << "正在保存数据..." << endl;
                rankList.saveToFile("carbon_data.txt");
                cout << "数据已保存到 carbon_data.txt" << endl;
                cout << "感谢使用碳交易所榜单管理系统！" << endl;
                break;
            }
            
            default:
                cout << "无效选择，请重新输入！" << endl;
        }
        
    } while (choice != 3);
    
    return 0;
}