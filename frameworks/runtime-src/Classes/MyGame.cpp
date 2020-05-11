
#include "io/VxFile.h"

#include <glad/gl.h>
#include <glfw3/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include "MyGame.h"
#include "png/png.h"
#include "CCStdC.h"
#include "lesson/Lesson1.h"
#include "lesson/Lesson2.h"
#include "lesson/Lesson3.h"
#include "lesson/Lesson4.h"
#include "lesson/Lesson5.h"
#include "lesson/Lesson6.h"

static const struct
{
	float x, y,z;
	float r, g, b;
	float u, v;
}  vertices[] = {
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
};



/*
struct float2 {
	float x;
	float y;
};

struct Vertex
{
	float2      pos;
	float2      uv;
};

GLfloat x = 100;
GLfloat y = 100;
GLfloat w = 400;
GLfloat h = 400;

Vertex aryReverseUv[] =
{
	float2{ x, y },         float2(0, 1),
	float2{ x + w, y },     float2(1, 1),
	float2{ x, y + h },     float2(0, 0),
	float2{ x + w, y + h }, float2(1, 0),
};

Vertex ary[] =
{
	float2{ x, y },         float2(0, 0),
	float2{ x + w, y },     float2(1, 0),
	float2{ x, y + h },     float2(0, 1),
	float2{ x + w, y + h }, float2(1, 1),
};


*/


vec3 pointLightPositions[] = {
	{0.7f,  0.2f,  2.0f},
	{2.3f, -3.3f, -4.0f},
	{-4.0f,  2.0f, -12.0f},
	{0.0f,  0.0f, -3.0f}
};

MyGame::MyGame(int width, int height)
{

}
MyGame::~MyGame()
{

}

 void MyGame::drawLight()
{
	 mat4x4 m, v, p, t, mvp;

	 glUseProgram(programLight);



		 mat4x4_identity(m);
		 mat4x4_rotate_X(m, m, (3.1415926 / 180) * -55);//(float)glfwGetTime());
		
		 mat4x4_translate(m, 1.2f, 1.0f, -2.0f);
		 //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		 mat4x4_scale_aniso(m, m, 0.2, 0.2, 0.2);
		// mat4x4_translate(t, 0.5, 0, -1.5);

		 mat4x4_perspective(p, 45, ratio, 0.1, 100);
		 //mat4x4_mul(mvp, v, m);
		 //mat4x4_mul(mvp, p, mvp);
		 //x = x + 0.001;
		 GLfloat radius = 10.0f;
		 //GLfloat camX = sin(glfwGetTime()) * radius;
		 //GLfloat camZ = cos(glfwGetTime()) * radius;
		 float eye[3] = { 0,0,1 };
		 float center[3] = { 0,0,0 };
		 float up[3] = { 0,1,0 };


		 mat4x4_look_at(v, eye, center, up);
		 //mat4x4_mul(v, v, t);


		 glUniformMatrix4fv(m_ml, 1, GL_FALSE, (const GLfloat*)m);
		 glUniformMatrix4fv(m_vl, 1, GL_FALSE, (const GLfloat*)v);
		 glUniformMatrix4fv(m_pl, 1, GL_FALSE, (const GLfloat*)p);
		 //glBindVertexArray(lightVertex_buffer);
		// glBindBuffer(GL_ARRAY_BUFFER, lightVertex_buffer);
		 //glEnableVertexAttribArray(m_lightPos);
		// glVertexAttribPointer(m_lightPos, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);

		 glDrawArrays(GL_TRIANGLES, 0, 36);
	 
}

 void MyGame::drawBox()
 {

	 mat4x4 m, v, p, t, mvp;

	 glUseProgram(program);

	 static float x = -4.0f, dx = 0.05;
	 x = x + dx;
	 if (x > 4 || x < -4.0) { dx = -dx; }
	 float eye[3] = { 0,1,3 };
	 float center[3] = { 0,0,0 };
	 float up[3] = { 0,1,0 };

	 glUniform1f(glGetUniformLocation(program, "light.constant"), 1.0f);
	 glUniform1f(glGetUniformLocation(program, "light.linear"), 0.09);
	 glUniform1f(glGetUniformLocation(program, "light.quadratic"), 0.032);



	 // directional light
	 glUniform3f(glGetUniformLocation(program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	 glUniform3f(glGetUniformLocation(program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	 glUniform3f(glGetUniformLocation(program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
	 glUniform3f(glGetUniformLocation(program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
	 // point light 1
	 glUniform3f(glGetUniformLocation(program, "pointLights[0].position"), pointLightPositions[0][0], pointLightPositions[0][1], pointLightPositions[0][2]);
	 glUniform3f(glGetUniformLocation(program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
	 glUniform3f(glGetUniformLocation(program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
	 glUniform3f(glGetUniformLocation(program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
	 glUniform1f(glGetUniformLocation(program, "pointLights[0].constant"), 1.0f);
	 glUniform1f(glGetUniformLocation(program, "pointLights[0].linear"), 0.09);
	 glUniform1f(glGetUniformLocation(program, "pointLights[0].quadratic"), 0.032);
	 // point light 2
	 glUniform3f(glGetUniformLocation(program, "pointLights[1].position"), pointLightPositions[1][0], pointLightPositions[1][1], pointLightPositions[1][2] );
	 glUniform3f(glGetUniformLocation(program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
	 glUniform3f(glGetUniformLocation(program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
	 glUniform3f(glGetUniformLocation(program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
	 glUniform1f(glGetUniformLocation(program, "pointLights[1].constant"), 1.0f);
	 glUniform1f(glGetUniformLocation(program, "pointLights[1].linear"), 0.09);
	 glUniform1f(glGetUniformLocation(program, "pointLights[1].quadratic"), 0.032);
	// point light 3
	glUniform3f(glGetUniformLocation(program, "pointLights[2].position"), pointLightPositions[2][0], pointLightPositions[2][1], pointLightPositions[2][2]);
	glUniform3f(glGetUniformLocation(program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].linear"), 0.09);
	glUniform1f(glGetUniformLocation(program, "pointLights[2].quadratic"), 0.032);
	// point light 4
	glUniform3f(glGetUniformLocation(program, "pointLights[3].position"), pointLightPositions[3][0], pointLightPositions[3][1], pointLightPositions[3][2]);
	glUniform3f(glGetUniformLocation(program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].linear"), 0.09);
	glUniform1f(glGetUniformLocation(program, "pointLights[3].quadratic"), 0.032);


	// spotLight
	glUniform3f(glGetUniformLocation(program, "spotLight.position"), eye[0], eye[1], eye[2]);
	glUniform3f(glGetUniformLocation(program, "spotLight.direction"), center[0], center[1], -2.0);
	glUniform3f(glGetUniformLocation(program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(program, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(program, "spotLight.cutOff"), cos(12.5f*0.01745329251994329576923690768489));
	glUniform1f(glGetUniformLocation(program, "spotLight.outerCutOff"), cos(15.0f*0.01745329251994329576923690768489));

	for (int i = 0; i < 1; i++)
	{
		mat4x4_identity(m);
		//mat4x4_rotate_X(m, m, ra[i]);//(float)glfwGetTime());
	   // mat4x4_rotate_Y(m, m, x);

		//mat4x4_translate(m, x, 0, 0);
		//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

		mat4x4_scale_aniso(m, m, 2,2,2);
	    
		//mat4x4_translate_in_place(m, xa[i], ya[i],za[i]);
		
		//mat4x4_rotate(m, m, 0, 1, 3, 20*i);

		mat4x4_perspective(p, 45, ratio, 0.1, 100);
		//mat4x4_mul(mvp, v, m);
		//mat4x4_mul(mvp, p, mvp);
		//x = x + 0.001;
		GLfloat radius = 10.0f;
		//GLfloat camX = sin(glfwGetTime()) * radius;
		//GLfloat camZ = cos(glfwGetTime()) * radius;


		mat4x4_look_at(v, eye, center, up);
		//mat4x4_rotate_X(v, v, (3.1415926 / 180) * 55);
		//mat4x4_mul(v, v, t);

		//vec3 lightPos = vec3(1.2f,1.0f, 2.0f);

		glUniformMatrix4fv(m_m, 1, GL_FALSE, (const GLfloat*)m);
		glUniformMatrix4fv(m_v, 1, GL_FALSE, (const GLfloat*)v);
		glUniformMatrix4fv(m_p, 1, GL_FALSE, (const GLfloat*)p);
		vec3 lightPos;
		lightPos[0] = -4.0f;
		lightPos[1] = -1.2f;
		lightPos[2] = 3.0f;

		
		


		GLint viewPosLoc = glGetUniformLocation(program, "viewPos");
		glUniform3f(viewPosLoc, eye[0], eye[1], eye[2]);


		//GLint matAmbientLoc = glGetUniformLocation(program, "material.ambient");
		//GLint matDiffuseLoc = glGetUniformLocation(program, "material.diffuse");
		//GLint matSpecularLoc = glGetUniformLocation(program, "material.specular");
		GLint matShineLoc = glGetUniformLocation(program, "material.shininess");

		//glUniform3f(matAmbientLoc, 0.0f, 0.1f, 0.06f);
		//glUniform3f(matDiffuseLoc, 0.0f, 0.50980392f, 0.50980392f);
		//glUniform1i(matDiffuseLoc, 0);
		//glUniform1i(matSpecularLoc, 1);
		glUniform1f(matShineLoc, 32.0f);



		GLint lightAmbientLoc = glGetUniformLocation(program, "light.ambient");
		GLint lightDiffuseLoc = glGetUniformLocation(program, "light.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(program, "light.specular");
		GLint lightPositionLoc = glGetUniformLocation(program, "light.position");

		glUniform3f(lightAmbientLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightDiffuseLoc, 1.0f, 1.0f, 1.0f);// 让我们把这个光调暗一点，这样会看起来更自然
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		//glUniform3f(lightPositionLoc, x, 0.5f, 3.0f);



		//glBindVertexArray(vertex_buffer);
		//glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glEnableVertexAttribArray(vpos_location);
	//	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}


void MyGame::run()
{
	//Lesson1::run();
	Lesson6::run();
}

bool MyGame::applicationDidFinishLaunching()
{
	return  true;
}


void MyGame::applicationDidEnterBackground()
{

 }


void MyGame::applicationWillEnterForeground()
{

 }
