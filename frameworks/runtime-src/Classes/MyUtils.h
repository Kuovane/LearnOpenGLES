
#pragma once
#include <glad/gl.h>
#include <glfw3/glfw3.h>
#include <VxExternal.h>
#include <stdlib.h>
#include <stdio.h>
#include "CCStdC.h"
/**
 @brief    The cocos2d Application.
 
 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  MyUtils
{
public:
	static GLFWwindow* createWindow(void* keyCallBack = nullptr);
	static int LoadGLTextures(std::string sFilePath, unsigned int type);
	static unsigned char* loadPng(const char* fileName, unsigned long &nSize, int &width, int &height);

	static GLuint createGLProgram(char* vertFile, char* fragFile);

};
