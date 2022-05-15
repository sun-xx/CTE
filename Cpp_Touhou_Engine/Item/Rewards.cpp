//By @Sun-XX

#include "Item.hpp"

Rewards::Rewards(Texture pic,int w,int h,float init_x,float init_y){
	this->picture = pic;
	this->width = w; this->height = h; //贴图

	this->x = init_x; this->y = init_y; //初始坐标
	this->angle = 0; this-> a_angle = 0;
	this->velocity = 0; this->a_velocity =0;

	this->alive = true;
	this->flash = 0; //初始帧为0
}

/*bool Rewards::near_player(float player_x,float player_y,float min_distance,
							float min_y,int special_condition){
	return (SDL_sqrt((player_x - this->x)^2+(player_y - this->y)^2) < min_distance) //接近自机
										||
		   						(player_y > min_y) //上线
								   		||
							(special_condition == true)) //特殊条件
									?true:false;
}*/

bool Rewards::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//出屏判断
	return !(this->x>screen_xl && this->x<screen_xr && this->y>screen_yb && this->y<screen_yt);
	//出屏返回true 反之返回false
}

Rewards::~Rewards(){ //防止用户忘记释放而写的默认析构函数
	delete this;
}
