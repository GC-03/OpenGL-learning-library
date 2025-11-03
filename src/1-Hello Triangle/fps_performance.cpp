/*
* This program is an expansion of indexed_drawing_square.cpp.
* I tried to add manually some form of fps counting and performance measurement.
* 
* Library used: GLFW3, GLAD
* Author: Giulio Cattelan
* Resources: https://learnopengl.com/Getting-started/Hello-Triangle
*/

/*
#include <glad.h>																													//Third-party library to specify at runtime OS-specific informations about OpenGL function locations
#include <glfw3.h>																													//Third-party library to handle window management and OpenGL context
//#include <windows.h>

#include <iostream>

GLFWwindow* createWindow(int width, int lenght, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
void initializeGLAD();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void checkShaderCompilation(GLuint shader);
const char* getShaderTypeName(int type);
void checkShaderProgramLink(GLuint shader);

const int INITIAL_WINDOW_WIDTH = 800;
const int INITIAL_WINDOW_HEIGHT = 600;

//Vertex shader source code (in GLSL)
const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"																							//At location 0 in memory, input element: a vec3 named aPos
	"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"																		//Assign to system gl_Position a vec4 with the position off the vertex
	"}\0"
;

//Fragment shader source code (in GLSL)
const char* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"																											//Output element: a vec4 named FragColor
	"void main() {\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"																				//Assign to FragColor a vec4 with the RGBA color
	"}\0"
;

int main() {

	//Square vertices
	const float vertices[] = {
		0.5f, 0.5f, 0.0f,		//top right
		0.5f, -0.5f, 0.0f,		//bottom right
		-0.5f, -0.5f, 0.0f,		//bottom left
		-0.5f, 0.5f, 0.0f		//top left
	};
	//Indices for drawing the square
	const unsigned int indices[] = {
		0, 1, 3,				//first triangle
		1, 2, 3					//second triangle
	};

	unsigned int vao, vbo, ebo, vertexShader, fragmentShader, shaderProgram;


	//initialization phase


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);																					//OpenGL max version supported for this context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);																					//OpenGL min version supported for this context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);																	//OpenGL core profile is used (no immediate mode and all old stuff)
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);																			//Used to run on MacOSX

	//GLFW window object creation
	GLFWwindow* window = createWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "OpenGL First Project", NULL, NULL);
	glfwMakeContextCurrent(window);																									//Associates the window created to the GLFW OpenGL context

	//GLAD initialization
	initializeGLAD();

	//Callback registration section. Must go after GLAD and GLFW window and context initialization and before the render loop initialization
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);																//Register the callback function to GLFW to execute it every time the event is triggered (in this case every time the window is resized)


	//Render setup phase


	//Creating and compiling vertex shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);																				//Generates an empty shader object of the specified type (in this case a vertex shader)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);																		//Attaches the shader source code to the shader
	glCompileShader(vertexShader);																									//Compiles the source code of the given shader
	checkShaderCompilation(vertexShader);

	//Creating and compiling fragment shader object
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);																			//Generates an empty shader object of the specified type (in this case a fragment shader)
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);																	//Attaches the shader source code to the shader
	glCompileShader(fragmentShader);																								//Compiles the source code of the given shader
	checkShaderCompilation(fragmentShader);

	//Creating the shader program object
	shaderProgram = glCreateProgram();																								//Creates a program object and returns the ID
	glAttachShader(shaderProgram, vertexShader);																					//Attaches the compiled vertex shader
	glAttachShader(shaderProgram, fragmentShader);																					//Attaches the compiled fragment shader
	glLinkProgram(shaderProgram);																									//Links the attached compiled shader in one final shader program, where each output is matched to each input following the pipeline
	checkShaderProgramLink(shaderProgram);

	//Deleting compiled shader. They're no longer necessary (it clears memory)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Generating vertex array object and vertex buffer object
	glGenVertexArrays(1, &vao);																										//Generate the Vertex Array Object
	glGenBuffers(1, &vbo);																											//Generate the Vertex Buffer Object
	glGenBuffers(1, &ebo);																											//Generate the Element Buffer Object

	//Binding vao
	glBindVertexArray(vao);

	//Loading data in vbo and ebo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);																								//Bind the vbo with the current buffer type target. Now any GL_ARRAY_BUFFER call we make will be used to configure the currently bound buffer (which is vbo)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);														//Stores the vertices array into our GL_ARRAY_BUFFER (which is vbo)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);																						//Bind the ebo with the current buffer type target. Now any GL_ELEMENT_ARRAY_BUFFER call we make will be used to configure the currently bound buffer (which is ebo)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);												//Stores the indices array into our GL_ELEMENT_ARRAY_BUFFER (which is ebo)

	//vbo configuration
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);													//Explains to OpenGL how to interpret our vertex data stored in the currently bound vertex array object
	glEnableVertexAttribArray(0);																									//Enables vertex attributes
	
	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);																								//Unbind the vbo (this is safe to do before unbinding the vao because glVertexAttribPointer registered vbo as the vertex attribute's bound vertex buffer)
	glBindVertexArray(0);																											//Unbind the vao (all vbo and ebo configurations are saved inside the vao)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);																						//Unbind the ebo (this must be done after unbinding the vao, otherwise the vao won't register the ebo)

	//FPS performance measurement
	double totalTimeCount = 0;
	int totalFrameCount = 0;

	double previousTime = glfwGetTime();
	double currentTime;
	int frameCount = 0;


	//Render loop


	//Render loop. It keeps looping drawing images and handling user input until we tell GLFW to stop
	while (!glfwWindowShouldClose(window)) {

		//input handling
		processInput(window);

		//color the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);																						//Set the state of the color used to reset the color buffer
		glClear(GL_COLOR_BUFFER_BIT);																								//Clears the given buffer of the current frame buffer. It uses glClearColor color to clear the color buffer with that color

		//Setting the current active shader program
		glUseProgram(shaderProgram);

		//Binding the vao
		glBindVertexArray(vao);

		//Drawing the object
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);																		//Draws what the vertices found in the currently active shader and the currently bound vao (or vbo + configuration)

		//Unbinding
		glBindVertexArray(0);

		//Counting time and FPS
		currentTime = glfwGetTime();
		frameCount++;
		totalFrameCount++;

		if (currentTime - previousTime >= 1.0) {
			totalTimeCount++;
			std::cout << "\033[2A";																									//Moves the cursor 2 lines above
			std::cout << "\033[2K" << "Time: " << totalTimeCount << "s" << std::endl;
			std::cout << "\033[2K" << "FPS: " << frameCount << std::endl;
			frameCount = 0;
			previousTime = currentTime;
		}

		//check and call event functions and swap buffers
		glfwPollEvents();																											//Checks if any events are triggered during this frame. If so, it updates the window state and calls the corresponding functions
		glfwSwapBuffers(window);																									//Swap the color buffer and show it as output for this frame (we use 2 buffer for drawing, one is shown, the other is being drawn. We simply swap them)
	}

	//FPS measurement final output
	std::cout << std::endl << "Time: " << totalTimeCount << "s" << std::endl;
	std::cout << "Total frame count: " << totalFrameCount << std::endl;
	std::cout << "Avg FPS: " << (double)totalFrameCount / totalTimeCount << std::endl;

	//Deallocating
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shaderProgram);

	glfwTerminate();																												//Destroys the OpenGL context, closes the window and terminates the GLFW library
	return 0;
}


//GLFW window object creation
GLFWwindow* createWindow(int width, int lenght, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWwindow* window = glfwCreateWindow(width, lenght, title, monitor, share);													//Creates a window object
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {																		//Load the proper function pointers and return true. glfwGetProcAddress is the pointer to the function that returns those addresses for this context
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

	//if spacebar is held, change the polygon rasterization mode to GL_LINE
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//Callback function to resize the viewport every time the window is resized by the used
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	//Tells OpenGL the size of the rendering window in order to map its own 2D coordinates into screen coordinates
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