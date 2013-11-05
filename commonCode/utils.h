/** @file utils.h
 *  @brief useful utilities for opengl based apps
 *
 *	Effects in Games, June 2012
 */
#pragma once

#include "stdafx.h"

using namespace std;
/** logging will be by using simple "printf" function */
#define UTILS_LOG_WITH_PRINTF

#ifdef UTILS_LOG_WITH_PRINTF
	#define LOG(msg, ...) { printf(msg, __VA_ARGS__); printf("\n"); }
	#define LOG_SUCCESS(msg, ...) { printf("SUCCESS: "); printf(msg, __VA_ARGS__); printf("\n"); }
	#define LOG_ERROR(msg, ...) { printf("ERR in %s at line %d: ", __FUNCTION__, __LINE__); printf(msg, __VA_ARGS__); printf("\n"); }
#else
	#define LOG(msg, ...) { }
	#define LOG_SUCCESS(msg, ...) { }
	#define LOG_ERROR(msg, ...) { }
#endif

#ifdef _DEBUG
	#define CHECK_OPENGL_ERRORS() utils::checkGLErrors(__FUNCTION__, __FILE__, __LINE__);
#else
	#define CHECK_OPENGL_ERRORS() 
#endif

namespace utils
{

///////////////////////////////////////////////////////////////////////////////
bool initGL(bool vsync);

void calculateFps(float *fps);

void updateTimer(double *deltaTime, double *appTime, const double REFRESH_TIME = 1.0/60.0);

bool checkGLErrors(const char *func, const char * file, int line);

inline float randFloatRange(float a, float b);

inline const char *fileNameFromPath(const char *filePath);

} // namespce utils	

///////////////////////////////////////////////////////////////////////////////
// inline

inline float utils::randFloatRange(float a, float b)
{
	return a + (float)rand()/(float)RAND_MAX * (b-a);
}

inline const char *utils::fileNameFromPath(const char *filePath)
{
	const char *s = strrchr(filePath, '\\');
	if (s == NULL) 
		s = strrchr(filePath, '/');
	return s == NULL ? filePath : s+1;
}

#ifndef M_PI
    #define M_PI 3.141592
#endif

// paths
#define TEXTURES_PATH "textures"
#define SHADERS_PATH "shaders"
#define SKYBOX_SHADERS_PATH "shaders/skybox"

//concat strings on compile time
#define CONCAT(str1, str2) str1"/"str2

#define SAFE_DELETE(pPtr) { delete pPtr; pPtr = NULL; }

namespace helpers {

	namespace ogl {
		/**
		 * Wrapper for OGL texture setter
		 */
		inline void setTexture(int gl_code, GLuint& tex){
			glActiveTexture(gl_code);
			glBindTexture(GL_TEXTURE_2D, tex);
		}

		/**
		 * Wrapper for SOIL texture Loader
		 *
		 * @param path
		 * @return (boolean| texture obj)
		 */
		inline GLuint loadTexture(const char* path){
			GLuint tex =  SOIL_load_OGL_texture(
				path,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS  
			);
			if (tex == 0) {
				std::cout << "ERROR\tNo file at path loaded " << path << std::endl;
				return false;
			} else {
				std::cout << "OK\tFile at path loaded " << path << std::endl;
				return tex;
			}
		}

		/**
		  * Wrapper for buffer creator
		  */
		inline void setupBuffer(int glOperation, GLenum& type , GLintptr size, const void* ptr, int operation){
			glGenBuffers(1,&type);
			glBindBuffer(glOperation, type);
			glBufferData(glOperation, size, ptr, operation);
		}
	}

	/**
	  * Wrapper for deletion
	  */
	template <class T>
	inline void freeMap(T& map) {
		for (T::iterator i = map.begin(); i != map.end();) {
			SAFE_DELETE((*i).second);
			map.erase (i++);
		}
	}
}