#ifndef _BALL_H_
#define _BALL_H_
#include "coordinate.h"
class BALL:private Coordinate{
	int type;
	bool v;
public:
	BALL(){}
	BALL(int xx,int yy,int t){x = xx,y = yy; type =t; v=true;}
	int move(){
		if (type == 1){
			x--;
			if (x<=0) v =false;
		}
		if (type == 2){
			x--;
			y--;
			if (x<=0 || y<=0) v =false;
		}
		if (type == 3){
			x--; y++;
			if (x<=0 || y>=max_y-1) v=false;
		}
		return 0;
	}
	int getx(){return x;}
	int gety(){return y;}
	bool getv(){return v;}
	int change_v(bool tmp){v=tmp; return 0;}
};
#endif