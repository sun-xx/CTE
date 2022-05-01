//By @Sun-XX

#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

//独立物体定义 

class Entity{
	/*物体基类*/
protected:
	/*---------------Variables---------------*/
	vector<Texture> pictures; //贴图集 
	Texture picture; //当前贴图
	int width,height; //贴图大小
	
	float x,y; float temp_x,temp_y; //坐标与坐标缓存
	float angle,a_angle; //角度与角速度
	float velocity,a_velocity; //速度与加速度
	float r; //物体半径
	int flash; //存在帧数
	bool alive; //是否存在 
	
	/*---------------Functions---------------*/
	void move(); //移动
	virtual void show(); //显示 可自定义
	
	virtual void special_play(); //特殊演出
	virtual void die_play(); //消失特效

public:
	Entity(vector<Texture> pics,int w,int h,float init_x,float init_y,float r); //构造函数
	virtual ~Entity(); //析构函数 自我销毁
	
	virtual void run(); //每帧演出 用户自定义 
	 
};


class Enemy:public Entity{
	/*杂鱼类*/
protected:
	bool hit_player(float player_tx,player_ty,float player_x,float player_y,
					float player_r,float player_velocity);
	//判断一帧内是否碰撞自机 传入参数：上一帧自机坐标 这一帧自机坐标 自机判定半径与速度
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb);
	//判断是否出屏 参数为屏幕左侧-右侧-上侧-下侧
	
	virtual void release_bullet(); //每帧执行一次 自定义发弹脚本

public:
	using Entity::Entity;
	
};

class Player:public Entity{
	/*自机类*/
protected:
	/*---------------Variables---------------*/ 
	bool slow_mode; //是否低速模式 
	bool shooting; //是否射击
	bool in_protect; //是否处于无敌 
	
	/*---------------Functions---------------*/
	virtual void shoot(); //射击
	virtual void bomb(); //自机符卡释放

public:
	using Entity::Entity; 
	
};


class Boss:public Entity{
	/*BOSS类*/
protected:
	vector<Spellcard> sc; //使用符卡
	 
	int hp; //血量 
	bool in_protect; //处于无敌状态 
	
public:
	using Entity::Entity;
	
};

#endif //ENTITY_HPP_INCLUDED
