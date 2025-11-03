/*
* Now create the same 2 triangles using two different VAOs and VBOs for their data.
* 
* Library used: GLFW3, GLAD
* Author: Giulio Cattelan
* Resources: https://learnopengl.com/Getting-started/Hello-Triangle
*/

/*
#include <glad.h>
#include <glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int INITIAL_WIDTH = 800;
const unsigned int INITIAL_LENGHT = 600;

const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
	"}\0"
;
const char* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0"
;


int main() {

	const float vertices1[] = {
		0.9f, 0.9f, 0.0f,
		0.9f, -0.9f, 0.0f,
		0.1f, -0.9f, 0.0f
	};
	const float vertices2[] = {
		-0.9f, 0.9f, 0.0f,
		-0.1f, 0.9f, 0.0f,
		-0.9f, -0.9f, 0.0f
	};

	unsigned int vao1, vao2, vbo1, vbo2, vertexShader, fragmentShader, shaderProgram;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_LENGHT, "Hello Triangle Ex1", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo1);
	glGenBuffers(1, &vbo2);

	glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao1);
	glDeleteVertexArrays(1, &vao2);
	glDeleteBuffers(1, &vbo1);
	glDeleteBuffers(1, &vbo2);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
*/