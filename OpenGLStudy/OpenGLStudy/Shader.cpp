#include "Shader.h"

void Shader() 
{
	// glfw: initialize and configure
// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	/*------着色器部分------*/

	//创建顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//将创建的顶点着色器和顶点着色器代码字符串绑定
	std::string vertex_shader_string = ReadEntireFile("ShaderFile/VS.txt");
	std::cout << vertex_shader_string << std::endl;
	const char* shader_string = vertex_shader_string.c_str();
	glShaderSource(vertexShader, 1, &shader_string, NULL);
	glCompileShader(vertexShader);

	CheckShaderResult(vertexShader, GL_VERTEX_SHADER);

	//创建片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//将创建的片段着色器和片段着色器代码绑定
	std::string fragment_shader_string = ReadEntireFile("ShaderFile/FS.txt");
	std::cout << fragment_shader_string << std::endl;
	shader_string = fragment_shader_string.c_str();
	glShaderSource(fragmentShader, 1, &shader_string, NULL);
	glCompileShader(fragmentShader);

	CheckShaderResult(fragmentShader, GL_FRAGMENT_SHADER);

	//创建着色器程序
	unsigned int shaderProgram = glCreateProgram();

	//将顶点着色器和片段着色器和着色器程序绑定
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);

	//连接
	glLinkProgram(shaderProgram);
	CheckProgramResult(shaderProgram);

	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* 使用VBO模式 */
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//创建顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//使用VAO模式
	//创建顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//绑定VAO
	glBindVertexArray(VAO);

	//利用glBindBuffer绑定gl_array_buffer类型的顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//将先前的顶点数据复制到缓冲的内存中
	//GL_STATIC_DRAW ：数据不会或几乎不会改变
	//GL_DYNAMIC_DRAW：数据会被改变很多
	//GL_STREAM_DRAW ：数据每次绘制时都会改变
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//连接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw
		// 使用着色器程序
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//#12

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return;
}