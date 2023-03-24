/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <ctime>
#include <random>
//Screen dimension constants	屏幕大小
const int SCREEN_WIDTH = 888;
const int SCREEN_HEIGHT = 888;

int main( int argc, char* args[] )
{
    bool quit{false}; 
    int gap = 2;
    std::default_random_engine engine;
    std::uniform_int_distribution<uint8_t> u(0, 255); // 左闭右闭区间
    engine.seed(time(0));

    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;  /* 就是一个二维图像, 这个图像可以从文件读取也可以从窗口中获取 */

    //Initialize SDL
    Uint32 subsystem_init = SDL_Init( SDL_INIT_VIDEO  ); 
    if ( subsystem_init < 0 ) {  /* 所有 SDL 的方法必须在初始化之后才能使用 */
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        goto ret;
    }

    if (subsystem_init & SDL_INIT_VIDEO) {
        printf("Video is initialized.\n"); 
    } else {
        printf("Video is not initialized.\n");
    }

    printf("初始化标记: %d\n", subsystem_init);
    // SDL_WasInit(SDL_INIT_VIDEO)

    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        goto ret;
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white

    for (size_t row = 0; row < SCREEN_HEIGHT; ++row) {
        SDL_Rect r = {0, row, SCREEN_WIDTH, gap};
        SDL_FillRect( screenSurface, &r, SDL_MapRGB( screenSurface->format, u(engine), u(engine), u(engine) ) );
    }
    
    //Update the surface 
    SDL_UpdateWindowSurface( window );  /* 这一个才是将绘制的画布放到窗口上显示 */
    
    //Hack to get window to stay up
    SDL_Event e; 
    
    while ( !quit ) { 
        while( SDL_PollEvent( &e ) ) { 
            if ( e.type == SDL_QUIT ) {
                quit = true; 
            }
        } 
    }

ret:    /* goto 后不能有任何声明!!! */
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
