
/*
#include "sdl_render/sdl_render.hpp"
#include<bits/stdc++.h>
//#include "touhou/item.hpp"
using namespace std;
bool isquit=0;
function<void()> quit;
void quit_()
{
    isquit=1;
}
vector<SDL_Texture*> texs;
vector<string> pics;
int main(int argc,char* argv[])
{
    if(!SDL_all_init())
    {
        cerr<<"SDL Init failed.Quitting..."<<endl<<SDL_GetError()<<endl;
        SDL_Quit();
    }

    cout<<SDL_GetError()<<endl;
    quit=quit_;

    pics.push_back("D:\\Touhou-project-fanmade-material\\touhou_fan_material\\th18_material\\bullet\\bullet4.png");

    //SDL_ClearError();
    Windows wind("render_test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_SHOWN);
    //SDL_ClearError();
    Renderer render(wind.get_window(),SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    //wind.show();
    //SDL_Renderer* render=SDL_CreateRenderer(wind.get_window(),-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    //cout<<IMG_GetError();
    //SDL_Delay(5000);
    Timer timer(60);
    wind.add_event(SDL_QUIT,quit);
    sdl_load_all_pics(pics,&texs,render.render());

    float x=0,y=0;
    auto it=texs.begin();
    Texture test(*it,render.render());
    test.set_source(12,13,39,39);
    test.set_zoom(0,0,39,39);
    cerr<<"heya";
    SDL_Rect sou;
    sou.x=12;
    sou.y=13;
    sou.w=39;
    sou.h=39;
    SDL_FRect des;
    des.x=x;
    des.y=y;
    des.w=39;
    des.h=39;

    //Texture t("D:\\Touhou-project-fanmade-material\\touhou_fan_material\\th18_material\\bullet\\bullet4.png",render.render());
    while(!isquit)
    {
        render.clear();
        //wind.show();
        //cout<<"wtf";
        timer.start_time();
        wind.Poll_event();
        test.show(render.render());
        x+=1;y+=1;
        test.set_zoom(x,y,39,39);
        //SDL_RenderCopyExF(render.render(),test.get_tex(),&sou,&des,0,NULL,SDL_FLIP_NONE);
        cerr<<SDL_GetError()<<endl;
        render.present();
        timer.ctrlfps();
    }
    //cout<<SDL_GetError();
    //SDL_Delay(5000);
    SDL_all_quit();
    return 0;
}

*/
