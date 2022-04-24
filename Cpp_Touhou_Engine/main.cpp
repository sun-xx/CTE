

/*
#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
class InitError : public std::exception
{
    std::string msg;
public:
    InitError();
    InitError( const std::string & );
    virtual ~InitError() throw();
    virtual const char * what() const throw();
};

InitError::InitError() :
    exception(),
    msg( SDL_GetError() )
{
}

InitError::InitError( const std::string & m ) :
    exception(),
    msg( m )
{
}

InitError::~InitError() throw()
{
}

const char * InitError::what() const throw()
{
    return msg.c_str();
}

class SDL
{
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
public:
    SDL( Uint32 flags = 0 );
    virtual ~SDL();
    void draw();
};

SDL::SDL( Uint32 flags )
{
    if ( SDL_Init( flags ) != 0 )
        throw InitError();

    if ( SDL_CreateWindowAndRenderer( 640, 480, SDL_WINDOW_SHOWN,
                                      &m_window, &m_renderer ) != 0 )
        throw InitError();
}

SDL::~SDL()
{
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

void SDL::draw()
{
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );

    int rgb[] = { 203, 203, 203, // Gray
                  254, 254,  31, // Yellow
                    0, 255, 255, // Cyan
                    0, 254,  30, // Green
                  255,  16, 253, // Magenta
                  253,   3,   2, // Red
                   18,  14, 252, // Blue
                    0,   0,   0  // Black
                };

    SDL_Rect colorBar;
    colorBar.x = 0; colorBar.y = 0; colorBar.w = 90; colorBar.h = 480;

    // Render a new color bar every 0.5 seconds
    for ( int i = 0; i != sizeof rgb / sizeof *rgb; i += 3, colorBar.x += 90 )
    {
        SDL_SetRenderDrawColor( m_renderer, rgb[i], rgb[i + 1], rgb[i + 2], 255 );
        SDL_RenderFillRect( m_renderer, &colorBar );
        SDL_RenderPresent( m_renderer );
        SDL_Delay( 500 );
    }
}



#define CV_PI 3.14159265359
#define halfPi ((float)(CV_PI*0.5))
#define Pi     ((float)CV_PI)
#define a0  0 //-4.172325e-7f   (-(float)0x7)/((float)0x1000000);



#define a1 1.000025f        //((float)0x1922253)/((float)0x1000000)*2/Pi;
#define a2 -2.652905e-4f    //(-(float)0x2ae6)/((float)0x1000000)*4/(Pi*Pi);
#define a3 -0.165624f       //(-(float)0xa45511)/((float)0x1000000)*8/(Pi*Pi*Pi);
#define a4 -1.964532e-3f    //(-(float)0x30fd3)/((float)0x1000000)*16/(Pi*Pi*Pi*Pi);
#define a5 1.02575e-2f      //((float)0x191cac)/((float)0x1000000)*32/(Pi*Pi*Pi*Pi*Pi);
#define a6 -9.580378e-4f    //(-(float)0x3af27)/((float)0x1000000)*64/(Pi*Pi*Pi*Pi*Pi*Pi);

#define Qsin(x) ((((((a6*(x) + a5)*(x) + a4)*(x) + a3)*(x) + a2)*(x) + a1)*(x) + a0)
#define Qcos(x) Qsin(halfPi - (x))


float deT(float num)
{
    if(num>=(-halfPi)&&num<=(halfPi)) return num;
    else
    {
        num-=int(num/halfPi)*halfPi;
    }
    std::cout<<num<<std::endl;
    return num;
}


#define PI 3.141592654
#define HALF_PI PI*0.5
#define TWO_PI  PI*2
#define  SIN_PARA_A 1.27323954f
#define  SIN_PARA_B 0.405284735f

*/


/*float Qsin(float x)// -pi--pi
{

	if (x< -PI){
		x -= ( (int)((x+PI)*10000) /62832)*TWO_PI;
	}
	else if (x>  PI){
		x -= ( (int)((x-PI)*10000) /62832+1)*TWO_PI;
	}


	//compute sine
	if (x< 0)
		return ((SIN_PARA_A + SIN_PARA_B * x)* x);
	else
		return ((SIN_PARA_A - SIN_PARA_B * x)* x);
}

float Qcos(float x)
{
	//compute cosine: sin(x + PI/2) = cos(x)

	x+= HALF_PI;
	if (x< -PI){
		x -= ( (int)((x+PI)*10000) /62832)*TWO_PI;
	}
	else if (x>  PI){
		x -= ( (int)((x-PI)*10000) /62832+1)*TWO_PI;
	}

	if (x< 0)
		return ((SIN_PARA_A + SIN_PARA_B * x)* x);
	else
		return ((SIN_PARA_A - SIN_PARA_B * x)* x);
}*/





/*
int main( int argc, char * argv[] )
{
    try
    {
        SDL sdl( SDL_INIT_EVERYTHING);
        std::cerr<<SDL_GetError();
        sdl.draw();

        //  std::cout<<Qcos(deT(5.9));
        return 0;
    }
    catch ( const InitError & err )
    {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
    }

    return 1;
}


*/

