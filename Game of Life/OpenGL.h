#ifndef OPENGL_H
#define OPENGL_H
#include "glad.h"
#include <GLFW/glfw3.h>


//definiere Matrix Größe
#define xdim 10
#define ydim 10


//Vektoren zum Zeichnen
typedef struct
{
    GLint width;
    GLint height;
    GLuint ShaderProgram;
    GLuint vao;
    GLuint vbo;
} user_data_t;

typedef float square[18];

//Fehlererkennung
void gl_check_error(const char* error_text);


//Funktionen der OpenGL.c
void InitShader(user_data_t* user_data);
void InitVao(user_data_t* user_data, float* square);
void InitOpenGL(GLFWwindow* window, float* square);
void DrawMatrix(GLFWwindow* window, float square[]);

#endif