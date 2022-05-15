
#include "../sdl_render/sdl_render.hpp"
#include<bits/stdc++.h>
using namespace std;
bool isquit=0;
function<void(SDL_Event)> quit;
function<void(SDL_Event)> playeffect;
function<void(SDL_Event)> mycall;
function<void(std::any)> after_call;
TexPool tpool;
 Mixer mx;
 MusPool mpool;
void quit_(SDL_Event event)
{
    isquit=1;
    mx.quit();
}
//Mixer mx;
void playeffect_(SDL_Event event)
{
    cerr<<event.key.keysym.sym<<endl;
    switch(event.key.keysym.sym)
    {
    case SDLK_DOWN:
        mx.play_sdeffect(mpool.get_sdeffect("biu"),0);
        break;
    }
}
void mycall_(SDL_Event event)
{
    //cerr<<"called"<<endl;
}
void after_call_(std::any param)
{
    cerr<<std::any_cast<int>(param);
    cerr<<"after_called"<<endl;
}


int main(int argc,char* argv[])
{
    if(!SDL_all_init())
    {
        cerr<<"SDL Init failed.Quitting..."<<endl<<SDL_GetError()<<endl;
        SDL_Quit();
    }

    cout<<SDL_GetError()<<endl;
    quit=quit_;
    playeffect=playeffect_;
    mycall=mycall_;
    after_call=after_call_;

    Windows wind("render_test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_SHOWN);
    Renderer render(wind.get_window(),SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    Timer timer(60);
    wind.bind_event(SDL_QUIT,quit);
    wind.bind_event(SDL_KEYDOWN,playeffect);
    const Uint32 Touhou_engine_test=wind.register_event();
    cerr<<"ID:"<<Touhou_engine_test;
    wind.bind_event(Touhou_engine_test,mycall);


    ifstream rft("./tests/pics.json");
    json texjs=json::parse(rft);
    tpool.loadpic(texjs,render.render());
    Texture tex(tpool.get_tex("test"),render.render());
    tex.set_source(0,0,100,100);

    ifstream rfm("./tests/music.json");
    json musjs=json::parse(rfm);
    mpool.loadmus(musjs);
    mx.init(0,0);
    mx.play_bgm(mpool.get_bgm("menu"),-1);
    //cerr<<"Mpool_first:"<<*mpool.get_bgm("menu")<<endl;

    Texture tex2(tpool.get_tex("test2"),render.render());
    tex2.set_source(50,50,30,30);
    tex2.set_zoom(20,20,200,200);

    while(!isquit)
    {
        render.clear();
        //wind.show();
        timer.start_time();
        wind.Poll_event();
        tex.show(render,2);
        tex2.show(render,1);
        //x+=1;y+=1;
        tex.set_zoom(0,0,39,39);

        render.present();
        wind.raise_event(Touhou_engine_test);
        cerr<<"main"<<endl;
        timer.ctrlfps();
    }

    SDL_all_quit();
    cerr<<"cyka"<<endl;
    return 0;
}

