//By @Sun-XX

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

class Bullet{
/* 单个子弹的类 包括了子弹的常规演出和通性 */
protected: //访问限制的各种基本属性 
	//---------------Variables---------------//
	vector<Texture> pictures; //贴图
	Texture picture; //当前贴图 
	int width,height; //大小 
	
	float x,y; //位置坐标
	float temp_x,temp_y; //坐标缓存
	float angle,a_angle; //单帧角度与角速度 
	float velocity,a_velocity; //单帧速度与加速度 
	float r; //子弹判定半径 
	int flash; //子弹演出帧数
	bool alive; //是否存活 
	
	//---------------Functions---------------//
	virtual void special_play();
	//基类中不实现 特殊演出 由用户自定义 每一类子弹派生一类
	virtual void die_play();
	//同上 消弹特效 注意是每帧执行一次
	void move(); //移动 参数为移动方向与移动距离
	virtual void show(); //显示 提供一般实现 可自定义 
	
	//以下为常规检测 
	bool hit_player(float player_tx,float player_ty,float player_x,float player_y,float player_r,
	float player_velocity);
	//上为判断一帧内是否碰撞自机
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//上为判断是否出屏 注意传入顺序为屏幕左侧x坐标-右侧x坐标-上方y坐标-下方y坐标
	//More methods to be coded... 
		
public: //允许调用的子弹类方法
	Bullet(vector<Texture> pic,int w,int h,float init_x,float init_y,float r_);
	//构造函数，参数为图片，宽，高，初始坐标，判定半径 
	~Bullet(); //析构函数 
	
	virtual void run(); //子弹每帧演出 包含默认实现 可由用户自定义 
};


class Rewards{ 
/* 得点或残雷碎片等奖励物品的类 */
protected: //未加注释同上
	//---------------Variables---------------//
	Texture picture;
	int width,height;
	
	float x,y; //坐标 
	float angle,a_angle; //角度与角速度
	float velocity,a_velocity; //速度与加速度 
	int flash; //存在帧数 
	bool alive; //是否存活 
	bool been_got; //被拾取 
	
	//---------------Functions---------------//
	bool near_player(float player_x,float player_y,float min_distance); //是否接近自机 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //判断出屏 
	//More methods to be coded...
	
public:
	Rewards(Texture pic,int w,int h,float init_x,float init_y);
	//构造函数，参数为图片，宽，高，初始坐标
	~Rewards(); //析构函数
	
	virtual void run(); //掉落物每帧演出 由用户自定义效果 
};

#endif // ITEM_HPP_INCLUDED
