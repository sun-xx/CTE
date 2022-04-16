#ifndef SDL_RENDER_HPP_INCLUDED
#define SDL_RENDER_HPP_INCLUDED

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<functional>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
using namespace std;



class Windows//窗体
{
protected:
    SDL_Window* win;
    int x,y,width,height;//窗体左上角坐标，宽，高
    Uint32 flags;//窗体特征
    SDL_Event evt;
    map<Uint32,function<void(SDL_Event)>> callbacks;
    bool isquit;
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
    void add_event(Uint32 type,function<void(SDL_Event)> func);
    void del_event(Uint32 type);
    SDL_Event get_event_info();
    void show();
    void hide();
};



class Renderer//渲染器
{
protected:
    SDL_Renderer* ren;
    int width,height;
    SDL_Rect view_port;
public:
    Renderer(SDL_Window* win,Uint32 flags);//flags,指定渲染器的模式
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
    void load_tex(SDL_Texture* b_tex);
    //void load_tex(string pic);
    ~Texture();
    void rotate_show(Renderer renderer,float center_pos_x,float center_pos_y,double angle);//将纹理旋转一定角度显示
    void flip_show(Renderer renderer,SDL_RendererFlip flags);//将纹理按某一方向翻转显示
    void show(SDL_Renderer* render);//正常显示
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
public:
    Timer(int fps);
    void setfps(int fps);//设定控制的fps
    void ctrlfps();//进行控制
    int get_lframe_time();//获取上一帧所用时间
    void start_time();
};





class Mixer//音频
{
protected:
    vector<Mix_Music*> bgm;//背景音乐
    vector<Mix_Chunk*> sound_effect;//特效音乐
public:
    Mixer(vector<string> bgms,vector<string> sound_effects);
    ~Mixer();
    void play_bgm(Mix_Music* music,int loops);//loops,播放次数，-1为无限次
    void play_soundeffect(Mix_Chunk* effect,int loops);

};





extern bool SDL_all_init();
extern bool SDL_all_quit();
extern void sdl_load_all_pics(vector<string> pics,vector<SDL_Texture*>* tex,SDL_Renderer* render);//预加载所有可能用到的图片素材


#endif // SDL_RENDER_HPP_INCLUDED
