//by @dynamder
#ifndef SDL_RENDER_HPP_INCLUDED
#define SDL_RENDER_HPP_INCLUDED

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<functional>
#include<queue>
#include<list>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;

class TexPool
{
protected:
    json pic_source;
    map<string,int> pindex;
    vector<SDL_Texture*> pool;
public:
    TexPool();
    TexPool(json js,SDL_Renderer* render);
    ~TexPool();
    void loadpic(json js,SDL_Renderer* render);
    SDL_Texture* get_tex(string name);
};

struct filters
{
    map<Uint32,int> p_filtered_event;
    map<Uint32,int> t_filtered_event;
};

class Windows//窗体
{
protected:
    SDL_Window* win;
    int x,y,width,height;//窗体左上角坐标，宽，高
    Uint32 flags;//窗体特征
    SDL_Event evt;
    map<Uint32,function<void(SDL_Event)>& > callbacks;
    bool isquit;
    vector<SDL_Event> flag_event;
    //map<Uint32,int> p_filtered_event;
    //map<Uint32,int> t_filtered_event;
    filters fil_event;
    static int SDLCALL p_do_filter(void *userdata, SDL_Event * event)//invalid use of member in static member function
    {
        filters* tmp=(filters*)userdata;
        if(tmp->p_filtered_event.find(event->type)!=tmp->p_filtered_event.end())
        {
            return 0;
        }
        else return 1;
    };
    static int SDLCALL t_do_filter(void *userdata, SDL_Event * event)
    {
        filters* tmp=(filters*)userdata;
        if(tmp->t_filtered_event.find(event->type)!=tmp->t_filtered_event.end())
        {
            return 0;
        }
        else return 1;
    }
public:
    Windows(string title,int x_,int y_,int width_,int height_,Uint32 flags_);//flags,指定窗体的模式
    ~Windows();
    SDL_Window* get_window();
    void get_window_size();//获取窗体的大小
    //void get_render_size();
    Uint32 get_window_flags();
    int win_width();
    int win_height();
    void Poll_event();
    void bind_event(Uint32 type,function<void(SDL_Event)>& func);
    void unbind_event(Uint32 type);
    SDL_Event get_event_info();
    void show();
    void hide();

    //////////////////////////
    Uint32 register_event();
    int raise_event(Uint32 id);//只能产生不带数据的“标志”消息
    int push_event(SDL_Event* event);//带数据的消息
    void set_ignore(Uint32 type,bool is_permanent);//设置需要被忽略的消息，is_permanent=0:但不立刻忽略,is_permanent=1:永久性的忽略该种类消息
    void ignore_event();//将当前消息队列中的设置过的忽略信息全部忽略
    void del_ignore(Uint32 type);
    /////////////////////////////////////////////////////////////////////
};




struct Layer
{
    Layer()
    {
        render=NULL;
        tex=NULL;
        srect=NULL;
        target=NULL;
        angle=0;
        coord=NULL;
    };
    //vector<std::any> params;
    SDL_Renderer* render;
    SDL_Texture* tex;
    SDL_Rect* srect;
    SDL_FRect* target;
    double angle;
    SDL_FPoint* coord;
    SDL_RendererFlip flags;
};



class Renderer//渲染器
{
protected:
    SDL_Renderer* ren;
    int width,height;
    SDL_Rect view_port;

    vector<list<Layer> > rendertable;
public:
    Renderer(SDL_Window* win,Uint32 flags);//flags,指定渲染器的模式
    void init(SDL_Window* win,Uint32 flags);
    Renderer(){};
    ~Renderer();
    void clear();//清空渲染器（以黑色覆盖）
    void present();//在屏幕上绘制
    void get_render_size();//获取可绘制区域的大小
    int rwidth();
    int rheight();
    void set_view_port(SDL_Rect* vp);
    void set_view_port(int x,int y,int width,int height);
    SDL_Rect get_view_port();
    SDL_Renderer* render();

    void push_ren(Layer layer,int priority);
};

class Texture//图片素材（以下对纹理的操作变换仅在显示时，不直接改变纹理）
{
protected:
    SDL_Texture* tex;
    int width,height;//纹理的宽，高
    SDL_FRect zoom;//source，选取纹理的某一部分，zoom，纹理缩放
    SDL_Rect source;
    unsigned char alpha;
public:
    //Texture(string pics,SDL_Renderer* render);
    Texture(SDL_Texture* tex_,SDL_Renderer* render);
    Texture() {};
    void load_tex(SDL_Texture* b_tex);
    //void load_tex(string pic);
    ~Texture();
    void rotate_show(Renderer& render,float center_pos_x,float center_pos_y,double angle,int priority);//将纹理旋转一定角度显示
    void flip_show(Renderer& render,SDL_RendererFlip flags,int priority);//将纹理按某一方向翻转显示
    void show(Renderer& render,int priority);//正常显示
    void set_source(int x,int y, int width, int height);
    void set_source(SDL_Rect* frect);
    void set_zoom(float x,float y,float width,float height);
    void set_zoom(SDL_FRect* frect);
    SDL_Rect get_source();
    SDL_FRect get_zoom();
    SDL_Texture* get_tex();
    //显示在渲染器上，非屏幕
    void get_params(Uint32* format,int* access, int* w, int *h);//获取纹理信息
};








class Timer//定时器，控制帧率
{
protected:
    int tick_per_frame;
    int fps;
    int last_frame_time;//上一帧所用时间
    int start_tick;
    unsigned int T_frames;//总帧数
    map<unsigned int,queue<pair<function<void(std::any)>&,std::any> > >calltable;
    void caller();
    void ascendframe();
public:
    Timer(int fps);
    void init(int fps);
    void setfps(int fps);//设定控制的fps
    void ctrlfps();//进行控制
    int get_lframe_time();//获取上一帧所用时间
    void start_time();
    void after(unsigned int frames,function<void(std::any)>& timer_callback,std::any params);
};



class MusPool
{
protected:
    json mus_source;
    map<string,int> mindex_b;
    map<string,int> mindex_e;
    vector<Mix_Music*> pool_bgm;//背景音乐池
    vector<Mix_Chunk*> pool_sdeffect;//特效音乐池
    void from_json(const json& j,MusPool& mp);
public:
    MusPool();
    MusPool(json js);
    ~MusPool();
    void loadmus(json js);
    Mix_Music* get_bgm(string name);
    Mix_Chunk* get_sdeffect(string name);
    void debug_muspool();
};


class Mixer//音频
{
protected:
    int bgm_volume;
    int sdeffect_volume;
public:
    Mixer(int b_volume,int sd_volume);
    Mixer();
    void init(int b_volume,int sd_volume);
    ~Mixer();
    void play_bgm(Mix_Music* music,int loops);//loops,播放次数，-1为无限次
    void play_sdeffect(Mix_Chunk* effect,int loops);
/////////////////////////////////////////////////////////////////////////////
    void pause_bgm();
    void pause_all();
    void resume_bgm();
    void resume_all();
    void set_bgm_volume(int volume);
    void set_sdeffect_volume(int volume);
    void quit();
    ///////////////////////////////////////////////////////to be tested
};





extern bool SDL_all_init();
extern void SDL_all_quit();



#endif // SDL_RENDER_HPP_INCLUDED
