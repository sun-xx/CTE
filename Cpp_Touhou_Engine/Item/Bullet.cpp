//By @Sun-XX

/*
Bullet的源代码。
终于来啦，对于子弹的实现（笑）
（编不下去了 
*/

#include "Item.hpp"

//实现顺序为：构造函数-演出-碰撞-出屏-移动-显示-析构函数 

Bullet::Bullet(Texture pic,int w,int h,float init_x,float init_y,float r_){
	/* 构造函数的实现。大抵就是几个赋值 */
	this->picture = pic;
	this->width = w; this->height = h; //贴图参数 
	
	this->x = init_x; this->y = init_y; //初始坐标 
	this->temp_x = this->x; this->temp_y = this->y;
	this->r = r_;
	
	this->alive = 1; //子弹存活  
	this->angle = 0; this->a_angle = 0; //初始方向
	this->speed = 0; this->a_speed = 0;
	this->flash = 0; 
	this->temp_flash = 0;
}

void Bullet::run(){ //每帧子弹运行 
	this->flash += 1; //帧数增加 
	
	if(this->alive == true){
		this->temp_x = x; this->temp_y = y; //将这帧坐标缓存 准备更新坐标
		this->angle += this->a_angle;
		this->speed += this->a_speed;
	
		special_play(); //特效
		
		if(hit_player(player_tx,player_ty,player_x,player_y) == true){ //一帧内如果碰撞自机自我销毁 
			this->alive = false;
			this->temp_flash = this->flash;
		} 
	}
	else{ //子弹受撞击 
		if((this->flash - this->temp_flash) < 15) //15f内执行消失特效 
			this->die_play(); //消失特效
		else //15f后自我删除 
			delete this;
	}
	this->show();
}

bool Bullet::hit_player(int player_tx,int player_ty,int player_x,int player_y,float player_r){
	//参数方程&一元二次方程求解子弹与自机一帧内轨迹是否正交 
	int X1,X2,Y1,Y2;
	X1 = temp_x - player_tx; X2 = x - player_x - X1;
	Y1 = temp_y - player_ty; Y2 = y - player_y - Y1;
	int a = X2^2 + Y2^2,
	b = 2*(X1*X2 + Y1*Y2);
	float c = X1*X1 + Y1*Y1 - r*r - player_r*player_r;
	float delta = b*b - 4*a*c;
	
	float t1 = (-b + Qsqrt(delta))/(2*a),
	t2 = (-b - Qsqrt(delta))/(2*a);
	
	return delta<0?false:((t1>=0 && t1<=1)||(t2>=0 && t1<=1)); //任意一个方程根在范围内即判定正交 
}

bool Bullet::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//出屏判断
	return !(x>screen_xl && x<screen_xr && y>screen_yb && y<screen_yt);
	//出屏返回true 反之返回false
}

void Bullet::move(){
	this->x += Qcos(angle)*speed;
	this->y += Qsin(angle)*speed; 
}

void Bullet::show(){ //显示 
	this->picture.rotate_show(window_renderer,x,y,angle); 
	//window_render为全局变量，窗口 
}

Bullet::~Bullet(){
	delete this;
}
