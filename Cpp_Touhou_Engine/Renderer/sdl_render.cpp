//by @dynamder
#include "sdl_render.hpp"

bool SDL_all_init()
{
    //cout<<"heya";
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<"SDL_INIT:"<<SDL_GetError();
        return 0;//初始化失败
    }
    //cerr<<SDL_GetError()<<endl;
    int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP;
    if((IMG_Init(flags)&flags)!=flags)
    {
        cout<<"IMG_INIT:"<<IMG_GetError();
        return 0;
    }
    if(Mix_Init(MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_FLAC)==0)
    {
        cout<<"MIX_INIT:"<<Mix_GetError();
    }
    return 1;
}

bool SDL_all_quit()
{
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}



/*void sdl_load_all_pics(vector<string> pics,vector<SDL_Texture*>* tex, SDL_Renderer* render)//预加载所有可能用到的图片素材
{
    for(vector<string>::iterator it=pics.begin(); it!=pics.end(); it++)
    {
        //Texture temp(*it,renderer);
        //Texture temp(*it,render);
        (*tex).push_back(IMG_LoadTexture(render,(*it).c_str()));
    }
}*/
//TexPool
TexPool::TexPool()
{

}
TexPool::TexPool(string jsfile,SDL_Renderer* render)
{
    ifstream rf(jsfile);
    json j=json::parse(rf);
    pic_source=j;
    //cerr<<rf.rdbuf()<<endl;
    if(!json::accept(rf))
    {
        cerr<<"not a valid json";
    }
    cout<<pic_source<<endl;
    int i=0;
    pool.clear();
    for (auto iter = pic_source.begin(); iter != pic_source.end(); iter++)
    {
        pindex.insert(pair<string,int>(iter.key(),i++));
        string temp=(*iter).get<std::string>();
        pool.push_back(IMG_LoadTexture(render,temp.c_str()));
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
}
void TexPool::loadpic(string jsfile,SDL_Renderer* render)
{
    ifstream rf(jsfile);
    json j=json::parse(rf);
    pic_source=j;
    //cout<<rf.rdbuf()<<endl;
    if(!json::accept(rf))
    {
        cerr<<"not a valid json";
    }
    int i=0;
    pool.clear();
    for (auto iter = pic_source.begin(); iter != pic_source.end(); iter++)
    {
        pindex.insert(pair<string,int>(iter.key(),i++));
        string temp=(*iter).get<std::string>();
        pool.push_back(IMG_LoadTexture(render,temp.c_str()));
        //std::cout << iter.key() << ":" << iter.value() << std::endl;
    }
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
/*Texture::Texture(string pics,SDL_Renderer* render)
{
    tex=IMG_LoadTexture(render,pics.c_str());
    if(tex==NULL)
    {
        cerr<<"Create texture failed:"<<SDL_GetError()<<endl;
        SDL_Quit();
    }
    SDL_QueryTexture(tex,NULL,NULL,&width,&height);
    SDL_GetTextureAlphaMod(tex,&alpha);
}*/
Texture::Texture(SDL_Texture* tex_,SDL_Renderer* render)
{
    tex=tex_;
    SDL_QueryTexture(tex,NULL,NULL,&width,&height);
    SDL_GetTextureAlphaMod(tex,&alpha);
}
Texture::~Texture()
{
    tex=nullptr;
}
void Texture::load_tex(SDL_Texture* b_tex)
{
    tex=b_tex;
}
void Texture::rotate_show(Renderer renderer,float center_pos_x,float center_pos_y,double angle)
{
    SDL_FPoint coord;
    coord.x=center_pos_x;
    coord.y=center_pos_y;
    SDL_RenderCopyExF(renderer.render(),tex,&source,&zoom,angle,&coord,SDL_FLIP_NONE);
}
void Texture::flip_show(Renderer renderer,SDL_RendererFlip flags)
{
    SDL_RenderCopyExF(renderer.render(),tex,&source,&zoom,NULL,NULL,flags);
}
void Texture::show(SDL_Renderer* render)
{
    SDL_RenderCopyExF(render,tex,&source,&zoom,NULL,NULL,SDL_FLIP_NONE);
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
Renderer::~Renderer()
{
    SDL_DestroyRenderer(ren);
    ren=NULL;
}
void Renderer::clear()
{
    SDL_RenderClear(ren);
}
void Renderer::present()
{
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
    SDL_DestroyWindow(win);
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
void Windows::add_event(Uint32 type,function<void(SDL_Event)> func)
{
    callbacks.insert(pair<Uint32,function<void(SDL_Event)> >(type,func));
}
void Windows::del_event(Uint32 type)
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
//////////////////////////////////////////////////////////////////////////////////
//Timer
Timer::Timer(int fps)
{
    fps=fps;
    tick_per_frame=1000/fps;
    start_tick=SDL_GetTicks();
    last_frame_time=0;
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
}
int Timer::get_lframe_time()
{
    return last_frame_time;
}
/////////////////////////////////////////////////////////////////////////////
//Mixer to be coded
Mixer::Mixer(vector<string> bgms,vector<string> sound_effects)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    for(vector<string>::iterator iter=bgms.begin(); iter!=bgms.end(); iter++)
    {
        bgm.push_back(Mix_LoadMUS((*iter).c_str()));
    }
    for(vector<string>::iterator iter=sound_effects.begin(); iter!=sound_effects.end(); iter++)
    {
        sound_effect.push_back(Mix_LoadWAV((*iter).c_str()));
    }
}
Mixer::~Mixer()
{
    Mix_CloseAudio();
}
void Mixer::play_bgm(Mix_Music* music,int loops)
{
    int flag=Mix_PlayMusic(music,loops);
}
void Mixer::play_soundeffect(Mix_Chunk* effect,int loops)
{
    int flag=Mix_PlayChannel(-1,effect,loops);
}
