#ifndef _MYCLS_H_
#define _MYCLS_H_
#include <Windows.h>
#define PERR(bSuccess, api){ if(!(bSuccess)) printf("%s:Error %d from %s \on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
void MyCls(HANDLE hConsole){
//设置清屏后光标返回的屏幕左上角坐标
COORD coordScreen={0, 0};
BOOL bSuccess;
DWORD cCharsWritten;
//保存缓冲区信息
CONSOLE_SCREEN_BUFFER_INFO csbi;
//当前缓冲区可容纳的字符数
DWORD dwConSize;
//获得缓冲区信息
bSuccess = GetConsoleScreenBufferInfo(hConsole,&csbi);
PERR(bSuccess,"GetConsoleScreenBufferInfo");
//缓冲区容纳字符数目
dwConSize = (csbi.dwSize.X) * (csbi.dwSize.Y);
//用空格填充缓冲区
//bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
PERR(bSuccess,"FillConsoleOutputCharacter");
//获得缓冲区信息
bSuccess = GetConsoleScreenBufferInfo(hConsole,&csbi);
PERR(bSuccess, "ConsoleScreenBufferInfo");
//填充缓冲区属性
bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
PERR(bSuccess, "FillConsoleOutputAttribute");
//光标返回屏幕左上角坐标
bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
PERR(bSuccess,"SetConsoleCursorPosition");
return;
}
//清屏函数
void clrscr(void){
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
MyCls(hStdOut);
return;
}
#endif