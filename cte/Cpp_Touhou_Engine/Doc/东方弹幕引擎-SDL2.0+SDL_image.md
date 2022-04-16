东方弹幕引擎-SDL2.0+SDL_image



思路：

1.touhou对象 ---------------------------------------游戏整体

2.menu对象----------------------------------------主菜单，难度，自机选择；进关卡后侧面显示残机，bomb等

3.entity对象->player，boss，enemy-----------------------------------------游戏中可被操控（人或对象自身）的对象

4.item对象->bullet，Power，point;bullet->laser---------------------------------------子弹，掉落物。特殊物品等

5.dialog对象----------------------------------剧情对话，结尾段剧情

6.Stage对象-------------------------------每一关



```C++
class touhou
{
    public:
    	touhou()
    public:
    	void start()//调用menu开始界面，选择难度，自机
        void stage_change()
        void end()//制作者感谢名单
        void run()//傻瓜式开始游戏
        
}


class menu
{
    public
        
}
```



```C++
tuple<Stage1,Stage2,...> st(s1,s2,...);
player ply;
menu m;
touhou th(st,ply,m);
    
    
    
class Stage1:public Stage
{
    ...
    void run()// which is virtual in the base class 'Stage'
    {
        ...
    }
}
...
    
class bullet1:public bullet
{
    ...
}
class laser1:public laser
{
    ...
}

```



