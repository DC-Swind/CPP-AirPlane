#ifndef _MAZE_
#define _MAZE_
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "mycls.h"
using namespace std;
class Maze{
	int x,y;
	int xx,yy;
	bool flag;
	bool first;
public:
	Maze()
	{
		xx = 4; yy = 3;
		x =22; y=20; flag = false; first = true;
	}
	int start()
	{
		while(true){
			int turn =-1;
			if(_kbhit()){
				char ch = _getch();
				switch(ch){
					case 100:    turn = RIGHT;    break;//���� d   
					case 119:    turn = UP;    break;//���� w
					case 97:    turn = LEFT;    break;//���� a
					case 115:    turn = DOWN;    break;//���� s
					case 'p':    system("pause");exit(0);break;//press p to exit
					default:    ;
				}
			}
			if (turn != -1)move(turn);
			if (flag) {
				break;
			}
			clrscr();
			print();
			game_main_time++;
			Sleep(100);
		}
		return 0;
	}
	int move(int turn)
	{
		switch(turn){
		case UP: if (x>0 && maze_map[x-1][y] == 0) x--; break;
		case DOWN: if (x<mz_x-1 && maze_map[x+1][y] == 0) x++; break;
		case LEFT: if (y>0 && maze_map[x][y-1] == 0) y--; break;
		case RIGHT: if (y<mz_y-1 && maze_map[x][y+1] == 0) y++; break;
		default:;
		}
		if ( x == 0 && y == 11) flag = true;
		return 0;
	}
	int print()
	{
		if (first)
		{
			cout<<"�ɻ������˰ɣ�ɧ�꣬�߹��Թ���Ѱ�����Ů��ɣ�"<<endl;
			cout<<"10�����Ϸ�����������Ķ�˵���ɣ�"<<endl<<endl;
			cout<<"+��ǽ��*���㣬Ů���ڳ���"<<endl<<endl;
			cout<<"��һ�����ҵ����Լ�"<<endl;
			cout<<"�ڶ������ҵ����Ů��"<<endl<<endl;
			cout<<"w-�ϣ�a-��s-�£�d-��"<<endl;
			Sleep(10000);
			system("cls");
			first = false;
			return 0;
		}
		//cout<<maze_map[x][y]<<endl;
		for (int i=0; i<mz_x; i++){
			for (int j=0; j<mz_y; j++) {
				if(maze_map[i][j] == 1)cout<<'+';
				if(maze_map[i][j] == 0){
					if (i == x && j==y) cout<<"*"; else cout<<" ";
				}
				if(maze_map[i][j] == 2)cout<<"&";
			}
			if (i == 1) cout<<"    "<<"gametime:"<<game_main_time;
			if (i == 3) cout<<"    "<<"score:"<<score;
			cout<<endl;
		}
		cout<<"w-�ϣ�a-��s-�£�d-��"<<endl;
		return 0;
	}
};
#endif