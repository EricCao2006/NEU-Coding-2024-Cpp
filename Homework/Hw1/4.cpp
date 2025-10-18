/**摄氏度转换为华氏度，华氏温度=1.8×摄氏温度＋32.0*/
#include <iostream>
double c2f(double celsius);
int main()
{
    using namespace std;
    double c;
    cout << "Please enter a Celsius value:";
    cin >> c;
    cout << c << " degrees Celsius is " << c2f(c) \
         << " degrees Fahrenheit." << endl;
}
double c2f(double celsius)
    {return 1.8 * celsius + 32.0;}