# Render

## Class

·TexPool

·MusPool

·Windows

·Renderer

·Texture

·Timer

·Mixer

## struct

·filters（不用理他你也不会用到）

·Layer(同上)

## function

·bool SDL_all_init

·void SDL_all_quit



------



------

# Class

## TexPool

​	TexPool()//空构造函数

​	TexPool(json js,SDL_Renderer* render)//js：描述所有需要用的图片的nlohmann::json对象，render：指定SDL_Renderer*

​	void loadpic(json js,SDL_Renderer* render)//参数，功能跟构造函数2一样

​	SDL_Texture* get_tex(string name)//通过在.json文件中的键来获取SDL_Texture*

## MusPool

```C++
MusPool();
MusPool(json js);//js同上
void loadmus(json js);
Mix_Music* get_bgm(string name);//类比TexPool
Mix_Chunk* get_sdeffect(string name);
```



## Windows

​	

```C++
	Windows(string title,int x_,int y_,int width_,int height_,Uint32 flags_)
	//title:窗口标题，后四个参数分别为左上角坐标，长，宽，flags_：创建窗口时的标志，见SDL_wiki
​	SDL_Window* get_window()
	//获得SDL_Window*
​	void get_window_size()
	//获取当前窗口的大小并存储到对象内
​	Uint32 get_window_flags()
	//获得窗口的标志
​	int win_width()
	//获得窗口的长
​	int win_height()
	//获得窗口的宽
​	void Poll_event()
	//处理事件，每帧清空消息队列
​	void bind_event(Uint32 type,function<void(SDL_Event)> func)
	//将某一事件与一个回调函数相关联
​	void unbind_event(Uint32 type)
	//解关联
​	SDL_Event get_event_info()
	//获取当前事件的详细信息
​	void show()
	//显示窗口
​	void hide()
	//隐藏窗口
​	Uint32 register_event()
	//注册一个自定义事件，返回事件的ID
​	int raise_event(Uint32 id)
	//产生一个不带有数据的“标志”事件（scratch的广播消息）
​	int push_event(SDL_Event* event)
	//将带数据的消息加入消息队列
​	void set_ignore(Uint32 type,bool is_permanent)
	//设置需要忽略的事件id，is_permanent:true->永久忽略该消息；false->在需要忽略该消息时手动调用ignore_event()
​	void ignore_event()
	//忽略非永久忽略消息
​	void del_ignore(Uint32 type)
    //取消忽略某一类型的消息
```

## Renderer

```C++
Renderer(SDL_Window* win,Uint32 flags);//flags,指定渲染器的模式
~Renderer();
void clear();//清空渲染器（以黑色覆盖）
void present();//在屏幕上绘制
void get_render_size();//获取可绘制区域的大小
int rwidth();//可绘制区域长
int rheight();//可绘制区域宽
void set_view_port(SDL_Rect* vp);//设置Renderer视窗（见SDL官网）
void set_view_port(int x,int y,int width,int height);//就是把上面的参数拆开来
SDL_Rect get_view_port();//获取视窗大小
SDL_Renderer* render();//获取SDL_Renderer*
```

## Texture

```C++
Texture(SDL_Texture* tex_,SDL_Renderer* render);
void load_tex(SDL_Texture* b_tex);//重新加载纹理
void rotate_show(Renderer& renderer,float center_pos_x,float center_pos_y,double angle,int priority);//将纹理旋转一定角度显示,priority表示第几图层，数值越小（必须大于0），图层越在上方
void flip_show(Renderer& renderer,SDL_RendererFlip flags,int priority);//将纹理按某一方向翻转显示
void show(Renderer& render,int priority);//正常显示
void set_source(int x,int y, int width, int height);//设置将被绘制的纹理部分
void set_source(SDL_Rect* frect);
void set_zoom(float x,float y,float width,float height);//设置绘制的位置，大小
void set_zoom(SDL_FRect* frect);
SDL_Rect get_source();//获取当前将被绘制的纹理部分
SDL_FRect get_zoom();//获取当前将被绘制到的位置，大小
SDL_Texture* get_tex();//获取SDL_Texture*
//显示在渲染器上，非屏幕
void get_params(Uint32* format,int* access, int* w, int *h);//获取纹理信息,见SDL_wiki
```

## Timer

```C++
Timer(int fps);//fps:帧率
void init(int fps);//同上
void setfps(int fps);//设定控制的fps
void ctrlfps();//进行控制，必须在帧循环最后调用
int get_lframe_time();//获取上一帧所用时间
void start_time();//开始该帧的计时，必须在帧循环一开始调用
void after(unsigned int frames,function<void(std::any)>& timer_callback,std::any params);
//从调用after时的帧数算起，frames帧后执行回调函数
//IMPORTANT:在回调函数中获取参数的值时请使用std::any_cast<T>
```

## Mixer

```C++
Mixer(int b_volume,int sd_volume);//b_volume:背景音乐音量，sd_volume:音效音量
Mixer();//一个形式上的玩意，记得后面使用init初始化
void init(int b_volume,int sd_volume);//同上
void play_bgm(Mix_Music* music,int loops);//loops,播放次数，-1为无限次
void play_sdeffect(Mix_Chunk* effect,int loops);//同上

void pause_bgm();//暂停背景音乐
void pause_all();//暂停所有正在播放的channel(bgm+音效)
void resume_bgm();//恢复播放背景音乐
void resume_all();//恢复播放所有channel
void set_bgm_volume(int volume);//设置背景音乐音量
void set_sdeffect_volume(Mix_Chunk* chunk,int volume);//设置某一种音效的音量，chunk：指定的音效
```

# Function

```
bool SDL_all_init();//将SDL彻底初始化，在程序的一开始必须被调用
void SDL_all_quit();//将SDL完全退出，程序的最后必须调用
```

