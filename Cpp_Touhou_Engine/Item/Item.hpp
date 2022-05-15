//By @Sun-XX

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
#include<bits/stdc++.h>
#include "../Renderer/sdl_render.hpp"
using namespace std;
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
	virtual void special_play()=0;
	//基类中不实现 特殊演出 由用户自定义 每一类子弹派生一类
	virtual void die_play();
	//同上 消弹特效 注意是每帧执行一次
	void move(); //移动
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
	virtual ~Bullet(); //析构函数

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
	virtual bool if_to_be_got(float player_x,float player_y,float min_distance,
								float min_y,int special_condition)=0;
	//是否被拾取 传入自机坐标 靠近自机最小判定距离 上线位置
	//可另行增加条件 无则传入-1 否则传入条件表达式 范例：(Signal > 1)（地灵殿信号系统）
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //判断出屏
	//More methods to be coded...

public:
	Rewards(Texture pic,int w,int h,float init_x,float init_y);
	//构造函数，参数为图片，宽，高，初始坐标
	virtual ~Rewards(); //析构函数 分数增加系统由用户自定义

	virtual void run()=0; //掉落物每帧演出 由用户自定义效果
};


class Laser{
/*
 * 有关激光的原理。
 * 用多个节点储存一整条激光，就好比一连串弹幕。
 * 整条激光粗细均匀变化，例如：
 * 从(0,0)粗细为0的节点渲染到(10,0)粗细为20的节点
 * 激光粗细则为 y=2x(x<10)
 * 激光的运动，则视为所有节点的运动。为了减少运算量，等价为插入头部节点，删除尾部节点。
 * 速度则由控制每次插入或删除的节点数量实现。长短则由插入和删除的节点数量差实现。
 * 例：头/尾部插入/删除两个节点比一个运动更快 头部不插入尾部删除则能实现类似E/N难度芳香终符激光效果。
 * 激光与自机的碰撞判定，仍用一元二次方程动圆正交，但由于粗细不均，方程中r则改变为r+t(R-r)
 * 即原理上视作某节点移动到了（靠近头部方向的）前一个节点，并移动过程中粗细匀速变化
 */
protected:
	//---------------Variables---------------//
	vector<float> x_pos; //节点x坐标
	vector<float> y_pos; //节点y坐标
	vector<float> size; //节点大小

	float temp_x_head,temp_y_head; //头部节点坐标缓存
	float temp_x_tail,temp_y_tail; //尾部节点坐标缓存

	float angle,a_angle; //角度与角速度
	float head_velocity,tail_velocity; //激光头尾移动速度
	float a_head_velocity,a_tail_velocity; //激光头尾加速度

	int flash; //存在帧数
	bool alive; //激光是否存在

	//---------------Functions---------------//
	virtual void special_play(); //特殊演出 用户重写
	void move(); //移动
	virtual void show(); //显示 提供一般实现 可自定义

	bool hit_player(); //检测碰撞自机
	bool out_of_screen(int screen_xl,int screen_xr,int screen_yt,int screen_yb); //判断出屏

public:
	Laser(float init_x,float init_y,int length); //传入初始坐标与长度（节点数量）
	virtual ~Laser();

	virtual void run(); //运行

};


#endif // ITEM_HPP_INCLUDED
