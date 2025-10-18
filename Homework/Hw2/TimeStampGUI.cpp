// 时间标记的图形界面显示
#include <windows.h>
#include <string>
#include <sstream>
#include "TimeStamp.h"

// 全局变量
HWND hEditTimestamp;
HWND hBtnConvert, hBtnReverseConvert;
HWND hEditYear, hEditMonth, hEditDay;
HWND hEditHour, hEditMinute, hEditSecond;
HINSTANCE hInst;

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateTimeDisplay(TimeStamp& ts);
std::wstring StringToWString(const std::string& str);
std::string WStringToString(const std::wstring& wstr);

// std::string转std::wstring
std::wstring StringToWString(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// std::wstring转std::string
std::string WStringToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// 更新时间显示
void UpdateTimeDisplay(TimeStamp& ts) {
    SetWindowTextW(hEditYear, StringToWString(ts.getYear()).c_str());
    SetWindowTextW(hEditMonth, StringToWString(ts.getMonth()).c_str());
    SetWindowTextW(hEditDay, StringToWString(ts.getDay()).c_str());
    SetWindowTextW(hEditHour, StringToWString(ts.getHour()).c_str());
    SetWindowTextW(hEditMinute, StringToWString(ts.getMinute()).c_str());
    SetWindowTextW(hEditSecond, StringToWString(ts.getSecond()).c_str());
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_CREATE:
        {
            // 创建时间戳输入框
            hEditTimestamp = CreateWindowW(
                L"EDIT", L"时间戳，默认为当前时间",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                10, 10, 150, 25,
                hwnd, NULL, hInst, NULL
            );

            // 创建正向转换按钮
            hBtnConvert = CreateWindowW(
                L"BUTTON", L"转换>",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                170, 10, 80, 25,
                hwnd, (HMENU)1, hInst, NULL
            );

            // 创建反向转换按钮
            hBtnReverseConvert = CreateWindowW(
                L"BUTTON", L"<转换",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                170, 40, 80, 25,
                hwnd, (HMENU)2, hInst, NULL
            );

            // 创建标签说明 - 第一行
            CreateWindowW(
                L"STATIC", L"年:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10, 40, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            CreateWindowW(
                L"STATIC", L"月:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                90, 40, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            CreateWindowW(
                L"STATIC", L"日:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                170, 40, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            // 创建时间输入框 - 第一行（年月日）
            hEditYear = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                45, 40, 40, 25,
                hwnd, NULL, hInst, NULL
            );

            hEditMonth = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                125, 40, 40, 25,
                hwnd, NULL, hInst, NULL
            );

            hEditDay = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                205, 40, 40, 25,
                hwnd, NULL, hInst, NULL
            );

            // 创建标签说明 - 第二行
            CreateWindowW(
                L"STATIC", L"时:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10, 70, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            CreateWindowW(
                L"STATIC", L"分:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                90, 70, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            CreateWindowW(
                L"STATIC", L"秒:",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                170, 70, 30, 25,
                hwnd, NULL, hInst, NULL
            );

            // 创建时间输入框 - 第二行（时分秒）
            hEditHour = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                45, 70, 40, 25,
                hwnd, NULL, hInst, NULL
            );

            hEditMinute = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                125, 70, 40, 25,
                hwnd, NULL, hInst, NULL
            );

            hEditSecond = CreateWindowW(
                L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                205, 70, 40, 25,
                hwnd, NULL, hInst, NULL
            );
        }
        return 0;

    case WM_COMMAND:
        if(LOWORD(wParam) == 1) { // 正向转换按钮被点击（时间戳->各部分）
            wchar_t buffer[256];
            GetWindowTextW(hEditTimestamp, buffer, sizeof(buffer)/sizeof(wchar_t));

            TimeStamp ts;
            if(wcslen(buffer) > 0) {
                long timestamp = _wtol(buffer);
                ts.set(timestamp);
            } else {
                ts.set(); // 使用当前时间
            }

            UpdateTimeDisplay(ts);
        }
        else if(LOWORD(wParam) == 2) { // 反向转换按钮被点击（各部分->时间戳）
            // 获取各个时间部分的值
            wchar_t yearBuf[16], monthBuf[16], dayBuf[16];
            wchar_t hourBuf[16], minuteBuf[16], secondBuf[16];

            GetWindowTextW(hEditYear, yearBuf, sizeof(yearBuf)/sizeof(wchar_t));
            GetWindowTextW(hEditMonth, monthBuf, sizeof(monthBuf)/sizeof(wchar_t));
            GetWindowTextW(hEditDay, dayBuf, sizeof(dayBuf)/sizeof(wchar_t));
            GetWindowTextW(hEditHour, hourBuf, sizeof(hourBuf)/sizeof(wchar_t));
            GetWindowTextW(hEditMinute, minuteBuf, sizeof(minuteBuf)/sizeof(wchar_t));
            GetWindowTextW(hEditSecond, secondBuf, sizeof(secondBuf)/sizeof(wchar_t));

            // 转换为std::string
            std::string year = WStringToString(std::wstring(yearBuf));
            std::string month = WStringToString(std::wstring(monthBuf));
            std::string day = WStringToString(std::wstring(dayBuf));
            std::string hour = WStringToString(std::wstring(hourBuf));
            std::string minute = WStringToString(std::wstring(minuteBuf));
            std::string second = WStringToString(std::wstring(secondBuf));

            // 使用splicing函数组合时间
            TimeStamp ts = ts.splicing(year, month, day, hour, minute, second);

            // 更新时间戳显示框
            wchar_t timestampStr[32];
            swprintf(timestampStr, L"%ld", ts.get());
            SetWindowTextW(hEditTimestamp, timestampStr);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// WinMain函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"TimeStampConverter";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // 检查窗口类是否注册成功
    if (!RegisterClassW(&wc)) {
        return 1;
    }

    HWND hwnd = CreateWindowW(
        L"TimeStampConverter",
        L"时间戳转换工具",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 260, 130,
        NULL, NULL, hInstance, NULL
    );

    // 检查窗口是否创建成功
    if (!hwnd) {
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    // 使用更标准的消息循环
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

int main() {
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOW);
}
