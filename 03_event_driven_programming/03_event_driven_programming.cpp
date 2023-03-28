/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.
事件触发
*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gXOut = SDL_LoadBMP( "x.bmp" );
    if( gXOut == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gXOut );
    gXOut = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {			
            /* 加载完数据图像后的处理循环 */
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue    轮询检查是否有事件发生
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit    可以演技一下这个事件机制是如何实现的
                    switch ( e.type ) {   
                        case SDL_QUIT:
                            printf("点击关闭按钮\n");
                            quit = true;
                            break;
                        
                        case SDL_KEYDOWN:
                            printf("键盘按下\n");
                            break;

                        case SDL_KEYUP:
                            printf("键盘弹起\n");
                            break;

                        case SDL_MOUSEMOTION:
                            printf("鼠标移动, x: %d, y: %d\n", e.motion.x, e.motion.y);
                            break;
                    }
                }

                //Apply the image
                SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL ); /* 前缓冲区 */
            
                //Update the surface
                SDL_UpdateWindowSurface( gWindow ); /* 后缓冲区 */
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}