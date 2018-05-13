// ============================================================================
// [Include Section]
// ============================================================================
#ifdef _WIN32
#include <SDL.h>
#else

#include "Canvas.hpp"
#include "Camera.hpp"
#include <sys/time.h>

#endif



// ============================================================================
// [CApp]
// ============================================================================
// This is just a sample SDL application class to test that the app works.
class CApp
{
public:

	// Application state
	enum APP_STATE
	{
		APP_OK = 0,
		APP_FAILED = 1
	};

	CApp();
	~CApp();
	
    void setInterval(double val) {
        _interval = val;
    }
    
    void onKeyPress(SDL_Keycode keyCode , double dt);
    
	// Run application, called by your code.
	int 			OnExecute();

private:
	
    double         _interval = 1 / 60.0f;
    
	// Whether the application is running.
	bool 			running;

	SDL_Window*		window;
    
	SDL_Renderer*	renderer;
    
    long            _time;
    
    Canvas *        _canvas;
    
    Camera *        _camara;

	// Initialize application
	int 			OnInit();
	
	// Clean up the application
	void 			OnCleanup();

	// Called to process SDL event.
	void 			OnEvent(SDL_Event* event , double dt);

	// Called to update game logic
	void			OnUpdate(double dt);
	
	// Called to render the app.
	void 			OnRender(double dt);
};
