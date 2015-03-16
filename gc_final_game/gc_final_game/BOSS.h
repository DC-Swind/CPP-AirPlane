#ifndef _BOSS_
#define _BOSS_
class BOSS{
	int blood;
	int speed;
	Player *player;
public:
	int start(Player *tmp)
	{
		player = tmp;
		while(true){
			int turn =0;
			if(_kbhit()){
				char ch = _getch();
				switch(ch){
					case 100:    turn = RIGHT;    break;//向右 d   
					case 119:    turn = UP;    break;//向上 w
					case 97:    turn = LEFT;    break;//向左 a
					case 115:    turn = DOWN;    break;//向下 s
					case 114:    map.reborn();  break;
					case 'j':    fout<<clock()<<" "<<pre_ball<<endl; if (clock() - pre_ball <200) break; pre_ball = clock(); map.attack();  break;
					case 'p':    system("pause");exit(0);break;//press p to exit
					default:    ;
				}
			}
			if (game_main_time%10 == 0){
				ey=rand()%(max_y-2)+1; espeed = rand()%2+1; blood = rand()%2+1; map.add_e(1,ey,espeed,blood);
			}
			if (time % 200 == 0 ){
				//fout<<time<<endl;
				map.move_ball();
			}
		
		
			time = (time+100)%800;
			game_main_time+=1;
			if (turn!=0){
				map.move(turn);
			}
			clrscr();
			map.print_map();
		}
	}
};
#endif