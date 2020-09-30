// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include "OpenGL.h"



void gl_check_error(const char* error_text)
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
            fprintf(stderr, "GLError: %s (%d) \n", error_text, error);
            exit(EXIT_FAILURE);
    }
}

void DrawMatrix(GLFWwindow* window)
{
    //Grundfarbe des Hintergrundes 
    glClearColor(1.0f,1.0f, 1.0f,0.0f);
    gl_check_error("glClearColor");
    glClear(GL_COLOR_BUFFER_BIT);

    //vao, vbo
}

