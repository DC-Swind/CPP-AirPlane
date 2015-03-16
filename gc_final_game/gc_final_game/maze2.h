#ifndef _MAZE2_
#define _MAZE2_
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "mycls.h"
#include <fstream>
#include "coordinate.h"
using namespace std;
ofstream fout2("d://test.txt");
class Stack{
	int top;
	int s[1000][2];
public:
	Stack(){top = -1; srand(time(NULL));}
	int push(int x,int y){top++; s[top][0] = x; s[top][1]=y; return 0;}
	int popx(int &x,int &y){x = s[top][0]; y = s[top][1]; top--; return 0;}
	bool empty(){if (top<0) return true; else return false;}
};
class Maze2:private Coordinate{
	int xx,yy;
	bool flag;
	bool first;
public:
	Maze2()
	{
		xx = mz_x-1; yy = mz_y-2;
		x =1; y=1; flag = false; first = true;
	}
	int dfs(int map[][mz_y],int xxx,int yyy,Stack *ss)
	{
		//if (xxx == 21 && yyy == 21) return 1;
		int dir[4];
		dir[0] = rand()%4+1;
		dir[1] = -1;
		while (dir[1] == dir[0] || dir[1] == -1){ dir[1] = rand()%4+1;}
		dir[2] = -1;
		while (dir[2] == dir[1] || dir[2] == dir[0] || dir[2] == -1) {dir[2] = rand()%4+1;}
		dir[3] = 16-dir[0]-dir[1]-dir[2];
		map[xxx][yyy] = 0;
		for (int i=0; i<4; i++){
			if (dir[i] == UP && can(UP,xxx,yyy) && map[xxx-2][yyy] == 4){
				ss->push(xxx-2,yyy);
				map[xxx-2][yyy] = 3;
				map[xxx-1][yyy] = 0;
			}
			if (dir[i] == DOWN && can(DOWN,xxx,yyy) && map[xxx+2][yyy] == 4){
				ss->push(xxx+2,yyy);
				map[xxx+2][yyy] = 3;
				map[xxx+1][yyy] = 0;
			}
			if (dir[i] == LEFT && can(LEFT,xxx,yyy) && map[xxx][yyy-2] == 4){
				ss->push(xxx,yyy-2);
				map[xxx][yyy-2] = 3;
				map[xxx][yyy-1] = 0;
			}
			if (dir[i] == RIGHT && can(RIGHT,xxx,yyy) && map[xxx][yyy+2] == 4){
				ss->push(xxx,yyy+2);
				map[xxx][yyy+2] = 3;
				map[xxx][yyy+1] = 0;
			}
		}
		return 0;
	}
	int generate_map()
	{
		for (int i = 0; i<mz_x; i++)
			for (int j=0; j<mz_y; j++) if (i %2 ==1 && j %2 == 1)maze_map[i][j] = 4; else maze_map[i][j] = 1;
		
		int out = rand()%3;
		if (out == 0){ xx = mz_x-1; yy = 1;}else if (out == 1) {xx = mz_x-1; yy = mz_y-2;} else {xx = 1; yy = mz_y-1;}
		maze_map[xx][yy] = 0;
		Stack ss;
		ss.push(1,1);
		while (!ss.empty()){
			int tmpx,tmpy;
			ss.popx(tmpx,tmpy);
			dfs(maze_map,tmpx,tmpy,&ss);
		}
		return 0;
	}
	int start()
	{
	
		generate_map();
		while(true){
			if (game_main_time % 30 == 0){
				generate_map();
				clrscr();
				print();
			}
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
			//system("cls");
			print();
			game_main_time++;
			//Sleep(100);
		}
		return 0;
	}
	bool can(int turn,int x,int y)
	{
		switch(turn){
		case UP: if (x>=3) return true; break;
		case DOWN: if (x<mz_x-3) return true; break;
		case LEFT: if (y>=3) return true; break;
		case RIGHT: if (y<mz_y-3) return true; break;
		default:;
		}
		return false;
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
		if ( x == xx && y == yy) flag = true;
		return 0;
	}
	int print()
	{
		if (first)
		{
			cout<<"飞机打累了吧！骚年，恭喜来到(名字自己YY)，穿过迷宫，(后面的剧情请自行YY)！"<<endl;
			cout<<"10秒后游戏继续，快速阅读说明吧！"<<endl<<endl;
			cout<<"*是你"<<endl<<endl;
			cout<<"第一步：找到你自己"<<endl;
			cout<<"第二步：找到出口"<<endl<<endl;
			cout<<"w-上，a-左，s-下，d-右"<<endl;
			Sleep(10000);
			system("cls");
			first = false;
			return 0;
		}
		//cout<<maze_map[x][y]<<endl;
		fout2<<clock()<<" ";
		for (int i=0; i<mz_x; i++){
			for (int j=0; j<mz_y; j++) {
				if (i == x && j == y) cout<<"A"; else
				{
					switch(maze_map[i][j]){
					case 0: cout<<" "; break;
					case 1: if (i % 2 == 0 ) cout<<"-"; else cout<<"|"; break;
					case 2: cout<<"&"; break;
					default: maze_map[i][j] = 0; cout<<" "; break;
					}
				}
				/*
				if(maze_map[i][j] == 0)cout<<" "; else
				if (maze_map[i][j] == 1){if (i%2 == 0) cout<<"-"; else cout<<"|";} else
				//if(maze_map[i][j] == 1)cout<<'+'; 
				if(maze_map[i][j] == 2)cout<<"&"; else 
				{maze_map[i][j] = 0; cout<<" ";} 
				*/
				
			}
			if (i == 1) cout<<"    "<<"gametime:"<<game_main_time;
			if (i == 3) cout<<"    "<<"score:"<<score;
			cout<<endl;
		}
		cout<<"w-UP，a-LEFT，s-DOWN，d-RIGHT"<<endl;
		fout2<<clock()<<endl;
		return 0;
	}
};
#endif