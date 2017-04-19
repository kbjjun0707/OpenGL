#pragma once

namespace jun {

	void init(char *windowName, int posX = 0, int posY = 0, int x = 1280, int y = 960);


	void reshape(int x, int y);

	void onMouseClick(int bnt, int state, int x, int y);
	void onKeyBoard(unsigned char key, int x, int y);
	
	void idle();
	void display();


	void run();
	
}