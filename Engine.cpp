/*
* This the  implimentation file for WordSearch Engine
@by Kutullo
*
*
*/



#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "TEXTURE.h"
#include "sprite.h"
#include "Tatris.h"




 int Engine::SCREEN_WIDTH = 620;
 int Engine::SCREEN_HIGHT = 621;
 GLFWwindow* Engine::window = NULL;

 Engine::Engine()
 {

 }

 Engine::~Engine()
 {

 }

 bool Engine::Initializer(char * windowTitle)
 {
	 glfwInit();
	 if (!glfwInit())
	 {
		 std::cout << "Engine::Init_  ERROR::glfwInit" << std::endl;
		 return false;
	 }

	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	 window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HIGHT, windowTitle, NULL, NULL);

	 if (window == NULL)
	 {
		 std::cout << "Engine::Init_  ERROR::WINDOW" << std::endl;
		 glfwTerminate();
		 return false;
	 }

	


	 //glfw setup
	 glfwMakeContextCurrent(window);
	 int width, hight;
	 glfwSetFramebufferSizeCallback(window, framebuffer_size_callback(window, SCREEN_WIDTH, SCREEN_HIGHT));
	 glfwGetFramebufferSize(window, &width, &hight);
	 glfwSwapInterval(1);


	 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	 {
		 std::cout << "Failed to initialize GLAD" << std::endl;
		 return false;
	 }
	/* const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	 int xpos = (mode->width - SCREEN_WIDTH) / 2;
	 int ypos = (mode->height - SCREEN_HIGHT) / 2;
	 glfwSetWindowPos(window, xpos, ypos);


	 //GL 
	 glViewport(0, 0, width, hight);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, width, 0, hight,-10,10);
	 glDepthRange(-10, 10);
	 glMatrixMode(GL_MODELVIEW);

	 */

	 //alpha

	 glEnable(GL_ALPHA_TEST);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	 return true;


 }

 void Engine::Update()
 {
	 glfwPollEvents();
 }

 void Engine::beginRander()
 {
	 glClearColor(0,0.5,1,1);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


 }

 void Engine::endRander()
 {
	
	 glfwSwapBuffers(window);

 }

 GLFWframebuffersizefun Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
 {
	 glViewport(0, 0, width, height);
 }