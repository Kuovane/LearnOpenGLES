
#include "Lesson1.h"
#include "MyUtils.h"


static const struct _vertiesType
{
	float x, y, z;
};


static const struct _vertiesType vertices[] = {
	{-0.5f, -0.5f, 0.0f, },
	{0.5f, -0.5f, 0.0f,  },
	{0.0f,  0.5f, 0.0f, },
};
static const struct _vertiesType vertices2[] = {
	{0.5f, 0.5f, 0.0f, },
	{-0.5f, 0.5f, 0.0f,  },
	{0.0f,  -0.5f, 0.0f, },
}
;

Lesson1::Lesson1(int width, int height)
{

}

 Lesson1::~Lesson1()
{

}

void Lesson1::run()
{
	GLFWwindow* window = MyUtils::createWindow();



	GLuint programId = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_lesson1.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_lesson1.frag");
	
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

	glBindVertexArray(vertexArrayId[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices2, GL_STATIC_DRAW);
	

	//
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(programId);

	int count = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (count  > 100)
		{
			glBindVertexArray(vertexArrayId[1]);
			//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId[2]);
			if (count > 200)
			{
				count = 0;
			}
		}
		else
		{
			glBindVertexArray(vertexArrayId[0]);
			//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId[1]);
			
		}
		count++;
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
