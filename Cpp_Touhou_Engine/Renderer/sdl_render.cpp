//by @dynamder
#include "sdl_render.hpp"

bool SDL_all_init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<"SDL_INIT:"<<SDL_GetError();
        return 0;//³õÊ¼»¯Ê§°Ü
    }
    int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP;
    if((IMG_Init(flags)&flags)!=flags)
    {
        cout<<"IMG_INIT:"<<IMG_GetError();
        return 0;
    }
    if(Mix_Init(MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_FLAC|MIX_INIT_MID|MIX_INIT_MOD|MIX_INIT_OPUS)==0)
    {
        cout<<"MIX_INIT:"<<Mix_GetError();
    }
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    //cerr<<Mix_GetError()<<endl;
    return 1;
}

void SDL_all_quit()
{
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}



///////////////////////////////////////////////////////////////////////////////////////////////
//MusPool
void MusPool::from_json(const json& j,MusPool& mp)
{
    int i=0;
    for (auto iter = j["bgms"].begin(); iter != j["bgms"].end(); iter++)
    {
        mp.mindex_b.insert(pair<string,int>(iter.key(),i++));
        cerr<<"key:"<<iter.key()<<endl;
        string temp=(*iter).get<std::string>();
        cerr<<"temp:"<<temp<<endl;
        mp.pool_bgm.push_back(Mix_LoadMUS(temp.c_str()));
        cerr<<"Music:"<<Mix_GetError()<<endl;
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
    i=0;
    for (auto iter = j["sdeffects"].begin(); iter != j["sdeffects"].end(); iter++)
    {
        mp.mindex_e.insert(pair<string,int>(iter.key(),i++));
        string temp=(*iter).get<std::string>();
        mp.pool_sdeffect.push_back(Mix_LoadWAV(temp.c_str()));
        cerr<<"Chunk:"<<Mix_GetError()<<endl;
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
    cerr<<"address_start:"<<&pool_bgm.at(0)<<endl;
    cerr<<"address_end:"<<&(*pool_bgm.end())<<endl;
}

MusPool::MusPool(json js)
{

    mus_source=js;
    MusPool::from_json(mus_source,*this);
    cerr<<"pool_size:"<<pool_bgm.size()<<" "<<pool_sdeffect.size()<<endl;
}

MusPool::MusPool()
{
    return;
}
MusPool::~MusPool()
{
    cerr<<"MusPool Destructing"<<endl;
    cerr<<"MusPool pool_bgm_freeing"<<endl;
    for(auto &s : pool_bgm)
    {
        //cerr<<"heya:"<<*s<<endl;
        Mix_FreeMusic(s);
    }
    pool_bgm.clear();
    cerr<<"MusPool pool_bgm_freed"<<endl;
    for(auto &s : pool_sdeffect)
    {
        Mix_FreeChunk(s);
    }
    pool_sdeffect.clear();
    cerr<<"MusPool pool_sdeffect_freed"<<endl;
    cerr<<"MusPool Destructed"<<endl;
}
void MusPool::loadmus(json js)
{

    mus_source=js;
    MusPool::from_json(mus_source,*this);
    cerr<<"pool:"<<pool_bgm.size()<<" "<<pool_sdeffect.size()<<endl;

    auto test=pool_bgm.back();
    if(test==NULL) cerr<<"Wha's the NULL fuck"<<endl;
}
Mix_Music* MusPool::get_bgm(string name)
{
    auto m=mindex_b.find(name);
    if(m==mindex_b.end())
    {
        cerr<<"name not found"<<endl;
        return NULL;
    }
    else
    {
        return pool_bgm.at(m->second);
    }
}
Mix_Chunk* MusPool::get_sdeffect(string name)
{
    auto m=mindex_e.find(name);
    if(m==mindex_e.end())
    {
        cerr<<"name not found"<<endl;
        return NULL;
    }
    else
    {
        return pool_sdeffect.at(m->second);
    }
}

void MusPool::debug_muspool()
{
    for(auto &s : pool_bgm)
    {
        cerr<<s<<" ";
    }
    cerr<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//TexPool
TexPool::TexPool()
{
    return;
}
TexPool::TexPool(json js,SDL_Renderer* render)
{
    pic_source=js;

    int i=0;
    pool.clear();
    for (auto iter = pic_source.begin(); iter != pic_source.end(); iter++)
    {
        pindex.insert(pair<string,int>(iter.key(),i++));
        string temp=(*iter).get<std::string>();
        pool.push_back(IMG_LoadTexture(render,temp.c_str()));
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
    //cerr<<"TexPool size:"<<pool.size()<<endl;
}
TexPool::~TexPool()
{
    cerr<<"TexPool Destructing"<<endl;
    for(auto &s : pool)
    {
        SDL_DestroyTexture(s);
    }
    cerr<<"TexPool Destructed"<<endl;
}
void TexPool::loadpic(json js,SDL_Renderer* render)
{
    pic_source=js;
    int i=0;
    pool.clear();
    for (auto iter = pic_source.begin(); iter != pic_source.end(); iter++)
    {
        pindex.insert(pair<string,int>(iter.key(),i++));
        string temp=(*iter).get<std::string>();
        pool.push_back(IMG_LoadTexture(render,temp.c_str()));
        cerr<<"Load_Error:"<<IMG_GetError()<<endl;
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
    cerr<<"TexPool size:"<<pool.size()<<endl;
}
SDL_Texture* TexPool::get_tex(string name)
{
    auto p=pindex.find(name);
    if(p==pindex.end())
    {
        cerr<<"name not found"<<endl;
        return NULL;
    }
    else
    {
        return pool.at(p->second);
    }
}

//Texture
Texture::Texture(SDL_Texture* tex_,SDL_Renderer* render)
{
    tex=tex_;
    SDL_QueryTexture(tex,NULL,NULL,&width,&height);
    SDL_GetTextureAlphaMod(tex,&alpha);
}
Texture::~Texture()
{
    //cerr<<"Texture Destructing"<<endl;
    tex=nullptr;
    //cerr<<"Texture Destructed"<<endl;
}
void Texture::load_tex(SDL_Texture* b_tex)
{
    tex=b_tex;
}
void Texture::rotate_show(Renderer& render,float center_pos_x,float center_pos_y,double angle,int priority)
{
    SDL_FPoint coord;
    coord.x=center_pos_x;
    coord.y=center_pos_y;

    Layer tmp;
    tmp.tex=get_tex();
    tmp.render=render.render();
    tmp.srect=&source;
    tmp.target=&zoom;
    tmp.angle=angle;
    tmp.coord=&coord;
    tmp.flags=SDL_FLIP_NONE;

    render.push_ren(tmp,priority);


    //SDL_RenderCopyExF(render,tex,&source,&zoom,angle,&coord,SDL_FLIP_NONE);
}
void Texture::flip_show(Renderer& render,SDL_RendererFlip flags,int priority)
{
    Layer tmp;
    tmp.tex=get_tex();
    tmp.render=render.render();
    tmp.srect=&source;
    tmp.target=&zoom;
    tmp.angle=0;
    tmp.coord=0;
    tmp.flags=flags;

    render.push_ren(tmp,priority);
    //SDL_RenderCopyExF(render,tex,&source,&zoom,NULL,NULL,flags);
}
void Texture::show(Renderer& render,int priority)
{
    Layer tmp;
    tmp.tex=get_tex();
    tmp.render=render.render();
    tmp.srect=&source;
    tmp.target=&zoom;
    tmp.angle=0;
    tmp.coord=0;
    tmp.flags=SDL_FLIP_NONE;

    render.push_ren(tmp,priority);
    //SDL_RenderCopyExF(render,tex,&source,&zoom,NULL,NULL,SDL_FLIP_NONE);
}
void Texture::set_source(int x,int y, int width, int height)
{
    source.x=x;
    source.y=y;
    source.w=width;
    source.h=height;
}
void Texture::set_source(SDL_Rect* rect)
{
    source=*rect;
}
void Texture::set_zoom(float x,float y,float width,float height)
{
    zoom.x=x;
    zoom.y=y;
    zoom.w=width;
    zoom.h=height;
}
void Texture::set_zoom(SDL_FRect* frect)
{
    zoom=*frect;
}
SDL_Rect Texture::get_source()
{
    return source;
}
SDL_FRect Texture::get_zoom()
{
    return zoom;
}
void Texture::get_params(Uint32* format,int* access, int* w, int *h)
{
    SDL_QueryTexture(tex,format,access,w,h);
}
SDL_Texture* Texture::get_tex()
{
    return tex;
}
//////////////////////////////////////////////////////////////////////////////////
//Renderer
//SDL_Renderer* Renderer::ren;
Renderer::Renderer(SDL_Window* win,Uint32 flags)
{
    ren=NULL;
    ren=SDL_CreateRenderer(win,-1,flags);
    //cerr<<SDL_GetError();
    if(ren==NULL)
    {
        cerr<<"Create Renderer failed:"<<SDL_GetError()<<endl;
        SDL_Quit();
    }
}
void Renderer::init(SDL_Window* win,Uint32 flags)
{
    ren=NULL;
    ren=SDL_CreateRenderer(win,-1,flags);
    //cerr<<SDL_GetError();
    if(ren==NULL)
    {
        cerr<<"Create Renderer failed:"<<SDL_GetError()<<endl;
        SDL_Quit();
    }
}
Renderer::~Renderer()
{
    cerr<<"Renderer Destructing"<<endl;
    SDL_DestroyRenderer(ren);
    ren=NULL;
    cerr<<"Renderer Destructed"<<endl;
}
void Renderer::clear()
{
    SDL_RenderClear(ren);
    for(auto &s : rendertable)
    {
        s.clear();
    }
    rendertable.clear();
}
void Renderer::present()
{
    for(auto s=rendertable.rbegin();s!=rendertable.rend();s++)
    {
        if(!(*s).empty())
        {
            for(auto &t: *s)
            {
                SDL_RenderCopyExF(t.render,t.tex,t.srect,t.target,t.angle,t.coord,t.flags);
            }
        }
    }
    SDL_RenderPresent(ren);
}
void Renderer::get_render_size()
{
    SDL_GetRendererOutputSize(ren,&width,&height);
}
int Renderer::rwidth()
{
    return width;
}
int Renderer::rheight()
{
    return height;
}
void Renderer::set_view_port(SDL_Rect* vp)
{
    SDL_RenderSetViewport(ren,vp);
    if(vp!=NULL)
    {
        view_port=*vp;
    }
}
void Renderer::set_view_port(int x,int y,int width,int height)
{
    view_port.x=x;
    view_port.y=y;
    view_port.w=width;
    view_port.h=height;
    SDL_RenderSetViewport(ren,&view_port);
}
SDL_Rect Renderer::get_view_port()
{
    return view_port;
}
SDL_Renderer* Renderer::render()
{
    return ren;
}

void Renderer::push_ren(Layer layer,int priority)
{
    if(rendertable.size()<=priority)
    {
        rendertable.resize(priority+1);
    }
    rendertable.at(priority).push_back(layer);
}
/////////////////////////////////////////////////////////////////////////////////
//Windows
Windows::Windows(string title,int x_,int y_,int width_,int height_,Uint32 flags_)
{
    win=SDL_CreateWindow(title.c_str(),x_,y_,width_,height_,flags_);
    if(win==NULL)
    {
        cerr<<"Create Window failed:"<<SDL_GetError()<<endl;
        SDL_Quit();
    }
    flags=flags_;
    x=x_;
    y=y_;
    width=width_;
    height=height_;
    callbacks.clear();
}
Windows::~Windows()
{
    cerr<<"Windows Destructing"<<endl;
    SDL_DestroyWindow(win);
    cerr<<"Windows Destructed"<<endl;
}
SDL_Window* Windows::get_window()
{
    return win;
}
void Windows::get_window_size()
{
    SDL_GetWindowSize(win,&width,&height);
}
int Windows::win_width()
{
    return width;
}
int Windows::win_height()
{
    return height;
}
void Windows::Poll_event()
{
    while(SDL_PollEvent(&evt))
    {
        auto it=callbacks.find(evt.type);
        if(it!=callbacks.end())
        {
            it->second(evt);
        }
    }
}
void Windows::bind_event(Uint32 type,function<void(SDL_Event)>& func)
{
    callbacks.insert(pair<Uint32,function<void(SDL_Event)>& >(type,func));
}
void Windows::unbind_event(Uint32 type)
{
    auto it=callbacks.find(type);
    callbacks.erase(it);
}
SDL_Event Windows::get_event_info()
{
    return evt;
}
void Windows::show()
{
    SDL_ShowWindow(win);
}
void Windows::hide()
{
    SDL_HideWindow(win);
}

Uint32 Windows::register_event()
{
    return SDL_RegisterEvents(1);
}
int Windows::raise_event(Uint32 id)
{
    SDL_Event t_evt;
    t_evt.type=id;
    flag_event.push_back(t_evt);
    SDL_Event* t2;
    t2=&(*(flag_event.end()-1));
    int ret=SDL_PushEvent(t2);
    return ret;
}
int Windows::push_event(SDL_Event* event)
{
    int ret=SDL_PushEvent(event);
    return ret;
}
void Windows::set_ignore(Uint32 type,bool is_permanent)
{
    if(is_permanent==true)
    {
        fil_event.p_filtered_event.insert(pair<Uint32,int>(type,0));
        SDL_SetEventFilter(p_do_filter,&fil_event);
    }
    else
    {
        fil_event.t_filtered_event.insert(pair<Uint32,int>(type,0));
    }
}
void Windows::ignore_event()
{
    SDL_FilterEvents(t_do_filter,&fil_event);
}
void Windows::del_ignore(Uint32 type)
{
    auto p_pos=fil_event.p_filtered_event.find(type);
    auto t_pos=fil_event.t_filtered_event.find(type);
    if(p_pos!=fil_event.p_filtered_event.end())
    {
        fil_event.p_filtered_event.erase(p_pos);
    }
    else if(t_pos!=fil_event.t_filtered_event.end())
    {
        fil_event.t_filtered_event.erase(t_pos);
    }
}


//////////////////////////////////////////////////////////////////////////////////
//Timer
Timer::Timer(int fps)
{
    fps=fps;
    tick_per_frame=1000/fps;
    start_tick=SDL_GetTicks();
    last_frame_time=0;
    T_frames=0;
}
void Timer::init(int fps)
{
    fps=fps;
    tick_per_frame=1000/fps;
    start_tick=SDL_GetTicks();
    last_frame_time=0;
    T_frames=0;
}
void Timer::setfps(int fps)
{
    fps=fps;
    tick_per_frame=1000/fps;
}
void Timer::ctrlfps()
{
    int end_tick=SDL_GetTicks();
    int frame_tick=end_tick-start_tick;
    if(frame_tick<tick_per_frame)
    {
        SDL_Delay(tick_per_frame-frame_tick);
    }
    last_frame_time=frame_tick;
}
void Timer::start_time()
{
    start_tick=SDL_GetTicks();
    ascendframe();
}
int Timer::get_lframe_time()
{
    return last_frame_time;
}
void Timer::ascendframe()
{
    T_frames++;
    caller();
}
void Timer::after(unsigned int frames,function<void(std::any)>& timer_callback,std::any params)
{
    auto pos=calltable.find(T_frames+frames);
    if(pos!=calltable.end())
    {
        pos->second.push(pair<function<void(std::any)>&,std::any>(timer_callback,params));
    }
    else
    {
        queue<pair<function<void(std::any)>&,std::any> > tmp;
        tmp.push(pair<function<void(std::any)>&,std::any>(timer_callback,params));
        calltable.insert(pair<unsigned int,queue<pair<function<void(std::any)>&,std::any> > >(T_frames+frames,tmp));
    }
}
void Timer::caller()
{
    auto pos=calltable.find(T_frames);
    //cerr<<"Caller_T_Frames:"<<T_frames<<endl;
    if(pos!=calltable.end())
    {
        while(!(pos->second.empty()))
        {
            pos->second.front().first(pos->second.front().second);
            pos->second.pop();
        }
        calltable.erase(pos);
    }
}
/////////////////////////////////////////////////////////////////////////////
//Mixer to be coded
Mixer::Mixer(int b_volume,int sd_volume)
{

    bgm_volume=b_volume;
    sdeffect_volume=sd_volume;
    set_bgm_volume(bgm_volume);
    set_sdeffect_volume(sd_volume);
}
void Mixer::init(int b_volume,int sd_volume)
{
    bgm_volume=b_volume;
    sdeffect_volume=sd_volume;
    set_bgm_volume(bgm_volume);
    set_sdeffect_volume(sdeffect_volume);
}
Mixer::Mixer()
{
    return;
}
Mixer::~Mixer()
{
    cerr<<"Mixer Destructed"<<endl;
}
void Mixer::play_bgm(Mix_Music* music,int loops)
{
    int flag=Mix_PlayMusic(music,loops);
    cerr<<"flags:"<<flag<<endl;
    cerr<<Mix_GetError()<<endl;
}
void Mixer::play_sdeffect(Mix_Chunk* effect,int loops)
{
    Mix_PlayChannel(-1,effect,loops);
}

void Mixer::pause_bgm()
{
    if(!Mix_PausedMusic())
    {
        Mix_PauseMusic();
    }
}
void Mixer::pause_all()
{
    Mix_ResumeMusic();
    Mix_Pause(-1);
}
void Mixer::set_bgm_volume(int volume)
{
    Mix_VolumeMusic(volume);
    bgm_volume=volume;
}
void Mixer::set_sdeffect_volume(int volume)
{
    Mix_Volume(-1,volume);
    Mix_VolumeMusic(bgm_volume);
    sdeffect_volume=volume;
}
void Mixer::resume_bgm()
{
    Mix_ResumeMusic();
}
void Mixer::resume_all()
{
    Mix_Resume(-1);
}
void Mixer::quit()
{
    //Mix_HaltChannel(-1);
}


//address_start:0x2374b9405d0
//address_end:0x2374b9405d8
//{0x2e57ea1ff70}


//0x220662ffd60
//0x220662ffd60

