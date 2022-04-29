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

bool Rewards::near_player(float player_x,float player_y,float min_distance){
	//勾股求距离与给定距离判断 
	return (Qsqrt((player_x - this->x)^2 + (player_y - this->y)^2)<min_distance)?true:false;
}

bool Rewards::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//出屏判断
	return !(x>screen_xl && x<screen_xr && y>screen_yb && y<screen_yt);
	//出屏返回true 反之返回false
}

bool Rewards::~Rewards(){ //析构函数 自我销毁 
	delete this;
}
