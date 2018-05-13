// ============================================================================
// [Include Section]
// ============================================================================
#include "CApp.h"
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
// ============================================================================
// [Defines & Constants]
// ============================================================================
#define APPTITLE 		"Z-Renderer"

using namespace std;

static long getCurrentMillSecond()
{
    long lLastTime = 0;
    struct timeval stCurrentTime;
    
    gettimeofday(&stCurrentTime,NULL);
    lLastTime = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001; // milliseconds
    return lLastTime;
}

CApp::CApp() :
    window(nullptr),
    renderer(nullptr),
    _canvas(nullptr),
	running(false)
{
    _time = getCurrentMillSecond();
}

CApp::~CApp()
{
	OnCleanup();
}

int CApp::OnInit()
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
	
    _canvas = Canvas::getInstance();
    
    _camara = Camera::getInstance();
    
	window = SDL_CreateWindow(APPTITLE,
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  _canvas->getWidth(), _canvas->getHeight(), 
							  SDL_WINDOW_SHOWN);
    
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    
    _canvas->setSurface(surface);

	if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	
	// Success
	return APP_OK;
}

void CApp::OnCleanup()
{
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);	
	}
	if (window != NULL)	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

void CApp::onKeyPress(SDL_Keycode keyCode) {
    
    switch (keyCode) {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_w:
            // 前
            cout<<"w"<<endl;
            break;
        case SDLK_s:
            // 后
            cout<<"s";
            break;
        case SDLK_a:
            // 左
            cout<<"a";
            break;
        case SDLK_d:
            // 右
            cout<<"d";
            break;
        case SDLK_UP:
            
            break;
        case SDLK_DOWN:
            
            break;
        case SDLK_LEFT:
            
            break;
        case SDLK_RIGHT:
            
            break;
        default:
            break;
    }
}

int CApp::OnExecute()
{
	// Initialize application.
	int state = OnInit();
	if (state != APP_OK) {
		return state;
	}
	
	// Enter the SDL event loop.
	SDL_Event event;

	running = true;
	
	while (running)
	{
        while (SDL_PollEvent(&event)) {
        	OnEvent(&event);
        }
        auto curTime = getCurrentMillSecond();
        auto dt = (curTime - _time) * 1.0f / 1000;
		OnUpdate(dt);
        OnRender(dt);
        _time = curTime;
	}

	return state;
}

void CApp::OnEvent(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_QUIT:
			running = false;
			break;
			
		case SDL_KEYDOWN:
            onKeyPress(event->key.keysym.sym);
            break;
		default:
			break;
	}
}

void CApp::OnUpdate(double dt)
{
	// Update your game logic here
}

void CApp::OnRender(double dt)
{
    SDL_RenderClear(renderer);

    _canvas->update(dt);
    
    SDL_UpdateWindowSurface(window);
	
    SDL_RenderPresent(renderer);
}













