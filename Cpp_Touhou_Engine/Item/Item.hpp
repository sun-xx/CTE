//By @Sun-XX

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
#include<bits/stdc++.h>
#include "../Renderer/sdl_render.hpp"
using namespace std;
class Bullet{
/* �����ӵ����� �������ӵ��ĳ����ݳ���ͨ�� */
protected: //�������Ƶĸ��ֻ�������
	//---------------Variables---------------//
	vector<Texture> pictures; //��ͼ
	Texture picture; //��ǰ��ͼ
	int width,height; //��С

	float x,y; //λ������
	float temp_x,temp_y; //���껺��
	float angle,a_angle; //��֡�Ƕ�����ٶ�
	float velocity,a_velocity; //��֡�ٶ�����ٶ�
	float r; //�ӵ��ж��뾶
	int flash; //�ӵ��ݳ�֡��
	bool alive; //�Ƿ���

	//---------------Functions---------------//
	virtual void special_play()=0;
	//�����в�ʵ�� �����ݳ� ���û��Զ��� ÿһ���ӵ�����һ��
	virtual void die_play();
	//ͬ�� ������Ч ע����ÿִ֡��һ��
	void move(); //�ƶ�
	virtual void show(); //��ʾ �ṩһ��ʵ�� ���Զ���

	//����Ϊ������
	bool hit_player(float player_tx,float player_ty,float player_x,float player_y,float player_r,
	float player_velocity);
	//��Ϊ�ж�һ֡���Ƿ���ײ�Ի�
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//��Ϊ�ж��Ƿ���� ע�⴫��˳��Ϊ��Ļ���x����-�Ҳ�x����-�Ϸ�y����-�·�y����
	//More methods to be coded...

public: //������õ��ӵ��෽��
	Bullet(vector<Texture> pic,int w,int h,float init_x,float init_y,float r_);
	//���캯��������ΪͼƬ�����ߣ���ʼ���꣬�ж��뾶
	virtual ~Bullet(); //��������

	virtual void run(); //�ӵ�ÿ֡�ݳ� ����Ĭ��ʵ�� �����û��Զ���
};


class Rewards{
/* �õ�������Ƭ�Ƚ�����Ʒ���� */
protected: //δ��ע��ͬ��
	//---------------Variables---------------//
	Texture picture;
	int width,height;

	float x,y; //����
	float angle,a_angle; //�Ƕ�����ٶ�
	float velocity,a_velocity; //�ٶ�����ٶ�
	int flash; //����֡��
	bool alive; //�Ƿ���
	bool been_got; //��ʰȡ

	//---------------Functions---------------//
	virtual bool if_to_be_got(float player_x,float player_y,float min_distance,
								float min_y,int special_condition)=0;
	//�Ƿ�ʰȡ �����Ի����� �����Ի���С�ж����� ����λ��
	//�������������� ������-1 �������������ʽ ������(Signal > 1)��������ź�ϵͳ��
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //�жϳ���
	//More methods to be coded...

public:
	Rewards(Texture pic,int w,int h,float init_x,float init_y);
	//���캯��������ΪͼƬ�����ߣ���ʼ����
	virtual ~Rewards(); //�������� ��������ϵͳ���û��Զ���

	virtual void run()=0; //������ÿ֡�ݳ� ���û��Զ���Ч��
};


class Laser{
/*
 * �йؼ����ԭ��
 * �ö���ڵ㴢��һ�������⣬�ͺñ�һ������Ļ��
 * ���������ϸ���ȱ仯�����磺
 * ��(0,0)��ϸΪ0�Ľڵ���Ⱦ��(10,0)��ϸΪ20�Ľڵ�
 * �����ϸ��Ϊ y=2x(x<10)
 * ������˶�������Ϊ���нڵ���˶���Ϊ�˼������������ȼ�Ϊ����ͷ���ڵ㣬ɾ��β���ڵ㡣
 * �ٶ����ɿ���ÿ�β����ɾ���Ľڵ�����ʵ�֡��������ɲ����ɾ���Ľڵ�������ʵ�֡�
 * ����ͷ/β������/ɾ�������ڵ��һ���˶����� ͷ��������β��ɾ������ʵ������E/N�Ѷȷ����շ�����Ч����
 * �������Ի�����ײ�ж�������һԪ���η��̶�Բ�����������ڴ�ϸ������������r��ı�Ϊr+t(R-r)
 * ��ԭ��������ĳ�ڵ��ƶ����ˣ�����ͷ������ģ�ǰһ���ڵ㣬���ƶ������д�ϸ���ٱ仯
 */
protected:
	//---------------Variables---------------//
	vector<float> x_pos; //�ڵ�x����
	vector<float> y_pos; //�ڵ�y����
	vector<float> size; //�ڵ��С

	float temp_x_head,temp_y_head; //ͷ���ڵ����껺��
	float temp_x_tail,temp_y_tail; //β���ڵ����껺��

	float angle,a_angle; //�Ƕ�����ٶ�
	float head_velocity,tail_velocity; //����ͷβ�ƶ��ٶ�
	float a_head_velocity,a_tail_velocity; //����ͷβ���ٶ�

	int flash; //����֡��
	bool alive; //�����Ƿ����

	//---------------Functions---------------//
	virtual void special_play(); //�����ݳ� �û���д
	void move(); //�ƶ�
	virtual void show(); //��ʾ �ṩһ��ʵ�� ���Զ���

	bool hit_player(); //�����ײ�Ի�
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //�жϳ���

public:
	Laser(float init_x,float init_y,int length); //�����ʼ�����볤�ȣ��ڵ�������
	virtual ~Laser();

	virtual void run(); //����

};


#endif // ITEM_HPP_INCLUDED
