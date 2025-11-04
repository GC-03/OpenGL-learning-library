/*
* This program is a test for the Shader class.
* 
* Library used: GLFW3, GLAD
* Author: Giulio Cattelan
*/
#define _USE_MATH_DEFINES

#include <glad.h>
#include <glfw3.h>
#include <Shader.h>

#include <iostream>
#include <math.h>

GLFWwindow* createWindow(int width, int lenght, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
void initializeGLAD();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int INITIAL_WINDOW_WIDTH = 800;
const int INITIAL_WINDOW_HEIGHT = 600;

int main() {

	const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vao, vbo;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = createWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "OpenGL First Project", NULL, NULL);
	glfwMakeContextCurrent(window);

	//GLAD initialization
	initializeGLAD();

	//Callback registration section
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Generating shader program
	Shader myCustomShaderObject(
		"./src/2-Shaders/Shader-class/vertexShader.glsl",
		"./src/2-Shaders/Shader-class/fragmentShader.glsl"
	);

	//Generating vertex array object and vertex buffer object
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	//Binding vao
	glBindVertexArray(vao);

	//Loading data in vbo and ebo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//vbo configuration
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Render loop. It keeps looping drawing images and handling user input until we tell GLFW to stop
	while (!glfwWindowShouldClose(window)) {

		//input handling
		processInput(window);

		//color the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Setting the current active shader program
		myCustomShaderObject.use();

		//Binding the vao
		glBindVertexArray(vao);

		//Drawing the object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Unbinding
		glBindVertexArray(0);

		//check and call event functions and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	//Deallocating
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}


//GLFW window object creation
GLFWwindow* createWindow(int width, int lenght, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWwindow* window = glfwCreateWindow(width, lenght, title, monitor, share);
	if (window == NULL) {
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		//return -1;
	}
	return window;
}

//GLAD initialization
void initializeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!" << std::endl;
		//return -1;
	}
}

//Function to process all input
void processInput(GLFWwindow* window) {
	//if escape key is pressed, it closes the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//Callback function to resize the viewport every time the window is resized by the used
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}