/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640 * 2;
const int SCREEN_HEIGHT = 480 * 2;

/**
 *  初始化 SDL, 创建窗口, 获取窗口画布
 */
//Starts up SDL and creates window
bool init();

//Loads media
// 加载图像
bool loadMedia();

//Frees media and shuts down SDL
// 释放资源
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
// 文中说, SDL_Window 这个东西就是一个图片, 包含所有用来
// 渲染的像素. 这个东西可以使用 CPU 也可以使用 GPU 进行渲染
SDL_Surface* gScreenSurface = NULL;	/* 指着就一定要记得初始化!!!! */

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

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
            //Get window surface 获取窗口画布, 我还是比较喜欢叫它画布
            // 每个窗口都会自带一个画布, 这个要显示东西, 就需要先把这个画布给搞到!!!
            // 哈哈哈, 没啥原因, 就是很开心
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image 好像只能加载 bmp
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
    printf("w: %d, h: %d, pitch: %d\n", gHelloWorld->w, gHelloWorld->h, gHelloWorld->pitch);
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

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
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
            
            //Update the surface 这里的渲染应该指的就是将图画到显示器上
            SDL_UpdateWindowSurface( gWindow );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}