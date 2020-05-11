
#include "Lesson3.h"
#include "MyUtils.h"


static const struct _vertiesType
{

	float x, y, z, r, g, b;
};


static struct _vertiesType vertices[] = {
	{ 0.5f, 0.5f, 0.0f, 1.0,0.0,0.0},   // 右上角
	{0.5f, -0.5f, 0.0f, 0.0,1.0,0.0}, // 右下角
	{-0.5f, -0.5f, 0.0f, 0.0,0.0,1.0}, // 左下角
	{-0.5f, 0.5f, 0.0f ,0.0,1.0,1.0},  // 左上角
}
;

static unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};


Lesson3::Lesson3(int width, int height)
{

}

 Lesson3::~Lesson3()
{

}

void Lesson3::run()
{
	GLFWwindow* window = MyUtils::createWindow();



	GLuint programId = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson3.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson3.frag");
	//GLuint programId2 = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson3.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson3.frag");
	
	GLuint vpos_location = glGetAttribLocation(programId, "vPos");
	GLuint aColor_location = glGetAttribLocation(programId, "aColor");

	// NOTE: OpenGL error checks have been omitted for brevity
	GLuint vertexBufferId[2];
	GLuint vertexArrayId[2];
	glGenBuffers(2, vertexBufferId);
	glGenVertexArrays(2,vertexArrayId);

	int stride = sizeof(vertices[0]);
	glBindVertexArray(vertexArrayId[0]);//绑定VAO后，后面glVertexAttribPointer会自动存储到VAO中
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glVertexAttribPointer(aColor_location, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * 4));
	glEnableVertexAttribArray(vpos_location);
	glEnableVertexAttribArray(aColor_location);//需要启用这个顶点属性

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

	int vertexColorLocation = glGetUniformLocation(programId, "ourColor");
	glUseProgram(programId);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int count = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBindBuffer(GL_VERTEX_ARRAY, vertexArrayId[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_VERTEX_ARRAY, 0);

		
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
