//@Entry point for 2d Tatris game 
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "TEXTURE.h"
#include "sprite.h"
#include "Tatris.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 360;
const unsigned int SCR_HEIGHT = 640;

const float fps =60;
const float dt = 1 / fps;
float acculator = 0;
float frameStart = glfwGetTime();


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TATRIS", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Loading Game Resources 
	ResourceManager::loadText("fonts/impact.ttf", 20, "TextMenu");
	Texture texture("textures/abstract.png");
	Texture menu("textures/MENU1.png");
	Texture logo("textures/logo.png");
	Texture dashbox("textures/dashbox.png");
	
	//load shader 
	Shader shader("shaders/vshader.vs", "shaders/fshader.frag");
	
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT),-1.0f,1.0f);	
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderprogram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//Rander object
	Sprite sprite(shader);

	//Text randerer object
	ResourceManager::loadText("fonts/impact.ttf", 19, "Text1");

	Tatris tatris(SCR_WIDTH, SCR_HEIGHT);
		
	glEnable(GL_DEPTH);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int count = 0;

	// render loop
	while (!glfwWindowShouldClose(window))
	{	
		const float currentTime = glfwGetTime();
		acculator += currentTime - frameStart;
		//processInput(window);
		

		
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderprogram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		// Clear the screen 
		glClearColor(0.8f, 0.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tatris.inputs(window);

		if (tatris.getState()==Menu)
		{ 		
		
			sprite.randerSprite(menu, glm::vec2(0, 0), glm::vec2(360, 640), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));
			
			sprite.randerSprite(dashbox, glm::vec2(90, 230), glm::vec2(180, 220), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));
			ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"), "PRESS SPACE ",
				130, 350, 1.0, glm::vec3(1.0, 1.0, 1.0));
			ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"), "TO PLAY ",
				150, 320, 1.0, glm::vec3(1.0, 1.0, 1.0));


			sprite.randerSprite(ResourceManager::getTexture("logo"), glm::vec2(35, 530), glm::vec2(290, 90), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));
			

		}
		else if (tatris.getState() == PlayGame)
		{

			frameStart = currentTime;
			if (acculator > dt)
				acculator = 0.2f;
			//Updating the game ;
			while (acculator>dt)
			{
				tatris.logic(dt);
				acculator -= dt;
			}

			sprite.randerSprite(texture, glm::vec2(0, 0), glm::vec2(360, 640), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));

			tatris.rander(sprite);
			tatris.randerTest(sprite);

		}

		else if (tatris.getState() == GameOver)
		{
			sprite.randerSprite(menu, glm::vec2(0, 0), glm::vec2(360, 640), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));

			sprite.randerSprite(dashbox, glm::vec2(90, 230), glm::vec2(180, 220), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));
			ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"), "GAME  OVER!! ",
				130, 400, 1.0, glm::vec3(1.0, 1.0, 0.0));

			ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"), "PRESS SPACE ",
				130, 350, 1.0, glm::vec3(1.0, 1.0, 1.0));

			ResourceManager::getText("Text1").RenderText(ResourceManager::getShader("textShader"), "TO PLAY ",
				150, 320, 1.0, glm::vec3(1.0, 1.0, 1.0));


			sprite.randerSprite(ResourceManager::getTexture("logo"), glm::vec2(35, 530), glm::vec2(290, 90), 0.0f, glm::vec4(1.0, 1.0, 1.0, 1.0));

		}
			
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	tatris.~Tatris();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, true);
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

