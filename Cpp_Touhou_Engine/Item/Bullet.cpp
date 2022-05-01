//By @Sun-XX

#include "Item.hpp"

Bullet::Bullet(vector<Texture> pic,int width,int height,float init_x,float init_y,float r_){
	/* ���캯����ʵ�֡���־��Ǽ�����ֵ */
	this->pictures = pic;
	this->width = w; this->height = h; //��ͼ���� 
	
	this->x = init_x; this->y = init_y; //��ʼ���� 
	this->temp_x = this->x; this->temp_y = this->y; //��ʼ���껺��������ͳһ
	this->angle = 0; this->a_angle = 0; //��ʼ����
	this->velocity = 0; this->a_velocity = 0; //��ʼ�ٶ�
	this->r = r_; //�ж��뾶 
	
	this->alive = true; //�ӵ����  
	this->flash = 0; //������ʱ֡��Ϊ0 
}

void Bullet::run(){ //ÿ֡�ӵ����� ��׼ģ�� 
	this->flash += 1; //֡������ 
	
	if(this->alive == true){
		this->temp_x = x; this->temp_y = y; //����֡���껺�� ׼����������
		this->angle += this->a_angle;
		this->velocity += this->a_velocity;
	
		this->special_play(); //��Ч
		
		if(hit_player(player_tx,player_ty,player_x,player_y) == true){ //һ֡�������ײ�Ի��������� 
			this->alive = false;
			this->flash = 0; //֡������ 
		} 
	}
	else{ //�ӵ���ײ��
		if(this->flash < 20) //20֡������ʧ��Ч 
			this->die_play();
	}
	this->picture = this->pictures[0];
	this->picture.set_zoom(this->x,this->y,this->width,this->height);
	this->show(); //��ʾ 
}

void Bullet::die_play(){ //Ĭ��������Ч ��С��ʧ 
	if((this->width >= 0.5) && (this->height >= 0.5)){
		this->width -= 0.5;
		this->height -= 0.5;
	}
}

bool Bullet::hit_player(float player_tx,float player_ty,float player_x,float player_y,
						float player_r,float player_velocity){
	//��������&һԪ���η�������ӵ����Ի�һ֡�ڹ켣�Ƿ�����
	//����˳��Ϊ ��һ֡�Ի����꣬��֡�Ի����꣬�Ի��ж��뾶 
	if(get_distance(player_x,player_y,this->x,this->y) >
		(this->velocity + player_velocity + this->r + player_r)){
		//ɸ�����볬���ٶȡ��뾶֮�� ��������ײ 
		return false;
	}
	else{
		float X1,X2,Y1,Y2;
		X1 = temp_x - player_tx; X2 = x - player_x - X1;
		Y1 = temp_y - player_ty; Y2 = y - player_y - Y1;
		float a = X2*X2 + Y2*Y2,
		b = 2*(X1*X2 + Y1*Y2),
		c = X1*X1 + Y1*Y1 - r*r - player_r*player_r;
		float delta = b*b - 4*a*c;
		
		float t1 = (-b + Qsqrt(delta))/(2*a),
		t2 = (-b - Qsqrt(delta))/(2*a);
		
		return delta<0?false:((t1>=0 && t1<=1)||(t2>=0 && t1<=1)); //����һ�����̸��ڷ�Χ�ڼ��ж�����
	}
}

bool Bullet::out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb){
	//�����ж�
	return !(this->x>screen_xl && this->x<screen_xr && this->y>screen_yb && this->y<screen_yt);
	//��������true ��֮����false
}

void Bullet::move(){ //ÿ֡�ƶ� 
	this->x += Qcos(angle)*velocity;
	this->y += Qsin(angle)*velocity;
}

void Bullet::show(){ //��ʾ 
	this->picture.rotate_show(window_renderer,this->x,this->y,angle); 
	//window_renderΪȫ�ֱ��������� 
}

Bullet::~Bullet(){ //�������� ��������
	delete this;
}
