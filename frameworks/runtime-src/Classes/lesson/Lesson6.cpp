
#include "Lesson6.h"
#include "MyUtils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const struct _vertiesType
{

	float x, y, z, r, g, b,s,t;
};


static struct _vertiesType vertices[] = {
	{-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0,0.0},
	{0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0,0.0},
	{0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0,1.0},
	{0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0,1.0},
	{-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0,1.0},
	{-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0,0.0},

	{-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0,0.0},
	{0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0,0.0},
	{ 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0,1.0},
	{0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0,1.0},
	{-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0,1.0},
	{-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0,0.0},

	{-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0,0.0},
	{-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0,0.0},
	{-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0,1.0},
	{-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0,1.0},
	{-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0,1.0},
	{-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0,0.0},

	{0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0,0.0},
	{0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0,0.0},
	{0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0,1.0},
	{0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0,1.0},
	{0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0,1.0},
	{0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0,0.0},

	{-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0,0.0},
	{0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,1.0,0.0},
	{0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0,1.0},
	{0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0,1.0},
	{-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0,1.0},
	{-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0,0.0},

	{-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0,0.0},
	{0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0,0.0},
	{0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0,1.0},
	{0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0,1.0},
	{-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0,1.0},
	{-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0,0.0}
}
;

static unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static float deltaTime = 0.0f; // 当前帧与上一帧的时间差
static float lastFrame = 0.0f; // 上一帧的时间

static float lastX = 320, lastY = 240, yaw= -90.0f, pitch=0.0, fov=45;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}
		
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMouse = true;
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;


	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}


static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

Lesson6::Lesson6(int width, int height)
{

}

 Lesson6::~Lesson6()
{

}

void Lesson6::run()
{
	GLFWwindow* window = MyUtils::createWindow(key_callback);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLuint programId = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson6.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson6.frag");
	//GLuint programId2 = MyUtils::createGLProgram("E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson6.vert", "E:/learn/c2dx/LearnOpenGLES/res/shaders/ccShader_Lesson6.frag");
	
	GLuint textureId = MyUtils::LoadGLTextures("textures/container2.png", GL_RGBA);

	glActiveTexture(GL_TEXTURE1);
	GLuint textureId2 = MyUtils::LoadGLTextures("textures/awesomeface.png", GL_RGBA);



	GLuint vpos_location = glGetAttribLocation(programId, "vPos");
	GLuint aColor_location = glGetAttribLocation(programId, "aColor");
	GLuint aTex_location = glGetAttribLocation(programId, "vTex");
	
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
	glVertexAttribPointer(aTex_location, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * 8));
	glEnableVertexAttribArray(vpos_location);
	glEnableVertexAttribArray(aColor_location);//需要启用这个顶点属性
	glEnableVertexAttribArray(aTex_location);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//
	//glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	//glEnableVertexAttribArray(0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//int vertexColorLocation = glGetUniformLocation(programId, "ourColor");
	glUseProgram(programId);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUniform1i(glGetUniformLocation(programId, "CC_Texture0"), 0);
	glUniform1i(glGetUniformLocation(programId, "CC_Texture1"), 1);
	int count = 0;


	

	glm::mat4 view(1.0);
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


	glm::mat4 model(1.0);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	unsigned int transformLoc = glGetUniformLocation(programId, "aTransform");

	unsigned int modelLoc = glGetUniformLocation(programId, "model");
	unsigned int projectLoc = glGetUniformLocation(programId, "projection");
	unsigned int viewLoc = glGetUniformLocation(programId, "view");


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glEnable(GL_DEPTH_TEST);


	glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//float timeValue = glfwGetTime();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;







		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//glm::mat4 trans(1.0);
		//trans = glm::rotate(trans, timeValue, glm::vec3(0.0, 0.0, 1.0));
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBindBuffer(GL_VERTEX_ARRAY, vertexArrayId[0]);

		glm::mat4 projection(1.0);
		projection = glm::perspective(glm::radians(fov), 640.0f / 480.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		
	
		
		glm::mat4 view(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));





		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//ourShader.setMat4("model", model);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//glm::mat4 trans2(1.0);
		//trans = glm::translate(trans2, glm::vec3(0.5f, -0.5f, 0.0f));
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_VERTEX_ARRAY, 0);

		
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
