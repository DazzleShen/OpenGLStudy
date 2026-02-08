#include "DrawRect.h"

void DrawRect()
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

	//创建着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//将创建的着色器和着色器代码字符串绑定
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	CheckShaderResult(vertexShader, GL_VERTEX_SHADER);

	//创建片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//将片段着色器和着色器代码绑定
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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

	/* 使用EBO模式 */
	float vertices[] =
	{
		0.5f, 0.5f, 0.0f,	//右上角
		0.5f, -0.5f, 0.0f,	//右下角
		-0.5f, -0.5f, 0.0f,	//左下角
		-0.5f, 0.5f, 0.0f	//左上角
	};

	unsigned int indices[] =
	{
		//注意索引需要从0开始
		0, 1, 3,	//第一个三角形
		1, 2, 3		//第二个三角形
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

	//创建索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//利用glBindBuffer绑定gl_array_buffer类型的顶点缓冲对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//将先前的顶点数据复制到缓冲的内存中
	//GL_STATIC_DRAW ：数据不会或几乎不会改变
	//GL_DYNAMIC_DRAW：数据会被改变很多
	//GL_STREAM_DRAW ：数据每次绘制时都会改变
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//连接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	//线框绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//默认的填充绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int nrAttributes = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vartex attributes supported: " << nrAttributes << std::endl;

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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return;
}
