/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Include SDL functions and datatypes
#include "SDL2/SDL.h"

int main( int argc, char* args[] )
{
    //The images    一个 SDL_Surface 便代表了一幅可以进行绘制的画布
    SDL_Surface* hello = NULL;
    SDL_Surface* screen = NULL;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Set up screen 创建了一块画布, w 640 高 320 每个像素 32 为
    // SDL_SWSURFACE 仅仅是为了指出, 画布位于软件内存, 好像这个标记没什么大用途
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    //Load image 这个是加载一幅 bmp 图像到指定的画布中
    hello = SDL_LoadBMP( "hello.bmp" );

    //Apply image to screen 在画布间拷贝数据
    SDL_BlitSurface( hello, NULL, screen, NULL );

    //Update Screen
    SDL_Flip( screen );

    //Pause
    SDL_Delay( 2000 );

    //Free the loaded image
    SDL_FreeSurface( hello );

    //Quit SDL
    SDL_Quit();

    return 0;
}
