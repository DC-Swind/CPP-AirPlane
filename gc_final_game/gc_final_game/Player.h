#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "coordinate.h"
class Player:private Coordinate{
	bool dead;
	char flag;
	int level;
	int exp;
	bool leida;
	bool miji;
	bool hujia;
	int zidan;
public:
	Player(){}
	Player(int xx,int yy,char f,int l){x=xx; y=yy; flag=f; dead=false; level= l; exp = 0; leida = false; miji = false; zidan = 50; hujia = false;}
	int getx(){return x;}
	int gety(){return y;}
	bool getd(){return dead;}
	int getexp(){return exp;}
	bool getleida(){return leida;}
	bool getmiji(){return miji;}
	bool gethujia(){return hujia;}
	int changeleida(bool x){leida = x; return 0;}
	int changemiji(bool x){miji = x; return 0;}
	int changehujia(bool x){hujia = x; return 0;}
	int changeexp(int x){
		exp = exp+x; 
		if (exp<0) exp = 0;
		if (exp <100) changelevel(1); else if (exp<300) changelevel(2); else changelevel(3);
		return 0;
	}
	int changed(bool tmp){dead = tmp; return 0;}
	char getf(){return flag;}
	int getlevel(){return level;}
	int move(int order)
	{
		switch(order){
        case 1:  if (y<max_y-2) y++; break;
        case 2:  if (y>1) y--; break;
        case 3:  if (x>1) x--; break;
        case 4:  if (x<max_x-2) x++; break;
        default:  break;
        }
		return 0;
	}
	int changelevel(int x){level =x; return 0;}
	int getzidan(){return zidan;}
	int changezidan(int x){zidan +=x; return 0;}
};
#endif