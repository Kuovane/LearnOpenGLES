#include"MyUtils.h"

#include "io/VxFile.h"

#include <glad/gl.h>
#include <glfw3/glfw3.h>


#include "MyGame.h"
#include "png/png.h"
#define  PRE_PATH "E:/learn/c2dx/cocos2d-x-lite_test/js-template-default/res/"
#include "CCStdC.h"


typedef struct
{
	const unsigned char * data;
	long size;
	int offset;
}tImageSourceData;

GLuint	s_texture[10];

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	tImageSourceData* isource = (tImageSourceData*)png_get_io_ptr(png_ptr);

	if ((int)(isource->offset + length) <= isource->size)
	{
		memcpy(data, isource->data + isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

unsigned char* decodePngData(const unsigned char * data, unsigned long dataLen, unsigned long &nSize, int &width, int &height)
{
	// length of bytes to check if it is a valid png file
#define PNGSIGSIZE  8
	bool ret = false;
	png_byte        header[PNGSIGSIZE] = { 0 };
	png_structp     png_ptr = 0;
	png_infop       info_ptr = 0;
	unsigned char* _data = nullptr;

	do
	{
		// png header len is 8 bytes
		if (dataLen < PNGSIGSIZE) break;

		// check the data is png or not
		memcpy(header, data, PNGSIGSIZE);
		if (png_sig_cmp(header, 0, PNGSIGSIZE))break;

		// init png_struct
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		if (!png_ptr)break;

		// init png_info
		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)break;


		// set the read call back function
		tImageSourceData imageSource;
		imageSource.data = (unsigned char*)data;
		imageSource.size = dataLen;
		imageSource.offset = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		// read png header info

		// read png file info
		png_read_info(png_ptr, info_ptr);

		int _width = png_get_image_width(png_ptr, info_ptr);
		int _height = png_get_image_height(png_ptr, info_ptr);
		width = _width;
		height = _height;
		png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

		//CCLOG("color type %u", color_type);

		// force palette images to be expanded to 24-bit RGB
		// it may include alpha channel
		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		// low-bit-depth grayscale images are to be expanded to 8 bits
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		{
			bit_depth = 8;
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}
		// expand any tRNS chunk data into a full alpha channel
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}
		// reduce images with 16-bit samples to 8 bits
		if (bit_depth == 16)
		{
			png_set_strip_16(png_ptr);
		}

		// Expanded earlier for grayscale, now take care of palette and rgb
		if (bit_depth < 8)
		{
			png_set_packing(png_ptr);
		}
		// update info
		png_read_update_info(png_ptr, info_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);
		int _renderFormat;
		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			//_renderFormat = Image::PixelFormat::I8;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			//_renderFormat = Image::PixelFormat::AI88;
			break;
		case PNG_COLOR_TYPE_RGB:
			//_renderFormat = Image::PixelFormat::RGB888;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			//_renderFormat = Image::PixelFormat::RGBA8888;
			break;
		default:
			break;
		}

		// read png data
		png_size_t rowbytes;
		png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * _height);

		rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		nSize = rowbytes * _height;
		_data = static_cast<unsigned char*>(malloc(nSize * sizeof(unsigned char)));
		if (!_data)
		{
			if (row_pointers != nullptr)
			{
				free(row_pointers);
			}
			break;
		}

		for (unsigned short i = 0; i < _height; ++i)
		{
			row_pointers[i] = _data + i * rowbytes;
		}
		png_read_image(png_ptr, row_pointers);

		png_read_end(png_ptr, nullptr);

		// premultiplied alpha for RGBA8888
		/*if (PNG_PREMULTIPLIED_ALPHA_ENABLED && color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		{
			premultipliedAlpha();
		}
		else
		{
			_hasPremultipliedAlpha = false;
		}*/

		if (row_pointers != nullptr)
		{
			free(row_pointers);
		}

		ret = true;
	} while (0);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}
	return _data;
}


unsigned char* MyUtils::loadPng(const char* fileName, unsigned long &nSize, int &width, int &height)
{
	unsigned long nLen = 0;
	unsigned char* pRawData = (unsigned char*)VxFile::createFileData(fileName, "rb", &nLen);
	if (pRawData)
	{

		auto pData = decodePngData(pRawData, nLen, nSize, width, height);
		delete[] pRawData;
		return pData;
	}
	return nullptr;
}

int MyUtils::LoadGLTextures(std::string sFilePath, unsigned int type)									// Load Bitmaps And Convert To Textures
{
	int Status = false;									// Status Indicator

	unsigned long dataLen = 0;

	std::string sFileName = PRE_PATH + sFilePath;//"textures/container2.png";
	int width, height;
	auto data = loadPng(sFileName.c_str(), dataLen, width, height);
	GLuint textureId = 0;
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (data)
	{
		glGenTextures(1, &textureId);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		delete[] data;
	}


	return textureId;										// Return The Status
}



 GLuint MyUtils::createGLProgram(char* vertFile, char* fragFile)
{
	GLuint  vertex_shader, fragment_shader, program;

	unsigned long  nSize = 0;
	std::string sVert;
	std::string sFrag;
	const char*  vertData = (const char*)VxFile::createFileData(vertFile, "r", &nSize);
	sVert.assign(vertData, nSize);
	const char* fragData = (const char*)VxFile::createFileData(fragFile, "r", &nSize);
	sFrag.assign(fragData, nSize);
	delete[]vertData;
	delete[]fragData;


	vertData = sVert.c_str();
	fragData = sFrag.c_str();



	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertData, NULL);
	glCompileShader(vertex_shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragData, NULL);
	glCompileShader(fragment_shader);


	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glGetShaderiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::program::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return program;
}


 GLFWwindow* MyUtils::createWindow()
 {
	 GLFWwindow* window;
	 glfwSetErrorCallback(error_callback);
	 if (!glfwInit())
		 exit(EXIT_FAILURE);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	 window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	 if (!window)
	 {
		 glfwTerminate();
		 exit(EXIT_FAILURE);
	 }
	 glfwSetKeyCallback(window, key_callback);
	 glfwMakeContextCurrent(window);
	 gladLoadGL(glfwGetProcAddress);
	 glfwSwapInterval(1);

	 return window;
 }
