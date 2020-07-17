#ifndef Engine_H
#define Engine_H



#include <GLFW\glfw3.h>
#include  <iostream>




class Engine
{
public: 
	Engine();
	~Engine();

	static int SCREEN_WIDTH;
	static int SCREEN_HIGHT;

	bool Initializer (char * windowTitle );

	void Update();
	void beginRander();
	void endRander();
	GLFWwindow* getWin(){ return window; };

	GLFWframebuffersizefun framebuffer_size_callback(GLFWwindow* window, int width, int height);
	

private:
	
	static GLFWwindow* window;




};



#endif // GAME_H
