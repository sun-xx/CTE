//By @Sun-XX

/*
Bullet��Դ���롣
���������������ӵ���ʵ�֣�Ц��
���಻��ȥ�� 
*/

#include "Item.hpp"

//ʵ��˳��Ϊ�����캯��-�ݳ�-��ײ-����-�ƶ�-��ʾ-�������� 

Bullet::Bullet(Texture pic,int w,int h,float init_x,float init_y,float r_){
	/* ���캯����ʵ�֡���־��Ǽ�����ֵ */
	this->picture = pic;
	this->width = w; this->height = h; //��ͼ���� 
	
	this->x = init_x; this->y = init_y; //��ʼ���� 
	this->temp_x = this->x; this->temp_y = this->y;
	this->r = r_;
	
	this->alive = 1; //�ӵ����  
	this->angle = 0; this->a_angle = 0; //��ʼ����
	this->speed = 0; this->a_speed = 0;
	this->flash = 0; 
	this->temp_flash = 0;
}

void Bullet::run(){ //ÿ֡�ӵ����� 
	this->flash += 1; //֡������ 
	
	if(this->alive == true){
		this->temp_x = x; this->temp_y = y; //����֡���껺�� ׼����������
		this->angle += this->a_angle;
		this->speed += this->a_speed;
	
		special_play(); //��Ч
		
		if(hit_player(player_tx,player_ty,player_x,player_y) == true){ //һ֡�������ײ�Ի��������� 
			this->alive = false;
			this->temp_flash = this->flash;
		} 
	}
	else{ //�ӵ���ײ�� 
		if((this->flash - this->temp_flash) < 15) //15f��ִ����ʧ��Ч 
			this->die_play(); //��ʧ��Ч
		else //15f������ɾ�� 
			delete this;
	}
	this->show();
}

bool Bullet::hit_player(int player_tx,int player_ty,int player_x,int player_y,float player_r){
	//��������&һԪ���η�������ӵ����Ի�һ֡�ڹ켣�Ƿ����� 
	int X1,X2,Y1,Y2;
	X1 = temp_x - player_tx; X2 = x - player_x - X1;
	Y1 = temp_y - player_ty; Y2 = y - player_y - Y1;
	int a = X2^2 + Y2^2,
	b = 2*(X1*X2 + Y1*Y2);
	float c = X1*X1 + Y1*Y1 - r*r - player_r*player_r;
	float delta = b*b - 4*a*c;
	
	float t1 = (-b + Qsqrt(delta))/(2*a),
	t2 = (-b - Qsqrt(delta))/(2*a);
	
	return delta<0?false:((t1>=0 && t1<=1)||(t2>=0 && t1<=1)); //����һ�����̸��ڷ�Χ�ڼ��ж����� 
}

bool Bullet::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//�����ж�
	return !(x>screen_xl && x<screen_xr && y>screen_yb && y<screen_yt);
	//��������true ��֮����false
}

void Bullet::move(){
	this->x += Qcos(angle)*speed;
	this->y += Qsin(angle)*speed; 
}

void Bullet::show(){ //��ʾ 
	this->picture.rotate_show(window_renderer,x,y,angle); 
	//window_renderΪȫ�ֱ��������� 
}

Bullet::~Bullet(){
	delete this;
}
