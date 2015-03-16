#ifndef _MYCLS_H_
#define _MYCLS_H_
#include <Windows.h>
#define PERR(bSuccess, api){ if(!(bSuccess)) printf("%s:Error %d from %s \on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
void MyCls(HANDLE hConsole){
//�����������귵�ص���Ļ���Ͻ�����
COORD coordScreen={0, 0};
BOOL bSuccess;
DWORD cCharsWritten;
//���滺������Ϣ
CONSOLE_SCREEN_BUFFER_INFO csbi;
//��ǰ�����������ɵ��ַ���
DWORD dwConSize;
//��û�������Ϣ
bSuccess = GetConsoleScreenBufferInfo(hConsole,&csbi);
PERR(bSuccess,"GetConsoleScreenBufferInfo");
//�����������ַ���Ŀ
dwConSize = (csbi.dwSize.X) * (csbi.dwSize.Y);
//�ÿո���仺����
//bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
PERR(bSuccess,"FillConsoleOutputCharacter");
//��û�������Ϣ
bSuccess = GetConsoleScreenBufferInfo(hConsole,&csbi);
PERR(bSuccess, "ConsoleScreenBufferInfo");
//��仺��������
bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
PERR(bSuccess, "FillConsoleOutputAttribute");
//��귵����Ļ���Ͻ�����
bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
PERR(bSuccess,"SetConsoleCursorPosition");
return;
}
//��������
void clrscr(void){
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
MyCls(hStdOut);
return;
}
#endif