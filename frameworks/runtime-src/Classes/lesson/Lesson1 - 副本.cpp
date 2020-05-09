
#include "Lesson1.h"
#include "MyUtils.h"

Lesson1::Lesson1(int width, int height)
{

}

 Lesson1::~Lesson1()
{

}

void Lesson1::run()
{
	GLFWwindow* window = MyUtils::createWindow();



	program = MyUtils::createGLProgram("E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_color.vert", "E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_color.frag");
	programLight = MyUtils::createGLProgram("E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_light.vert", "E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/shaders/ccShader_light.frag");

	// NOTE: OpenGL error checks have been omitted for brevity
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	s_texture[0] = LoadGLTextures("textures/login_girl.png", GL_RGBA);
	s_texture[1] = LoadGLTextures("textures/login_girl_n.png", GL_RGB);
	//glBindVertexArray(vertex_buffer);

	m_m = glGetUniformLocation(program, "Modle");
	m_v = glGetUniformLocation(program, "View");
	m_p = glGetUniformLocation(program, "Project");


	CC_TextureID = glGetUniformLocation(program, "CC_Texture0");
	int CC_TextureID1 = glGetUniformLocation(program, "CC_Texture1");
	//lightPosLoc = glGetUniformLocation(program, "lightPos");
	vpos_location = glGetAttribLocation(program, "vPos");
	vnormal_location = glGetAttribLocation(program, "vNormal");
	vpos_texCoord = glGetAttribLocation(program, "a_texCoord");



	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);

	glEnableVertexAttribArray(vnormal_location);
	glVertexAttribPointer(vnormal_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(vpos_texCoord);
	glVertexAttribPointer(vpos_texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 6));
	//glEnableVertexAttribArray(0);



	//glGenBuffers(1, &lightVertex_buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, lightVertex_buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, lightVertex_buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);



	//glBindVertexArray(lightVertex_buffer);

	//glEnableVertexAttribArray(m_lightPos);
	//glVertexAttribPointer(m_lightPos, 3, GL_FLOAT, GL_FALSE, sizeof(lightVertices[0]), (void*)0);
	//glVertexAttribPointer(m_lightPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	m_ml = glGetUniformLocation(programLight, "Modle");
	m_vl = glGetUniformLocation(programLight, "View");
	m_pl = glGetUniformLocation(programLight, "Project");
	//m_lightPos = glGetAttribLocation(programLight, "vlPos");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, s_texture[0]);
	glUniform1i(CC_TextureID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, s_texture[1]);

	glUniform1i(CC_TextureID1, 1);

	//glEnableVertexAttribArray(vpos_texCoord);
	//glVertexAttribPointer(vpos_texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	//glDepthRange( -1,1 );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, s_texture[0]);

	float x = 0.0;


	for (int i = 0; i < 10; i++)
	{
		xa[i] = (rand() % 100 - 50) / 10.0f;
		ya[i] = (rand() % 50 - 30) / 10.0f;
		za[i] = -rand() % 10 - 2;
		ra[i] = rand() % 360 * (3.14159 / 180.0f);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawBox();
		//   drawLight();
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(16);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
