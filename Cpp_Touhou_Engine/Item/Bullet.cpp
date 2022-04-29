//By @Sun-XX

#include "Item.hpp"

Bullet::Bullet(Texture pic,int w,int h,float init_x,float init_y,float r_){
	/* 构造函数的实现。大抵就是几个赋值 */
	this->picture = pic;
	this->width = w; this->height = h; //贴图参数 
	
	this->x = init_x; this->y = init_y; //初始坐标 
	this->temp_x = this->x; this->temp_y = this->y; //初始坐标缓存与坐标统一
	this->angle = 0; this->a_angle = 0; //初始方向
	this->velocity = 0; this->a_velocity = 0; //初始速度
	this->r = r_; //判定半径 
	
	this->alive = true; //子弹存活  
	this->flash = 0; //被生成时帧数为0 
}

virtual void Bullet::run(){ //每帧子弹运行 标准模板 
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
		this->die_play();
	}
	this->show(); //显示 
}

bool Bullet::hit_player(float player_tx,float player_ty,float player_x,float player_y,float player_r){
	//参数方程&一元二次方程求解子弹与自机一帧内轨迹是否正交
	//传参顺序为 上一帧自机坐标，该帧自机坐标，自机判定半径 
	float X1,X2,Y1,Y2;
	X1 = temp_x - player_tx; X2 = x - player_x - X1;
	Y1 = temp_y - player_ty; Y2 = y - player_y - Y1;
	float a = X2^2 + Y2^2,
	b = 2*(X1*X2 + Y1*Y2),
	c = X1*X1 + Y1*Y1 - r*r - player_r*player_r;
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

void Bullet::move(){ //每帧移动 
	this->x += Qcos(angle)*velocity;
	this->y += Qsin(angle)*velocity;
}

virtual void Bullet::show(){ //显示 
	this->picture.rotate_show(window_renderer,x,y,angle); 
	//window_render为全局变量，窗口 
}

Bullet::~Bullet(){ //析构函数 自我销毁
	delete this;
}
