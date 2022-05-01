//By @Sun-XX

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

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
	virtual void special_play();
	//�����в�ʵ�� �����ݳ� ���û��Զ��� ÿһ���ӵ�����һ��
	virtual void die_play();
	//ͬ�� ������Ч ע����ÿִ֡��һ��
	void move(); //�ƶ� ����Ϊ�ƶ��������ƶ�����
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
	~Bullet(); //�������� 
	
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
	bool near_player(float player_x,float player_y,float min_distance); //�Ƿ�ӽ��Ի� 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //�жϳ��� 
	//More methods to be coded...
	
public:
	Rewards(Texture pic,int w,int h,float init_x,float init_y);
	//���캯��������ΪͼƬ�����ߣ���ʼ����
	~Rewards(); //��������
	
	virtual void run(); //������ÿ֡�ݳ� ���û��Զ���Ч�� 
};

#endif // ITEM_HPP_INCLUDED
