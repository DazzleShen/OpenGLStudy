#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//顶点着色器代码
static const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

//片段着色器代码
static const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
inline void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    std::cout << "resize width: " << width << " ,height:" << height << std::endl;
}

//检测着色器是否成功编译
inline void CheckShaderResult(unsigned int shader, GLenum type)
{
	int success;
	char infoLog[512];
	std::string type_string = "";
	switch (type)
	{
	case GL_VERTEX_SHADER:
		type_string = "VERTEX";
		break;
	case GL_FRAGMENT_SHADER:
		type_string = "FRAGMENT";
		break;
	default:
		std::cout << "ERROR::SHADER::CREATETYPE" << std::endl;
		break;
	}
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << type_string << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

//检测着色器程序是否成功编译
inline void CheckProgramResult(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GLPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

inline std::string ReadEntireFile(const std::string& file_name)
{
	std::ifstream file(file_name);

	if(!file.is_open())
	{
		std::cerr << "无法打开文件：" << file_name << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();
	return buffer.str();
}