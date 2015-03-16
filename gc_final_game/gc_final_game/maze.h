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
					case 100:    turn = RIGHT;    break;//向右 d   
					case 119:    turn = UP;    break;//向上 w
					case 97:    turn = LEFT;    break;//向左 a
					case 115:    turn = DOWN;    break;//向下 s
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
			cout<<"飞机打累了吧！骚年，走过迷宫，寻找你的女神吧！"<<endl;
			cout<<"10秒后游戏继续，快速阅读说明吧！"<<endl<<endl;
			cout<<"+是墙，*是你，女神在出口"<<endl<<endl;
			cout<<"第一步：找到你自己"<<endl;
			cout<<"第二步：找到你的女神"<<endl<<endl;
			cout<<"w-上，a-左，s-下，d-右"<<endl;
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
		cout<<"w-上，a-左，s-下，d-右"<<endl;
		return 0;
	}
};
#endif