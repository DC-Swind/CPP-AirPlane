#include <iostream>
#include "Map.h"
#include <dos.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <time.h>
#include "heap_var.h"
#include "mycls.h"
#include "maze2.h"
#include <fstream>
using namespace std;
int overmovie();
int start()
{
    MAP map(10,10,'A');
    map.clear_map(' ');
    map.print_map();
	
    int turn,ey,espeed,blood;
	int time = 0;
	int tmppp;
    while(true){
		tmppp = clock();
        //fout<<tmppp<<endl;
		turn =0;
        if(_kbhit()){
            char ch = _getch();
            switch(ch){
                case 100:    turn = RIGHT;    break;//向右 d   
                case 119:    turn = UP;    break;//向上 w
                case 97:    turn = LEFT;    break;//向左 a
                case 115:    turn = DOWN;    break;//向下 s
				case 105:   ey=rand()%(max_y-2)+1; espeed = rand()%2+1; blood = rand()%5+1; map.add_e(1,ey,espeed,blood); break;   //增加敌机 i
				case 114:    map.reborn();  break;
				case 'j':    map.attack();  break;
                case 'p':    system("pause");exit(0);break;//press p to exit
				case 'm':   if (bug) map.screen_clear(); break;
				case 'z':   map.shop(); break;
				case 'q':   q_count ++; if (q_count >6) bug = true; break;
                default:    ;
            }
        }
		if (over_movie) break;
		if (game_main_time >150) game_main_time = 4;
		if (game_main_time >300) game_main_time = 3;
		if (game_main_time >500) game_main_time = 2;
		if (game_main_time >850) game_main_time = 1;
		if (game_main_time%speed_add_e == 0){
			ey=rand()%(max_y-2)+1; espeed = rand()%2+1; blood = rand()%2+1; map.add_e(1,ey,espeed,blood);
		}
		
		if (time % 200 == 0 ){
			//fout<<time<<endl;
			map.move_ball();
		}
		
		if (map.getE_num()>0){		
			//int tmppp = clock();
			map.move_plane(time);
			//fout<<clock()-tmppp<<endl;
		}
		time = (time+100)%800;
		game_main_time+=1;
        if (turn!=0){
			map.move(turn);
        }
		clrscr();
        map.print_map();
		//fout<<time<<endl;
       // Sleep(10);
		//fout<<clock()- tmppp<<endl;
    }
	overmovie();
    system("pause");
    return 0;
}
int overmovie()
{
	cout<<"恭喜你！通关！"<<endl;
	cout<<"总共用时："<<game_main_time<<"回合"<<endl;

	return 0;
}
int test()
{
	while(1){
		cout<<clock()<<endl;
		Sleep(100);
	}
	return 0;
}
int test2()
{
	Maze2 maze;
	maze.print();
	maze.start();
	system("pause");
	return 0;
}
int pre_movie()
{
	int tt = 200;  string space = "              "; int xx = 3;
	cout<<endl<<endl<<endl<<space; Sleep(tt);
	cout<<"年 "; Sleep(tt);cout<<"度 "; Sleep(tt);cout<<"巨 "; Sleep(tt);cout<<"制 "; Sleep(tt);cout<<" ："<<endl; Sleep(tt);
	cout<<endl<<endl<<space<<space<<"--------";Sleep(tt);
	cout<<"打 "; Sleep(tt);cout<<"飞 "; Sleep(tt);cout<<"机 "; Sleep(tt);cout<<" "; Sleep(tt);
	cout<<endl<<endl<<space;
	cout<<"游 "; Sleep(tt);cout<<"戏 "; Sleep(tt);cout<<"背 "; Sleep(tt);cout<<"景 "; Sleep(tt);cout<<"： "; Sleep(tt);
	cout<<endl<<endl<<space;
	cout<<"自 "; Sleep(xx*tt);cout<<"己 "; Sleep(xx*tt);cout<<"Y "; Sleep(xx*tt);cout<<"Y      "; Sleep(xx*tt);
	cout<<"! "; Sleep(xx*tt);cout<<"!! "; Sleep(xx*tt);cout<<"!!! "; Sleep(xx*tt);
	cout<<endl<<endl<<space<<"加载完成，";
	system("pause");
	clrscr();
	return 0;
}
int plane_title()
{
	int tt = 200;  string space = "              ";
	cout<<endl<<endl<<endl<<space;
	cout<<"先打会儿飞机吧！！！"<<endl;
	cout<<endl<<space<<"5秒后游戏开始:"; Sleep(1000);
	for (int i=5;i>0;i--){cout<<" "<<i; Sleep(1000);}
	cout<<endl;
	return 0;
}
int main()
{
	//pre_movie();
	system("cls");
	//plane_title();
	system("cls");
	//test();
	test2();
    //start();
    return 0;
}