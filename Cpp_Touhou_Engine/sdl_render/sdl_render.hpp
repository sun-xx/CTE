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
    TexPool(string jsfile,SDL_Renderer* render);
    void loadpic(string jsfile,SDL_Renderer* render);
    SDL_Texture* get_tex(string name);
};
class Windows//����
{
protected:
    SDL_Window* win;
    int x,y,width,height;//�������Ͻ����꣬����
    Uint32 flags;//��������
    SDL_Event evt;
    map<Uint32,function<void(SDL_Event)>> callbacks;
    bool isquit;
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
    void add_event(Uint32 type,function<void(SDL_Event)> func);
    void del_event(Uint32 type);
    SDL_Event get_event_info();
    void show();
    void hide();
};



class Renderer//��Ⱦ��
{
protected:
    SDL_Renderer* ren;
    int width,height;
    SDL_Rect view_port;
public:
    Renderer(SDL_Window* win,Uint32 flags);//flags,ָ����Ⱦ����ģʽ
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
};

// no match for 'operator!=' (operand types are 'std::filesystem::__cxx11::path' and 'std::filesystem::__cxx11::path')|
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
    void load_tex(SDL_Texture* b_tex);
    //void load_tex(string pic);
    ~Texture();
    void rotate_show(Renderer renderer,float center_pos_x,float center_pos_y,double angle);//��������תһ���Ƕ���ʾ
    void flip_show(Renderer renderer,SDL_RendererFlip flags);//������ĳһ����ת��ʾ
    void show(SDL_Renderer* render);//������ʾ
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
public:
    Timer(int fps);
    void setfps(int fps);//�趨���Ƶ�fps
    void ctrlfps();//���п���
    int get_lframe_time();//��ȡ��һ֡����ʱ��
    void start_time();
};





class Mixer//��Ƶ
{
protected:
    vector<Mix_Music*> bgm;//��������
    vector<Mix_Chunk*> sound_effect;//��Ч����
public:
    Mixer(vector<string> bgms,vector<string> sound_effects);
    ~Mixer();
    void play_bgm(Mix_Music* music,int loops);//loops,���Ŵ�����-1Ϊ���޴�
    void play_soundeffect(Mix_Chunk* effect,int loops);

};





extern bool SDL_all_init();
extern bool SDL_all_quit();
extern void sdl_load_all_pics(vector<string> pics,vector<SDL_Texture*>* tex,SDL_Renderer* render);//Ԥ�������п����õ���ͼƬ�ز�


#endif // SDL_RENDER_HPP_INCLUDED
