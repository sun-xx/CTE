//By @Sun-XX

/*
Item的源代码。
在这里面，是尽可能做成了囊括屏幕物体的定义的感觉呢……（笑）
实现，每一类物体会单独的开一个文件的。虽然不一定是这样就是了。
单个子弹啊、资源点啊，各种动来动去的让人眼花的东西啊。 
*/

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

class Bullet{
/* 单个子弹的类 包括了子弹的常规演出和通性 */
protected: //访问限制的各种基本属性 
	//---------------Variables---------------//
	Texture picture; //贴图
	int width,height; //外接矩形大小 
	
	float x,y; //位置坐标
	float temp_x,temp_y; //坐标缓存
	float angle,a_angle; //单帧角度与角速度 
	float speed,a_speed; //单帧速度与加速度 
	float r; //子弹判定半径 
	int flash; //子弹演出帧数
	int temp_flash; //被撞击时帧数 
	bool alive; //是否存活 
	
	//---------------Functions---------------//
	virtual void special_play();
	//基类中不实现 特殊演出 由用户自定义 每一类子弹派生一类 只需重写该方法即可 
	virtual void die_play();
	//同上 消弹特效 注意是每帧执行一次 从子弹消失到现在 帧数为flash-temp_flash 
	void move(); //移动 参数为移动方向与移动距离
	void show(); //显示 
	
	//以下为常规检测 
	bool hit_player(int player_tx,int player_ty,int player_x,int player_y,float player_r);
	//上为判断一帧内是否碰撞自机 注意传入顺序为先传上一帧自机坐标 再传这一帧自机坐标 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//上为判断是否出屏 注意传入顺序为屏幕左侧x坐标-右侧x坐标-上方y坐标-下方y坐标
	//More methods to be coded... 
		
public: //允许调用的子弹类方法
	Bullet(Texture pic,int w,int h,float init_x,float init_y,float r_);
	//构造函数，参数为图片，宽，高，初始坐标，判定半径 
	~Bullet(); //析构函数 
	
	void run(); //子弹每帧演出 
};


class Rewards{ 
/* 得点或残雷碎片等奖励物品的类 */
protected: //未加注释同上
	//---------------Variables---------------//
	Texture picture;
	int width,height;
	
	int x,y;
	int init_direction,init_speed; //物品爆出时初始运动方向与速度 20f特效演出时间
	int flash;
	bool been_got; //被收取 
	
	//---------------Functions---------------//
	bool near_player(int player_x,int player_y); //是否接近自机 
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	void slide_to_player(int player_x,int player_y); //被自机拾取
	//More methods to be coded...
	
public:
	Rewards(Texture pic,int w,int h,int init_x,int init_y,int drc,int spd);
	//构造函数，参数为图片，宽，高，初始坐标，初角度，初速度
	~Rewards(); //析构函数
	
	void run(); //奖励物品每帧演出 
};

#endif // ITEM_HPP_INCLUDED
