#pragma once
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

/**
 * 时间标记
 */
class TimeStamp {
private:
    /**时间戳*/
    time_t stamp;
    /**
     * 时间字符串切片工具
     * ctime提供的时间字符串的格式为：
     * Sun Sep 28 20:33:33 2025[换行符][null字符]
     * @param offset 时间偏移量
     * @param count 字符串长度
     * @return
     */
    string extract (int offset, int count) const {
        string timeString = ctime(&stamp);
        return timeString.substr(offset, count);
    }

public:
    /**时间戳设定，一定非负*/
    void set (long s = 0) {
        if (s <= 0) {stamp = time(0);}
        else {stamp = s;}
    }
    time_t get() const {return stamp;}
    // 时间戳切片系列函数：
    string getAsString() const {return extract(0,24);}
    string getYear() const {return extract(20,4);}
    string getMonth() const {return extract(4,3);}
    string getDay() const {return extract(8,2);}
    string getHour() const {return extract(11,2);}
    string getMinute() const {return extract(14,2);}
    string getSecond() const {return extract(17,2);}
    /**
     * 时间字符串转换回时间戳
     */
    time_t stringToStamp(string TimeString) const {
        struct tm timeinfo = {0};
        char monthStr[4];
        sscanf(TimeString.c_str(), "%*s %3s %2d %2d:%2d:%2d %4d",
               monthStr, &timeinfo.tm_mday,
               &timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec,
               &timeinfo.tm_year);
        timeinfo.tm_isdst = -1;
        timeinfo.tm_year -= 1900;
        string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        for (int i = 0; i < 12; i++) {
            if (months[i] == string(monthStr)) {
                timeinfo.tm_mon = i;
                break;
            }
        }
        return mktime(&timeinfo);
    }

    /**
    *时间标记拼接
    * @param Year 六部分
    * @return 时间标记
    */
    TimeStamp splicing(string Year, string Month, string Day, string Hour, string Minute, string Second) const {
        //先拼接时间字符串
        string timeString = Year + " " + Month + " " + Day + " " + Hour + " " + Minute + " " + Second;
        //再转换成时间戳
        TimeStamp result;
        result.set(stringToStamp(timeString));
        return result;
    }
};