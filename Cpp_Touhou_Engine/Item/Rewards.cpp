//By @Sun-XX

#include "Item.hpp"

Rewards::Rewards(Texture pic,int w,int h,float init_x,float init_y){
	this->picture = pic;
	this->width = w; this->height = h; //��ͼ 
	
	this->x = init_x; this->y = init_y; //��ʼ����
	this->angle = 0; this-> a_angle = 0;
	this->velocity = 0; this->a_velocity =0; 
	
	this->alive = true;
	this->flash = 0; //��ʼ֡Ϊ0 
}

bool Rewards::near_player(float player_x,float player_y,float min_distance){
	//�������������������ж� 
	return (get_distance(this->x,this->y,player_x,player_y)<min_distance)?true:false;
}

bool Rewards::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//�����ж�
	return !(this->x>screen_xl && this->x<screen_xr && this->y>screen_yb && this->y<screen_yt);
	//��������true ��֮����false
}

bool Rewards::~Rewards(){ //�������� �������� 
	delete this;
}
