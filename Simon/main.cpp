#include "SimonApp.h"
#include <time.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main() {
	
	// allocation
	auto app = new SimonApp();
	srand(time(NULL));

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	_CrtDumpMemoryLeaks();

	return 0;
}