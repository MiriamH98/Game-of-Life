#ifndef OPENGL_H
#define OPENGL_H
#include "glad.h"
#include <GLFW/glfw3.h>


//definiere Matrix Größe
#define xDim 100
#define yDim 100

struct Cell
{
    float Drawable[18]; //enthält die Vao-Daten
    bool Alive;
    bool NextRound;
};

//Vektoren zum Zeichnen
typedef struct
{
    GLint Width;
    GLint Height;
    GLuint ShaderProgram;
    GLuint Vao;
    GLuint Vbo;
} UserData_t;


//Fehlererkennung
void GlCheckError(const char* error_text);


//Funktionen der OpenGL.c
void InitShader(UserData_t* UserData);
void MakeVao(UserData_t* UserData, struct Cell Matrix[xDim][yDim]);
void InitVao(UserData_t* UserData, float* Square);
void InitOpenGL(GLFWwindow* Window, struct Cell Matrix[xDim][yDim]);
void DrawMatrix(GLFWwindow* Window, struct Cell Matrix[xDim][yDim]);

#endif