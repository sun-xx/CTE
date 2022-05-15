//By @Sun-XX

#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

//�������嶨�� 

class Entity{
	/*�������*/
protected:
	/*---------------Variables---------------*/
	vector<Texture> pictures; //��ͼ�� 
	Texture picture; //��ǰ��ͼ
	int width,height; //��ͼ��С
	
	float x,y; float temp_x,temp_y; //���������껺��
	float angle,a_angle; //�Ƕ�����ٶ�
	float velocity,a_velocity; //�ٶ�����ٶ�
	float r; //����뾶
	int flash; //����֡��
	bool alive; //�Ƿ���� 
	
	/*---------------Functions---------------*/
	void move(); //�ƶ�
	virtual void show(); //��ʾ ���Զ���
	
	virtual void special_play(); //�����ݳ�
	virtual void die_play(); //��ʧ��Ч

public:
	Entity(vector<Texture> pics,int w,int h,float init_x,float init_y,float r); //���캯��
	virtual ~Entity(); //�������� ��������
	
	virtual void run(); //ÿ֡�ݳ� �û��Զ��� 
	 
};

void Entity::move(){
	this->x += Qcos(angle)*velocity;
	this->y += Qsin(angle)*velocity;
}

void Entity::show(){
	this->picture.rotate_show(window_renderer,this->x,this->y,angle); 
	//window_renderΪȫ�ֱ��������� 
}


class Enemy:public Entity{
	/*������*/
protected:
	bool hit_player(float player_tx,float player_ty,float player_x,float player_y,
					float player_r,float player_velocity);
	//�ж�һ֡���Ƿ���ײ�Ի� �����������һ֡�Ի����� ��һ֡�Ի����� �Ի��ж��뾶���ٶ�
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//�ж��Ƿ���� ����Ϊ��Ļ���-�Ҳ�-�ϲ�-�²�
	
	virtual void release_bullet(); //ÿִ֡��һ�� �Զ��巢���ű�

public:
	using Entity::Entity;
	
};

class Player:public Entity{
	/*�Ի���*/
protected:
	/*---------------Variables---------------*/ 
	bool slow_mode; //�Ƿ����ģʽ 
	bool shooting; //�Ƿ����
	vector<int> powers; //ÿ�ɻ��� 
	bool hit; //�Ƿ��ڱ���״̬(�Ƿ�ɾ���) 
	bool in_protect; //�Ƿ����޵� 
	int die_bomb_time; //����ʱ�� 
	
	/*---------------Functions---------------*/
	virtual void shoot(); //���
	virtual void bomb(); //�Ի������ͷ�
	void control(); //�ٿ��Ի� 

public:
	using Entity::Entity; 
	
};


class Boss:public Entity{
	/*BOSS��*/
protected:
	vector<Spellcard> sc; //ʹ�÷���
	 
	int hp; //Ѫ�� 
	bool in_protect; //�����޵�״̬ 
	
public:
	using Entity::Entity;
	
};

#endif //ENTITY_HPP_INCLUDED
