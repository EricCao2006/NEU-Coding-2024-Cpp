#include <iostream>
#include <string>
#include <limits>

using namespace std;

//捐款者信息
struct Donor {
    string name;
    double amount;
};

int main() {
    int numDonors;
    cout << "请输入捐献者数目: ";
    cin >> numDonors;
    //清除输入缓冲区
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Donor* donors = new Donor[numDonors];    
    for (int i = 0; i < numDonors; i++) {
        cout << "请输入第 " << i + 1 << " 位捐献者的姓名: ";
        getline(cin, donors[i].name);
        cout << "请输入第 " << i + 1 << " 位捐献者的捐款数额: ";
        cin >> donors[i].amount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    //重要捐款人（捐款超过10000）
    cout << "\nGrand Patrons:" << endl;
    bool hasGrandPatrons = false;
    for (int i = 0; i < numDonors; i++) {
        if (donors[i].amount > 10000) {
            cout << donors[i].name << ": ￥" << donors[i].amount << endl;
            hasGrandPatrons = true;
        }
    }
    if (!hasGrandPatrons) {cout << "none" << endl;}
    //其他捐款人
    cout << "\nPatrons:" << endl;
    bool hasPatrons = false;
    for (int i = 0; i < numDonors; i++) {
        if (donors[i].amount <= 10000) {
            cout << donors[i].name << ": ￥" << donors[i].amount << endl;
            hasPatrons = true;
        }
    }
    if (!hasPatrons) {cout << "none" << endl;}
    delete[] donors;//释放内存
    return 0;
}