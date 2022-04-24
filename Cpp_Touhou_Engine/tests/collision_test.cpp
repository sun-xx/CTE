#include "../sdl_render/sdl_render.hpp"
#include<any>
//#include "../Qcalc/Qcalc.hpp"
#include<cmath>
using namespace std;
vector<string> pics;
vector<SDL_Texture*> tex_pool;
bool isquit=0;
void quit_(SDL_Event evt)
{
    isquit=1;
}
float player_x=0,player_y=0,player_x_last=0,player_y_last=0;
void mov_(SDL_Event evt)
{
    switch(evt.key.keysym.sym)
    {
    case SDLK_UP:
        player_y+=1;
        break;
    case SDLK_DOWN:
        player_y-=1;
        break;
    case SDLK_LEFT:
        player_x-=1;
        break;
    case SDLK_RIGHT:
        player_x+=1;
        break;
    }
}

pair<float,float> transfer_coord_to_sdl(float x,float y,float world_x,float world_y)
{
    return make_pair(world_x+x,world_y-y);
}
function<void(SDL_Event)> quit;
function<void(SDL_Event)> mov;




bool iscollide(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float ra,float rb)
{
    float dxA=x2-x1;
    float dyA=y2-y1;
    float dxB=x4-x3;
    float dyB=y4-y3;

    float a=0,b=0,c=0;
    if(dxB==0&&dyB==0&&dxA!=0&&dyA!=0)
    {
        a=dxA*dxA+dyA*dyA;
        b=-2*(x3*dxA+dyA*(y3-y1+(x1*dyA)/dxA));
        c=x3*x3+(y3-y1+(x1*dyA)/dxA)*(y3-y1+(x1*dyA)/dxA)-ra*ra-rb*rb;
    }
    if(dxA==0&&dyA==0&&dxB!=0&&dyB!=0)
    {
        a=dxB*dxB+dyB*dyB;
        b=-2*(x1*dxB+dyB*(y1-y3+(x3*dyB)/dxB));
        c=x1*x1+(y1-y3+(x3*dyB)/dxB)*(y1-y3+(x3*dyB)/dxB)-ra*ra-rb*rb;
    }
    else
    {
        a=(dxA-dxB)*(dxA-dxB)+(dyA-dyB)*(dyA-dyB);
        b=2*(dyA-dyB)*(y1-y3+x3*dyB/dxB-x1*dyA/dxA);
        c=((y1-y3)*(y1-y3)+(x3*dyB/dxB-x1*dyA/dxA)*(x3*dyB/dxB-x1*dyA/dxA)+2*(y1-y3)*(x3*dyB/dxB-x1*dyA/dxA)-ra*ra-rb*rb);
    }



    float delta=b*b-4*a*c;


    if(delta<0) return false;

    float xa=dxA*((-b+sqrt(delta))/(2*a));
    float xb=dxA*((-b-sqrt(delta))/(2*a));
    if((x1<xa&&xa<x2)||(x1<xb&&xb<x2))
    {
        cout<<a<<" "<<b<<" "<<c<<endl;
        cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<x3<<" "<<y3<<" "<<x4<<" "<<y4<<" "<<ra<<" "<<rb<<" "<<endl<<endl;
        return true;
    }
    else return false;
}


int main(int argc,char* argv[])
{
    if(!SDL_all_init())
    {
        cerr<<"SDL_INIT_FAILED"<<SDL_GetError();
    }
    Windows wind("collide test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_ALLOW_HIGHDPI);
    float world_x=800/2,world_y=600/2;
    Renderer ren(wind.get_window(),SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    pics.push_back("D:\\Touhou-project-fanmade-material\\touhou_fan_material\\th18_material\\bullet\\bullet4.png");
    sdl_load_all_pics(pics,&tex_pool,ren.render());


    Texture pltex(*(tex_pool.begin()),ren.render());
    Texture tex(*(tex_pool.begin()),ren.render());

    quit=quit_;
    mov=mov_;
    wind.add_event(SDL_QUIT,quit);
    wind.add_event(SDL_KEYDOWN,mov);

    Timer t(60);

    tex.set_source(12,13,39,39);
    tex.set_zoom(0,0,39,39);

    pltex.set_source(77,11,37,37);
    pltex.set_zoom(0,0,37,37);

    float x=0,y=0,x_last=0,y_last=0,step=0;

    pair<float,float> object_sdl;
    pair<float,float> object_sdl_last;
    pair<float,float> player_sdl;
    pair<float,float> player_sdl_last;
    while(!isquit)
    {
        t.start_time();
        wind.Poll_event();

        x=60*cos(step);
        y=60*sin(step);
        step+=0.05;

        object_sdl=transfer_coord_to_sdl(x,y,world_x,world_y);
        player_sdl=transfer_coord_to_sdl(player_x,player_y,world_x,world_y);
        tex.set_zoom(object_sdl.first,object_sdl.second,39,39);
        pltex.set_zoom(player_sdl.first,player_sdl.second,39,39);
        ren.clear();
        tex.show(ren.render());
        pltex.show(ren.render());
        ren.present();


        if(iscollide(x_last,y_last,x,y,player_x_last,player_y_last,player_x,player_y,39,37))
        {
            SDL_Delay(2000);
            player_x=0;
            player_y=0;
        }



        x_last=x;
        y_last=y;
        player_x_last=player_x;
        player_y_last=player_y;

        t.ctrlfps();

    }
    return 0;
}
