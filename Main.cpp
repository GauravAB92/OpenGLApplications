#include "Geometry3D.h"
#include <iostream>




int main(int argc, char** argv)
{
	Geometry3D app;


	if (!app.Initialize())
	{
		std::cout << " failed to intialized application" << std::endl;
	}
	
	app.RenderLoop();

	return 0;
}