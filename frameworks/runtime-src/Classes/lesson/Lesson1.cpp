
#include "Lesson1.h"
#include "MyUtils.h"


static const struct
{
	float x, y, z;
}  vertices[] = {
	{-0.5f, -0.5f, 0.0f, },
	{0.5f, -0.5f, 0.0f,  },
	{0.0f,  0.5f, 0.0f, },
};

Lesson1::Lesson1(int width, int height)
{

}

 Lesson1::~Lesson1()
{

}

void Lesson1::run()
{
	GLFWwindow* window = MyUtils::createWindow();



	GLuint programId = MyUtils::createGLProgram("E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_lesson1.vert", "E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_lesson1.frag");
	

	// NOTE: OpenGL error checks have been omitted for brevity
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	


	GLuint vpos_location = glGetAttribLocation(programId, "vPos");


	glEnableVertexAttribArray(vpos_location);

	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	
	

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(programId);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
