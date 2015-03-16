#ifndef _MAP_H_
#define _MAP_H_
#include <iostream>
#include "heap_var.h"
#include "Enemy.h"
#include "BALL.h"
#include "Player.h"
#include <iomanip>
#include "maze2.h"
#include <string>
using namespace std;


struct E_list{
	Enemy *plane;
	E_list *next;
};
struct B_list{
	BALL *ball;
	B_list *next;
};
class MAP{
    Player *player;
    char map[max_x][max_y];
	E_list *E_plane;
	int E_num;
	
	B_list *myball;
	int myball_n;

	bool fuben;
public:
	MAP(){}
	MAP(int xx,int yy,int f){player = new Player(xx,yy,f,1); E_num =0 ; myball_n =0;fuben = false;}
    
    int print_map()
    {
		if (E_num>0){
			E_list * tmp = E_plane;
			while(tmp!=NULL){
				if (tmp->plane->getx() == player->getx() && tmp->plane->gety() == player->gety()){
					gameover();
					tmp->plane->changev(false);
				}else if (!tmp->plane->getyinshen() || player->getleida())
				map[tmp->plane->getx()][tmp->plane->gety()]='T';
				tmp = tmp->next;
			}
		}
		if (myball_n>0){
			B_list * tmpp = myball;
			while (tmpp!=NULL){
				map[tmpp->ball->getx()][tmpp->ball->gety()] = '.';
				tmpp= tmpp->next;
			}
		}
		if (player->getd()) map[player->getx()][player->gety()] = 'X'; 
		else {  
			map[player->getx()][player->gety()] = player->getf(); 
			if (player->gethujia()){
				if (player->gety()>1) map[player->getx()][player->gety()-1] = '<';
				if (player->gety()<max_y-2) map[player->getx()][player->gety()+1] = '>';
			}
		}
        for (int i=0; i<max_x; i++){
            for (int j=0; j<max_y; j++) cout<<map[i][j];
			if (i == 1) cout<<"  "<<"gametime:"<<game_main_time;
			if (i == 3) cout<<"  "<<"score:   "<<score;
			if (player->getmiji() && !fuben){
				fuben = true;
				screen_clear();
				system("cls");
				Maze2 maze;
				maze.start();
				system("cls");
				over_movie = true;
				return 0;
			}
			if (i == 5) cout<<"  "<<"level:   "<<player->getlevel();
			if (i == 7) cout<<"  "<<"exp:     "<<setw(3)<<player->getexp();
			if (i == 9) cout<<"  "<<"hujia：    x"<<player->gethujia();
			if (i == 11) cout<<"  "<<"ball:    "<<setw(3)<<player->getzidan();
			if (i == 13) cout<<"  "<<"miji：    x"<<player->getmiji();
			if (i == 15) cout<<"  "<<"leida：   x"<<player->getleida();
			if (i == 17) cout<<"  "<<"z-shop";
            cout<<endl;
        }
        cout<<"w-UP / a-LEFT / s-DOWN / d-RIGHT /i-adde /j-attack /r-reborn/ p-exit"<<endl;
        return 0;
    }
    int clear_map(char c)
    {
		//if (c == ' '){
			for (int i=0; i<max_x; i++)
				for (int j=0; j<max_y; j++){
					if (i == 0 || i==max_x-1) map[i][j]='-';else
					if (j == 0 || j==max_y-1) map[i][j]='|';else
						map[i][j]=' ';
				}
		//}
		//else{
		//	for (int i=0; i<max_x; i++)
		//		for (int j=0; j<max_y; j++) if (map[i][j] == c) map[i][j] = ' ';
		//}


        return 0;
    }
    int move(int order){
		if (player->getd()) return 0;
		map[player->getx()][player->gety()]=' ';
		player->move(order);
        return 0;
    }
	int getE_num(){return E_num;}
	int getball_n(){return myball_n;}
	int add_e(int xx,int yy,int s,int b)
	{
		Enemy *tmp= new Enemy(xx,yy,s,b,rand()%2);  /////////////////*****yinshen
		if (E_num == 0) {
			E_plane = new E_list;
			E_plane->plane = tmp;
			E_plane->next =NULL;
			E_num++;
		} else{
			E_list *tmpp = E_plane;
			while (tmpp->next!=NULL) tmpp = tmpp->next;
			tmpp->next = new E_list;
			tmpp->next->next = NULL;
			tmpp->next->plane = tmp;
			E_num++;
		}
		return 0;
	}
	int gameover()
	{
		if (!player->getd())player->changeexp(-100);
		player->changed(true);
		player->changeleida(false);
		player->changemiji(false);
		player->changehujia(false);
		return 0;
	}
	int move_plane(int time)
	{
		if (E_num == 0) return 0;
		E_list *tmp = E_plane;
		clear_map('#');
		while (tmp!=NULL){
			if ((3-tmp->plane->getspeed())*time%800 ==0 ){
				tmp->plane->move(1,player->getx(),player->gety());
			}
			if (myball_n>0){
				B_list *tmpp =myball;
				while (tmpp!=NULL){
					if (tmpp->ball->getx() == tmp->plane->getx() && tmpp->ball->gety() == tmp->plane->gety()){
						tmpp->ball->change_v(false);
						//tmp->plane->changev(false);
						tmp->plane->changeb(1);
						if (tmp->plane->getblood() == 0) tmp->plane->changev(false);
						score++; player->changeexp(1);
						break;
					}
					tmpp = tmpp->next;
				}
			}
			tmp = tmp->next;
		}
		tmp = E_plane; E_list *tmp_pre = NULL;
		while (tmp!=NULL){
			if (tmp->plane->getx()>max_x-2 || !tmp->plane->getv()){
				if (tmp_pre == NULL){ E_plane = E_plane->next; delete tmp->plane; delete tmp; tmp = E_plane;}
				else {tmp_pre->next = tmp->next; delete tmp->plane; delete tmp; tmp = tmp_pre->next;}
				E_num--;
			}else{
				//map[tmp->plane->getx()][tmp->plane->gety()] = '#';
				tmp_pre = tmp;
				tmp = tmp->next;
			}
		}
		if (myball_n>0){
		B_list *tmppp = myball; B_list *tmppp_pre = NULL;	
		while (tmppp!=NULL){
			if (tmppp->ball->getx()<2 ||!tmppp->ball->getv()){
				if (tmppp_pre == NULL){ myball = myball->next; delete tmppp->ball; delete tmppp; tmppp = myball;}
				else {tmppp_pre->next = tmppp->next; delete tmppp->ball; delete tmppp; tmppp = tmppp_pre->next;}
				myball_n--;
			}else{
				tmppp_pre = tmppp;
				tmppp = tmppp->next;
			}
		}
		}
		return 0;
	}
	int reborn()
	{
		player->changed(false);
		return 0;
	}
	int attack()
	{
		if (player->getzidan() == 0) return 0;
		player->changezidan(-1);
		if (player->getd()) return 0;
		switch (player->getlevel()){
		case 1: add_ball(1); break;
		case 2: add_ball(2);add_ball(3); break;
		case 3: add_ball(1);add_ball(2); add_ball(3); break;
		default:;
		}
		return 0;
	}
	int add_ball(int x)
	{		
		BALL *tmp= new BALL(player->getx()-1,player->gety(),x);
		if (myball_n == 0) {
			myball = new B_list;
			myball->ball = tmp;
			myball->next =NULL;
			myball_n++;
		} else{
			B_list *tmpp = myball;
			while (tmpp->next!=NULL) tmpp = tmpp->next;
			tmpp->next = new B_list;
			tmpp->next->next = NULL;
			tmpp->next->ball = tmp;
			myball_n++;
		}
		return 0;
	}
	int move_ball()
	{
		if (myball_n == 0) return 0;
		B_list *tmp = myball;
		while (tmp!=NULL){
			tmp->ball->move();
			if (E_num>0){
				E_list *tmpp = E_plane;
				while (tmpp!=NULL){
					if (tmpp->plane->getx() == tmp->ball->getx() && tmpp->plane->gety() == tmp->ball->gety()){
						//tmpp->plane->changev(false);
						tmpp->plane->changeb(1);
						if (tmpp->plane->getblood() == 0) tmpp->plane->changev(false);
						tmp->ball->change_v(false);
						score++; player->changeexp(1);
						break;
					}
					tmpp = tmpp->next;
				}
			}
			tmp = tmp->next;
		}
		
		tmp = myball; B_list *tmp_pre = NULL;	
		while (tmp!=NULL){
			if (tmp->ball->getx()<2 ||!tmp->ball->getv()){
				if (tmp_pre == NULL){ myball = myball->next; delete tmp->ball; delete tmp; tmp = myball;}
				else {tmp_pre->next = tmp->next; delete tmp->ball; delete tmp; tmp = tmp_pre->next;}
				myball_n--;
			}else{
				tmp_pre = tmp;
				tmp = tmp->next;
			}
		}
		if (E_num>0){
		E_list*tmppp = E_plane; E_list *tmppp_pre = NULL;
		while (tmppp!=NULL){
			if (tmppp->plane->getx()>max_x-2 || !tmppp->plane->getv()){
				if (tmppp_pre == NULL){ E_plane = E_plane->next; delete tmppp->plane; delete tmppp; tmppp = E_plane;}
				else {tmppp_pre->next = tmppp->next; delete tmppp->plane; delete tmppp; tmppp = tmppp_pre->next;}
				E_num--;
			}else{
				tmppp_pre = tmppp;
				tmppp = tmppp->next;
			}
		}
		}
		return 0;
	}
	
	int screen_clear()  //不用的要delete掉
	{
		if (player->getd()) return 0;
		E_num = 0;
		myball_n =0;
		//while(myball != NULL){B_list *tmp = myball; myball = myball->next; delete tmp; }
		//myball = NULL;
		//E_plane =NULL;
		while (E_plane != NULL) {E_list *tmp = E_plane; E_plane = E_plane->next; delete tmp;}
		return 0;
	}
int shop()
{
	int cur = -1;
	system("cls");
	while(true){
		clrscr();
		string space = "     ";
		char a[6]; a[0] = ' '; a[1] = ' '; a[2] = ' '; a[3] = ' '; a[4] = ' ';
		if (cur == -1) cur = 0; a[cur] = '-';
		cout<<endl<<endl<<space<<space<<"Shop:"<<endl<<endl;
		cout<<space<<space<<space<<a[0]<<"miji(500)：It is nessesary！"<<endl;
		cout<<space<<space<<space<<a[1]<<"leida(30)：Detection of stealth！"<<endl;
		cout<<space<<space<<space<<a[2]<<"ball x50(10)：no explain！"<<endl;
		cout<<space<<space<<space<<a[3]<<"hujia(20)：cool、beauty，but useless！"<<endl;
		cout<<space<<space<<space<<a[4]<<"exp x50(5000)：for test！"<<endl;
		cout<<endl<<endl<<space<<space<<"w-UP,s-DOWN  j-buy  z-exit"<<endl;
        if(_kbhit()){
            char ch = _getch();
            switch(ch){
                case 119:    a[cur] = ' '; cur--; if (cur < 0 ) cur =0;   break;//向上 w
                case 115:    a[cur] = ' '; cur++; if (cur > 4 ) cur =4;   break;//向下 s
				case 'j':    if (cur == 0 && score>=500){ player->changemiji(true); score -=500; } 
							 else if (cur == 1 && score>=30) {player->changeleida(true); score-=30;} 
							 else if (cur == 2 && score>=10) {player->changezidan(50); score -=10;}
							 else if (cur == 3 && score>=20) {player->changehujia(true); score -=20;}
							 else if (cur == 4 && score>=5000) {player->changeexp(50); score -=5000;}
							 break;
                case 'z':    return 0; break;//press p to exit
                default:    ;
            }
        }
		Sleep(100);
	}

	system("pause");
	return 0;
}
	
};
#endif