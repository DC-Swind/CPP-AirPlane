#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "coordinate.h"
class Enemy:private Coordinate
{
	int speed;
	int blood;
	bool v;
	bool yinshen;
public:
	Enemy(){}
	Enemy(int xx,int yy,int s,int b,bool ys=false)
	{
		x = xx;
		y = yy;
		speed = s;
		blood = b;
		v = true;
		yinshen = ys;
	}
	int getx(){return x;}
	int gety(){return y;}
	bool getyinshen(){return yinshen;}
	int getspeed(){return speed;}
	bool getv(){return v;}
	int getblood(){return blood;}
	int move(int m,int tmpx, int tmpy)
	{
		x+=m;
		int ty = rand()%2; int tt = rand()%5;
		if (tt == 0 && y+ty<max_y-2) y+=ty;
		if (tt == 1 && y-ty>0) y-=ty;
		if (tt >= 2){
			if (y>tmpy) y-=1;
			if (y<tmpy) y+=1;
		}
		return 0;
	}
	int changev(bool tmp){v = tmp; return 0;}
	int changeb(int x){blood -=x; return 0;}
};
#endif