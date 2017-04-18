#pragma once

namespace jun {
		
	void display();
	void reshape(int x, int y);
	void idle();

	void init(char *windowName, int posX = 0, int posY = 0, int x = 1280, int y = 960);

	void run();
	
}