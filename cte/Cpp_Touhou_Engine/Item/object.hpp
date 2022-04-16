//comment because test sdl_render



/*

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
#include <string>
#include "../Qcalc.hpp"

class Item{
protected:
    SDL_Texture* picture;
    bool living; //物体是否存在
    double x,y; //物体坐标位置
    long flash; //物体已存在帧数
    int size_x,size_y;//物体大小(外接正方形)

public:
    Item(SDL_Surface* pic,double x_,double y_,long fl);//构造函数
    //void playing(double player_pos_x,double player_pos_y,int get_point_line,short t);
    virtual void special();//特殊演出
    void show(SDL_Renderer* renderer);//显示（绘制）该对象
    void run(); //通过增加帧数运行Item
    bool out_of_screen(int left_x,int right_x,int top_y,int bottom_y);
    double return_distance(double target_x,double target_y); //计算两点距离
    ~Item();//析构函数
};

Item::Item(SDL_Texture* pic,double x_,double y_,long fl){
	living = 1;
	picture = pic;
	x = x_; y=y_;
	flash = fl;
}

void Item::run(){
	flash += 1;
}

bool Item::out_of_screen(int left_x,int right_x,int top_y,int bottom_y){
	return (x>left_x && x<right_x && y>bottom_y && y<top_y);
}

double Item::return_distance(double target_x,double target_y){
	return Qsqrt((target_x - x)*(target_x-x) + (target_y -y)*(target_y-y));
}

void Item::show(SDL_Renderer* renderer){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=size_x;
    rect.h=size_y;


    SDL_RenderCopy(renderer,picture,NULL,)
	//to be coded...
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
class Point:public Item{
private:
	short type; //红蓝点
	int num; //携带资源数量
	int direction; //移动方向
	bool state; //状态
public:
    virtual void special(double player_pos_x,double player_pos_y);
	int move(short speed); //移动
	void playing(double player_pos_x,double player_pos_y,int get_point_line,short t); //单资源点移动轨迹
};

int Point::move(short speed){
	x += cos(direction)*speed;
	y += sin(direction)*speed;
}

void Point::playing(double player_pos_x,double player_pos_y,int get_point_line,short t){
	direction = rand()%90-45; //随机初始掉落时方向
	if(flash == 1){ //初始化
		state = 0;
		type = t;
		switch(type){
			case 1:
				//P点
				break;
			case 2:
				//蓝点
				break;
			//其它种类掉落点
		}
	}
	if(flash <= 7){ //爆点特效
		move(7-flash);
	}
	else{ //掉落
		y -= 5;
	}
	if((fabs(player_pos_x - x)<30 && fabs(player_pos_y - y)<30)||
	player_pos_y > get_point_line ){ //到自机x，y差小于30或上线则触发收点
		state = 1; //进入特殊状态为被收点
	}
	living = out_of_screen();//屏幕参数
	if(state == 1) special();
}

void Point::special(double player_pos_x,double player_pos_y){ //重写特殊演出 被收点 滑行到自机
	direction = atan2((player_pos_y - y),(player_pos_x - x));
	move(15);
	if(return_distance(player_pos_x,player_pos_y)<5)
		living = 0;
}

class Bullet:public Item{
private:
	void follow_trace();//按照参数方程所定轨迹运动
};

#endif // ITEM_HPP_INCLUDED

*/
