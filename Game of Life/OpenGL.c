// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include "OpenGL.h"
#include <string.h>

void gl_check_error(const char* error_text)
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
            fprintf(stderr, "GLError: %s (%d) \n", error_text, error);
            exit(EXIT_FAILURE);
    }
}

void check_error(int condition, const char* error_text)
{
	if (!condition)
	{
		fprintf(stderr, "%s\n", error_text);
		exit(EXIT_FAILURE);
	}
}

//Shader in String umwandeln zur Verwendung in gl-Funktion glShaderSource
char* ReadShaderToString(const char* path)
{
    //Shader File:
    FILE* file = fopen(path, "rb");

    //Pointer auf Ende für Dateigröße
    int success = fseek(file, 0,SEEK_END);

    //Lesen der Dateigröße
    long size = ftell(file);
    check_error(size >= 0, "Failed to determine file size.");

    //Pointer zurück auf Anfang
    rewind(file);

    //Speicher für Buffer
    char* buffer = malloc(size + 1);
    check_error(buffer != NULL, "Failed to allocate buffer.");

    //Dateiinhalt in Buffer schreiben
    size_t FileIntoBuffer = fread(buffer, size, 1, file);
    check_error(FileIntoBuffer == 1, "Failed to read file.");

    //Datei schließen
    success = fclose(file);
    check_error(success == 0, "Failed to close file.");

    buffer[size] = '\0';

    return buffer;



}

GLuint CreateShader(GLenum type, const char* shader_path, const char* shader_tag)
{
    GLuint shader = glCreateShader(type);
    gl_check_error("glCreateShader");

    char *ShaderSource = ReadShaderToString(shader_path);
    glShaderSource(shader, 1, (const char**)&ShaderSource, NULL);
    gl_check_error("GLShaderSource");

    free(ShaderSource);

    glCompileShader(shader);
    gl_check_error("glCompileShader");

    // Check the compilation status:
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	gl_check_error("glGetShaderiv");

	if (success)
	{
		return shader;
	}

	// Extract the length of the error message (including '\0'):
	GLint info_length = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
	gl_check_error("glGetShaderiv");

	if (info_length > 1)
	{
		// Extract the message itself:
		char* info = malloc(info_length);
		//check_error(info != NULL, "Failed to allocate memory for error message.");

		glGetShaderInfoLog(shader, info_length, NULL, info);
		gl_check_error("glGetShaderInfoLog");

		fprintf(stderr, "Error compiling shader (%s): %s\n", shader_tag, info);
		free(info);
	}
	else
	{
		fprintf(stderr, "No info log from the shader compiler :(\n");
	}

	exit(EXIT_FAILURE);
}

void InitShader(user_data_t* user_data)
{
    //Vertex Shader erstellen
    GLuint VertexShader = CreateShader(GL_VERTEX_SHADER, "vertex.glsl", "Vertex shader");

    //Fragment Shader erstellen
    GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER, "fragment.glsl", "Fragment shader");

    //Shader Programm erstellen:
    GLuint ShaderProgram = glCreateProgram();
    gl_check_error("glCreateProgram");

    //Shader an Programm heften
    glAttachShader(ShaderProgram, VertexShader);
    gl_check_error("glAttachShader [vertex]");

    glAttachShader(ShaderProgram, FragmentShader);
    gl_check_error("glAttachShader [fragment]");

    //Linken
    glLinkProgram(ShaderProgram);
    gl_check_error("glLinkProgram");

    //Fehlertest:
    int success;
    char infolog[512];

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infolog);
        printf("Error linking shader program: %s", infolog);
    }

    glUseProgram(ShaderProgram);
    gl_check_error("glUseProgram");

    // Detach the shaders after linking:
	glDetachShader(ShaderProgram, VertexShader);
	gl_check_error("glDetachShader [vertex]");

	glDetachShader(ShaderProgram, FragmentShader);
	gl_check_error("glDetachShader [fragment]");

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader); 

    user_data->ShaderProgram = ShaderProgram;



}

//Vao, Vbo
void InitVao(user_data_t* user_data, float* square)
{
    //Anlegen und Binden eines Vertex Buffer Objektes
    GLuint vbo;
    glGenBuffers(1, &vbo);
    gl_check_error("glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl_check_error("glBindBuffer");

    //AUF USER DATA ANPASSEN??
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, square, GL_STATIC_DRAW);
    gl_check_error("glBufferData");


    user_data->vbo = vbo;


    GLuint vao;
    glGenVertexArrays(1, &vao);
    gl_check_error("glGenVertexArray");
    
    glBindVertexArray(vao);
    gl_check_error("glBindVertexArray");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(vao);
    

    user_data->vao = vao;


}

void InitOpenGL(GLFWwindow* window, float* square)
{
    user_data_t* user_data = glfwGetWindowUserPointer(window);
    InitShader(user_data);
    InitVao(user_data, square);
    
    
}

/*int makeCells() [][]*cell
{
    cell := make([][]*cell, xdim, xdim)
    for ( x = 0; x < xdim; x++)
    {
        for ( y = 0; y < ydim; y++)
        {
            c:= newCell(x,y)
            cells[x] = append(cells[x], c)
        }
        
    }
    return cells

}*/


void DrawMatrix(GLFWwindow* window, float* square)
{
    
    //Grundfarbe des Hintergrundes 
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gl_check_error("glClearColor");
    glClear(GL_COLOR_BUFFER_BIT);
    gl_check_error("glClear");

    //Viereck zeichnen aus 2 Dreiecken
    glDrawArrays(GL_TRIANGLES, 0, 6);
    gl_check_error("glDrawArrays");

    //Zellen als Matrix aus Vierecken

 
}



