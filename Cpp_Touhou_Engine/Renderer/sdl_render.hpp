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

class Windows//����
{
protected:
    SDL_Window* win;
    int x,y,width,height;//�������Ͻ����꣬����
    Uint32 flags;//��������
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
    Windows(string title,int x_,int y_,int width_,int height_,Uint32 flags_);//flags,ָ�������ģʽ
    ~Windows();
    SDL_Window* get_window();
    void get_window_size();//��ȡ����Ĵ�С
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
    int raise_event(Uint32 id);//ֻ�ܲ����������ݵġ���־����Ϣ
    int push_event(SDL_Event* event);//�����ݵ���Ϣ
    void set_ignore(Uint32 type,bool is_permanent);//������Ҫ�����Ե���Ϣ��is_permanent=0:�������̺���,is_permanent=1:�����Եĺ��Ը�������Ϣ
    void ignore_event();//����ǰ��Ϣ�����е����ù��ĺ�����Ϣȫ������
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



class Renderer//��Ⱦ��
{
protected:
    SDL_Renderer* ren;
    int width,height;
    SDL_Rect view_port;

    vector<list<Layer> > rendertable;
public:
    Renderer(SDL_Window* win,Uint32 flags);//flags,ָ����Ⱦ����ģʽ
    void init(SDL_Window* win,Uint32 flags);
    Renderer(){};
    ~Renderer();
    void clear();//�����Ⱦ�����Ժ�ɫ���ǣ�
    void present();//����Ļ�ϻ���
    void get_render_size();//��ȡ�ɻ�������Ĵ�С
    int rwidth();
    int rheight();
    void set_view_port(SDL_Rect* vp);
    void set_view_port(int x,int y,int width,int height);
    SDL_Rect get_view_port();
    SDL_Renderer* render();

    void push_ren(Layer layer,int priority);
};

class Texture//ͼƬ�زģ����¶�����Ĳ����任������ʾʱ����ֱ�Ӹı�����
{
protected:
    SDL_Texture* tex;
    int width,height;//����Ŀ���
    SDL_FRect zoom;//source��ѡȡ�����ĳһ���֣�zoom����������
    SDL_Rect source;
    unsigned char alpha;
public:
    //Texture(string pics,SDL_Renderer* render);
    Texture(SDL_Texture* tex_,SDL_Renderer* render);
    Texture() {};
    void load_tex(SDL_Texture* b_tex);
    //void load_tex(string pic);
    ~Texture();
    void rotate_show(Renderer& render,float center_pos_x,float center_pos_y,double angle,int priority);//��������תһ���Ƕ���ʾ
    void flip_show(Renderer& render,SDL_RendererFlip flags,int priority);//������ĳһ����ת��ʾ
    void show(Renderer& render,int priority);//������ʾ
    void set_source(int x,int y, int width, int height);
    void set_source(SDL_Rect* frect);
    void set_zoom(float x,float y,float width,float height);
    void set_zoom(SDL_FRect* frect);
    SDL_Rect get_source();
    SDL_FRect get_zoom();
    SDL_Texture* get_tex();
    //��ʾ����Ⱦ���ϣ�����Ļ
    void get_params(Uint32* format,int* access, int* w, int *h);//��ȡ������Ϣ
};








class Timer//��ʱ��������֡��
{
protected:
    int tick_per_frame;
    int fps;
    int last_frame_time;//��һ֡����ʱ��
    int start_tick;
    unsigned int T_frames;//��֡��
    map<unsigned int,queue<pair<function<void(std::any)>&,std::any> > >calltable;
    void caller();
    void ascendframe();
public:
    Timer(int fps);
    void init(int fps);
    void setfps(int fps);//�趨���Ƶ�fps
    void ctrlfps();//���п���
    int get_lframe_time();//��ȡ��һ֡����ʱ��
    void start_time();
    void after(unsigned int frames,function<void(std::any)>& timer_callback,std::any params);
};



class MusPool
{
protected:
    json mus_source;
    map<string,int> mindex_b;
    map<string,int> mindex_e;
    vector<Mix_Music*> pool_bgm;//�������ֳ�
    vector<Mix_Chunk*> pool_sdeffect;//��Ч���ֳ�
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


class Mixer//��Ƶ
{
protected:
    int bgm_volume;
    int sdeffect_volume;
public:
    Mixer(int b_volume,int sd_volume);
    Mixer();
    void init(int b_volume,int sd_volume);
    ~Mixer();
    void play_bgm(Mix_Music* music,int loops);//loops,���Ŵ�����-1Ϊ���޴�
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
