//comment because test sdl_render



/*

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
#include <string>
#include "../Qcalc.hpp"

class Item{
protected:
    SDL_Texture* picture;
    bool living; //�����Ƿ����
    double x,y; //��������λ��
    long flash; //�����Ѵ���֡��
    int size_x,size_y;//�����С(���������)

public:
    Item(SDL_Surface* pic,double x_,double y_,long fl);//���캯��
    //void playing(double player_pos_x,double player_pos_y,int get_point_line,short t);
    virtual void special();//�����ݳ�
    void show(SDL_Renderer* renderer);//��ʾ�����ƣ��ö���
    void run(); //ͨ������֡������Item
    bool out_of_screen(int left_x,int right_x,int top_y,int bottom_y);
    double return_distance(double target_x,double target_y); //�����������
    ~Item();//��������
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
	short type; //������
	int num; //Я����Դ����
	int direction; //�ƶ�����
	bool state; //״̬
public:
    virtual void special(double player_pos_x,double player_pos_y);
	int move(short speed); //�ƶ�
	void playing(double player_pos_x,double player_pos_y,int get_point_line,short t); //����Դ���ƶ��켣
};

int Point::move(short speed){
	x += cos(direction)*speed;
	y += sin(direction)*speed;
}

void Point::playing(double player_pos_x,double player_pos_y,int get_point_line,short t){
	direction = rand()%90-45; //�����ʼ����ʱ����
	if(flash == 1){ //��ʼ��
		state = 0;
		type = t;
		switch(type){
			case 1:
				//P��
				break;
			case 2:
				//����
				break;
			//������������
		}
	}
	if(flash <= 7){ //������Ч
		move(7-flash);
	}
	else{ //����
		y -= 5;
	}
	if((fabs(player_pos_x - x)<30 && fabs(player_pos_y - y)<30)||
	player_pos_y > get_point_line ){ //���Ի�x��y��С��30�������򴥷��յ�
		state = 1; //��������״̬Ϊ���յ�
	}
	living = out_of_screen();//��Ļ����
	if(state == 1) special();
}

void Point::special(double player_pos_x,double player_pos_y){ //��д�����ݳ� ���յ� ���е��Ի�
	direction = atan2((player_pos_y - y),(player_pos_x - x));
	move(15);
	if(return_distance(player_pos_x,player_pos_y)<5)
		living = 0;
}

class Bullet:public Item{
private:
	void follow_trace();//���ղ������������켣�˶�
};

#endif // ITEM_HPP_INCLUDED

*/
