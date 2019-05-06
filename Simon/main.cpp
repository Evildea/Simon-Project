#include "SimonApp.h"
#include <time.h>

int main() {
	
	// allocation
	auto app = new SimonApp();
	srand(time(NULL));

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}