/*
* This program contains some info about how to pass data to and throguh shaders.
* Here we constantly change the color of our triangle.
*
* Library used: GLFW3, GLAD
* Author: Giulio Cattelan
* Resources: https://learnopengl.com/Getting-started/Hello-Triangle
*/

/*
#define _USE_MATH_DEFINES

#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <math.h>

GLFWwindow* createWindow(int width, int lenght, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
void initializeGLAD();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void checkShaderCompilation(GLuint shader);
const char* getShaderTypeName(int type);
void checkShaderProgramLink(GLuint shader);

const int INITIAL_WINDOW_WIDTH = 800;
const int INITIAL_WINDOW_HEIGHT = 600;

const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"									//output argument to send to the fragment shader
	"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
	"}\0"
;

const char* fragmentShaderSource =
	"#version 330 core\n"
	"in vec4 vertexColor;\n"									//input argument received from the vertex shader
	"out vec4 FragColor;\n"
	"uniform vec4 uniformColor;\n"								//uniform is a global variable unique per shader program
	"void main() {\n"
		"FragColor = uniformColor;\n"
	"}\0"
;

int main() {

	const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vao, vbo, vertexShader, fragmentShader, shaderProgram;


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


	//Creating and compiling vertex shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader);

	//Creating and compiling fragment shader object
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader);

	//Creating the shader program object
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderProgramLink(shaderProgram);

	//Deleting compiled shader. They're no longer necessary (it clears memory)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


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
		glUseProgram(shaderProgram);

		//Reminder: F(t) = A*cos(2*PI*f*t + P)
		//A = amplitude
		//f = frequency
		//t = time
		//P = initial phase

		float time = glfwGetTime();
		float x = 2.0f / 3.0f * M_PI * time;
		float red = (cos(x) + 1.0f) / 2.0f;
		float green = (cos(x - 2.0f / 3.0f * M_PI) + 1.0f) / 2.0f;
		float blue = (cos(x - 4.0f / 3.0f * M_PI) + 1.0f) / 2.0f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniformColor");
		glUniform4f(vertexColorLocation, red, green, blue, 1.0f);

		std::cout << "\033[5A";
		std::cout << "\033[2K" << "Time: " << time << std::endl;
		std::cout << "\033[2K" << "X [ 2/3*PI * time ]: " << x << std::endl;
		std::cout << "\033[2K" << "Red [ 1/2 * cos(x) + 1/2 ]: " << red << std::endl;
		std::cout << "\033[2K" << "Green [ 1/2 * cos(x - 2/3*PI) + 1/2 ]: " << green << std::endl;
		std::cout << "\033[2K" << "Blue [ 1/2 * cos(x - 4/3*PI) + 1/2 ]: " << blue << std::endl;

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
	glDeleteProgram(shaderProgram);

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

//Checks shader compilation status and shows error info
void checkShaderCompilation(GLuint shader) {
	int success;
	char infoLog[512];
	int type;
	const char* typeName;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderiv(shader, GL_SHADER_TYPE, &type);
		typeName = getShaderTypeName(type);
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << typeName << "::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}
}

const char* getShaderTypeName(int type) {
	switch (type) {
	case GL_VERTEX_SHADER:
		return "GL_VERTEX_SHADER";
	case GL_GEOMETRY_SHADER:
		return "GL_VERTEX_SHADER";
	case GL_FRAGMENT_SHADER:
		return "GL_FRAGMENT_SHADER";
	default:
		return "GL_UNKNOWN_SHADER";
	}
}

void checkShaderProgramLink(GLuint shaderProgram) {
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl << infoLog << std::endl;
	}
}
*/