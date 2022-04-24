//By @Sun-XX

/*
Item��Դ���롣
�������棬�Ǿ�����������������Ļ����Ķ���ĸо��ء�����Ц��
ʵ�֣�ÿһ������ᵥ���Ŀ�һ���ļ��ġ���Ȼ��һ�������������ˡ�
�����ӵ�������Դ�㰡�����ֶ�����ȥ�������ۻ��Ķ������� 
*/

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

class Bullet{
/* �����ӵ����� �������ӵ��ĳ����ݳ���ͨ�� */
protected: //�������Ƶĸ��ֻ������� 
	//---------------Variables---------------//
	Texture picture; //��ͼ
	int width,height; //��Ӿ��δ�С 
	
	float x,y; //λ������
	float temp_x,temp_y; //���껺��
	float angle,a_angle; //��֡�Ƕ�����ٶ� 
	float speed,a_speed; //��֡�ٶ�����ٶ� 
	float r; //�ӵ��ж��뾶 
	int flash; //�ӵ��ݳ�֡��
	int temp_flash; //��ײ��ʱ֡�� 
	bool alive; //�Ƿ��� 
	
	//---------------Functions---------------//
	virtual void special_play();
	//�����в�ʵ�� �����ݳ� ���û��Զ��� ÿһ���ӵ�����һ�� ֻ����д�÷������� 
	virtual void die_play();
	//ͬ�� ������Ч ע����ÿִ֡��һ�� ���ӵ���ʧ������ ֡��Ϊflash-temp_flash 
	void move(); //�ƶ� ����Ϊ�ƶ��������ƶ�����
	void show(); //��ʾ 
	
	//����Ϊ������ 
	bool hit_player(int player_tx,int player_ty,int player_x,int player_y,float player_r);
	//��Ϊ�ж�һ֡���Ƿ���ײ�Ի� ע�⴫��˳��Ϊ�ȴ���һ֡�Ի����� �ٴ���һ֡�Ի����� 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//��Ϊ�ж��Ƿ���� ע�⴫��˳��Ϊ��Ļ���x����-�Ҳ�x����-�Ϸ�y����-�·�y����
	//More methods to be coded... 
		
public: //������õ��ӵ��෽��
	Bullet(Texture pic,int w,int h,float init_x,float init_y,float r_);
	//���캯��������ΪͼƬ�����ߣ���ʼ���꣬�ж��뾶 
	~Bullet(); //�������� 
	
	void run(); //�ӵ�ÿ֡�ݳ� 
};


class Rewards{ 
/* �õ�������Ƭ�Ƚ�����Ʒ���� */
protected: //δ��ע��ͬ��
	//---------------Variables---------------//
	Texture picture;
	int width,height;
	
	int x,y;
	int init_direction,init_speed; //��Ʒ����ʱ��ʼ�˶��������ٶ� 20f��Ч�ݳ�ʱ��
	int flash;
	bool been_got; //����ȡ 
	
	//---------------Functions---------------//
	bool near_player(int player_x,int player_y); //�Ƿ�ӽ��Ի� 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	void slide_to_player(int player_x,int player_y); //���Ի�ʰȡ
	//More methods to be coded...
	
public:
	Rewards(Texture pic,int w,int h,int init_x,int init_y,int drc,int spd);
	//���캯��������ΪͼƬ�����ߣ���ʼ���꣬���Ƕȣ����ٶ�
	~Rewards(); //��������
	
	void run(); //������Ʒÿ֡�ݳ� 
};

#endif // ITEM_HPP_INCLUDED
