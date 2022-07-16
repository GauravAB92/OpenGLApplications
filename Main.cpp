#include "TestApplication.h"
#include <iostream>




int main(int argc, char** argv)
{
	Test app;


	if (!app.Initialize())
	{
		std::cout << " failed to intialized application" << std::endl;
	}
	
	app.RenderLoop();

	return 0;
}