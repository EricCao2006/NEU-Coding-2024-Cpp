#include <iostream>
using namespace std;
void showtime(int hour,int min);
int main()
{
    int hr,min;
    cout << "Enter the number of hours: ";
    cin >> hr;
    cout << "Enter the number of minutes: ";
    cin >> min;
    showtime(hr,min);
    return 0;
}
void showtime(int hour,int minute)
{
    cout << "Time:" << hour << ":" \
        << minute << endl ;
}