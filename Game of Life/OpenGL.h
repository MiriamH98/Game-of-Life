#ifndef OPENGL_H
#define OPENGL_H

#include <GLFW/glfw3.h>
#include "glad.h"

//definiere Matrix Größe
#define xdim 10
#define ydim 10

//Vektoren zum Zeichnen
typedef struct
{
    GLuint vao;
    GLuint vbo;
} user_data_t;



//Fehlererkennung
void gl_check_error(const char* error_text);


//Funktionen der OpenGL.c
void DrawMatrix(GLFWwindow* window);

#endif