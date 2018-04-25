// ============================================================================
// [Include Section]
// ============================================================================
#include "CApp.h"

// ============================================================================
// [Defines & Constants]
// ============================================================================
#define APPTITLE 		"Z-Renderer"

const int SCREEN_WIDTH 	= 800;
const int SCREEN_HEIGHT	= 600;


CApp::CApp() :
    window(nullptr),
    renderer(nullptr),
    _canvas(nullptr),
	running(false)
{
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
	
    _canvas = new Canvas(SCREEN_WIDTH , SCREEN_HEIGHT);
    
    _camara = Camera::getInstance();
    
	window = SDL_CreateWindow(APPTITLE,
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							  SCREEN_WIDTH, SCREEN_HEIGHT, 
							  SDL_WINDOW_SHOWN);
    
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    
    _canvas->setSurface(surface);

	if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//        renderer = SDL_CreateSoftwareRenderer(surface);
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
		
		OnUpdate();
		OnRender();
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
			if (event->key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		default:
			break;
	}
}

void CApp::OnUpdate()
{
	// Update your game logic here
}

void CApp::OnRender()
{
    SDL_RenderClear(renderer);

    _canvas->update();
    
    SDL_UpdateWindowSurface(window);
	
    SDL_RenderPresent(renderer);
}
