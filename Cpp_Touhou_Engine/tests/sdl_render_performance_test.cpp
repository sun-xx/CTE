#include "../renderer/sdl_render.hpp"
#include <SDL2/sdl.h>
#include "../Item/Bullet.cpp"
#undef main
using namespace std;
bool isquit=0;
function<void(SDL_Event)> quit;
void quit_(SDL_Event)
{
    isquit=1;
}
extern Renderer render;
TexPool tpool;
class myBullet:virtual public Bullet
{
public:
    myBullet(vector<Texture> tex,int w,int h,float init_x,float init_y,float r_):Bullet(tex,w,h,init_x,init_y,r_)
    {

    };
    virtual ~myBullet(){};
protected:
    virtual void special_play();
};
void myBullet::special_play()
{
    angle=90;
    velocity=3;
    this->move();
}

int main(int argc,char* argv[])
{
    SDL_all_init();
    Windows wind("render_test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_SHOWN);
    render.init(wind.get_window(),SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    quit=quit_;

    Timer timer(60);
    wind.bind_event(SDL_QUIT,quit);
    ifstream rft("./tests/pics.json");
    json texjs=json::parse(rft);
    tpool.loadpic(texjs,render.render());
    Texture tex(tpool.get_tex("test"),render.render());
    tex.set_source(11,11,43,43);
    tex.set_zoom(0,0,43,43);

    vector<Texture> texv;
    texv.push_back(tex);
    myBullet test(texv,43,43,40,40,3);

    cerr<<"Texture size:"<<sizeof(Texture);
    while(!isquit)
    {
        render.clear();
        timer.start_time();
        wind.Poll_event();
        test.run(render);
        render.present();
        timer.ctrlfps();
    }

    return 0;
}

