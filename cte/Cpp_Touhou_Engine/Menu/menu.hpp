#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "../sdl_render/sdl_render.hpp"
class Menu
{
protected:
    vector<vector<Texture> > mpics;
    pair<const vector<Texture>::iterator,const vector<Texture>::iterator> it_main;
    pair<const vector<Texture>::iterator,const vector<Texture>::iterator> it_runtime;
    pair<const vector<Texture>::iterator,const vector<Texture>::iterator> it_ending;
public:
    Menu(vector<vector<SDL_Texture*> > b_texs);
    void main_menu();
    void run_time_menu();
    void ending_menu();
};

#endif // MENU_HPP_INCLUDED
