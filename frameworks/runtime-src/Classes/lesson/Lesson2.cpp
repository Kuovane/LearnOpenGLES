
#include "Lesson2.h"
#include "MyUtils.h"


static const struct _vertiesType
{
	float x, y, z;
};

static  struct _vertiesType vertices[] = {
	 0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
}
;

static unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};


Lesson2::Lesson2(int width, int height)
{

}

 Lesson2::~Lesson2()
{

}

void Lesson2::run()
{
	GLFWwindow* window = MyUtils::createWindow();



	GLuint programId = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson1.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson1.frag");
	GLuint programId2 = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson2.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson2.frag");
	
	GLuint vpos_location = glGetAttribLocation(programId, "vPos");

	// NOTE: OpenGL error checks have been omitted for brevity
	GLuint vertexBufferId[2];
	GLuint vertexArrayId[2];
	glGenBuffers(2, vertexBufferId);
	glGenVertexArrays(2,vertexArrayId);

	glBindVertexArray(vertexArrayId[0]);//绑定VAO后，后面glVertexAttribPointer会自动存储到VAO中
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//
	//glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	//glEnableVertexAttribArray(0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int count = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (count < 100)
		{
			glUseProgram(programId);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBindBuffer(GL_VERTEX_ARRAY, vertexArrayId[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_VERTEX_ARRAY, 0);
		}
		else
		{
			glUseProgram(programId2);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		
		if (count > 200)
		{
			count = 0;
		}
		count++;
		
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
