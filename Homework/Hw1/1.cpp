//将以“long”为单位的距离转换为以“码”为单位
//1 long == 220 yard
#include <iostream>
using namespace std;
int main(void)
{
    double long_distance;
    cout << "long: ";
    cin >> long_distance;
    cout << "Yard: " << long_distance * 220 << endl;
    return 0;
}