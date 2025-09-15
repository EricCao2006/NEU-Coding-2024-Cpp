//光年转为天文单位
//1光年=63240天文单位
#include <iostream>
using namespace std;
double lyr2au(double light_year);
int main()
{
    double lyr;
    cout << "Enter the number of light years: ";
    cin >> lyr;
    cout << lyr << " light years = " \
        << lyr2au(lyr) << " astronomical units." \
        << endl;
}

double lyr2au(double light_year)
{
    return light_year * 63240;
}