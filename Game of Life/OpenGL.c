// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "OpenGL.h"
#include <string.h>



void GlCheckError(const char* ErrorText)
{
    GLenum Error = glGetError();
    if(Error != GL_NO_ERROR)
    {
            fprintf(stderr, "GLError: %s (%d) \n", ErrorText, Error);
            exit(EXIT_FAILURE);
    }
}

void CheckError(int Condition, const char* ErrorText)
{
	if (!Condition)
	{
		fprintf(stderr, "%s\n", ErrorText);
		exit(EXIT_FAILURE);
	}
}

//Shader in String umwandeln zur Verwendung in gl-Funktion glShaderSource
char* ReadShaderToString(const char* Path)
{
    //Shader File:
    FILE* File = fopen(Path, "rb");

    //Pointer auf Ende für Dateigröße
    int Success = fseek(File, 0,SEEK_END);

    //Lesen der Dateigröße
    long Size = ftell(File);
    CheckError(Size >= 0, "Failed to determine File size.");

    //Pointer zurück auf Anfang
    rewind(File);

    //Speicher für Buffer
    char* Buffer = malloc(Size + 1);
    CheckError(Buffer != NULL, "Failed to allocate buffer.");

    //Dateiinhalt in Buffer schreiben
    size_t FileIntoBuffer = fread(Buffer, Size, 1, File);
    CheckError(FileIntoBuffer == 1, "Failed to read File.");

    //Datei schließen
    Success = fclose(File);
    CheckError(Success == 0, "Failed to close File.");

    Buffer[Size] = '\0';

    return Buffer;



}

GLuint CreateShader(GLenum type, const char* ShaderPath, const char* ShaderTag)
{
    GLuint Shader = glCreateShader(type);
    GlCheckError("glCreateShader");

    char *ShaderSource = ReadShaderToString(ShaderPath);
    glShaderSource(Shader, 1, (const char**)&ShaderSource, NULL);
    GlCheckError("GLShaderSource");

    free(ShaderSource);

    glCompileShader(Shader);
    GlCheckError("glCompileShader");

    // Check the compilation status:
	GLint Success;

	glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
	GlCheckError("glGetShaderiv");

	if (Success)
	{
		return Shader;
	}

	// Extract the length of the Error message (including '\0'):
	GLint InfoLength = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLength);
	GlCheckError("glGetShaderiv");

	if (InfoLength > 1)
	{
		// Extract the message itself:
		char* Info = malloc(InfoLength);
		//CheckError(info != NULL, "Failed to allocate memory for Error message.");

		glGetShaderInfoLog(Shader, InfoLength, NULL, Info);
		GlCheckError("glGetShaderInfoLog");

		fprintf(stderr, "Error compiling shader (%s): %s\n", ShaderTag, Info);
		free(Info);
	}
	else
	{
		fprintf(stderr, "No info log from the shader compiler :(\n");
	}

	exit(EXIT_FAILURE);
}

void InitShader(UserData_t* UserData)
{
    //Vertex Shader erstellen
    GLuint VertexShader = CreateShader(GL_VERTEX_SHADER, "vertex.glsl", "Vertex shader");

    //Fragment Shader erstellen
    GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER, "fragment.glsl", "Fragment shader");

    //Shader Programm erstellen:
    GLuint ShaderProgram = glCreateProgram();
    GlCheckError("glCreateProgram");

    //Shader an Programm heften
    glAttachShader(ShaderProgram, VertexShader);
    GlCheckError("glAttachShader [vertex]");

    glAttachShader(ShaderProgram, FragmentShader);
    GlCheckError("glAttachShader [fragment]");

    //Linken
    glLinkProgram(ShaderProgram);
    GlCheckError("glLinkProgram");

    //Fehlertest:
    int Success;
    char InfoLog[512];

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if(!Success)
    {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
        printf("Error linking shader program: %s", InfoLog);
    }

    glUseProgram(ShaderProgram);
    GlCheckError("glUseProgram");

    // Shader nach dem Linken vom Program entfernen:
	glDetachShader(ShaderProgram, VertexShader);
	GlCheckError("glDetachShader [vertex]");

	glDetachShader(ShaderProgram, FragmentShader);
	GlCheckError("glDetachShader [fragment]");

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader); 

    UserData->ShaderProgram = ShaderProgram;
}

//Abgeänderte InitVao, die die Dreieckskoordinaten in der Matrix ausliest und in den Buffer läd 
void MakeVao(UserData_t* UserData, struct Cell Matrix[xDim][yDim])
{
	
    float Temp[18*xDim*yDim];//Alle Daten müssen gleichzeitig in den Buffer geladen werden, weshalb sie beim rauslesen zwischengespeichert werden
    
    for(int x = 0; x < xDim; x++)
    {
        for(int y = 0; y < yDim; y++)
        {
            int k = 18 * (x * yDim + y);           
            for(int i = 0; i < 18; i++)
            {                
                Temp[k + i] = Matrix[x][y].Drawable[i];//Herauslesen von drawable Daten von Lifematrix              
            }            
        }
    }   
    //Anlegen und Binden eines Vertex Buffer Objektes
    GLuint Vbo;
    glGenBuffers(1, &Vbo);
    GlCheckError("glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    GlCheckError("glBindBuffer");

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18 * xDim * yDim, Temp, GL_STATIC_DRAW);
    GlCheckError("glBufferData");


    UserData->Vbo = Vbo;


    GLuint Vao;
    glGenVertexArrays(1, &Vao);
    GlCheckError("glGenVertexArray");
    
    glBindVertexArray(Vao);
    GlCheckError("glBindVertexArray");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(Vao);
    

    UserData->Vao = Vao;


}
//Vao, Vbo Funktionen
void InitVao(UserData_t* UserData, float* Square)
{
    //Anlegen und Binden eines Vertex Buffer Objektes
    GLuint Vbo;
    glGenBuffers(1, &Vbo);
    GlCheckError("glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    GlCheckError("glBindBuffer");

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, Square, GL_STATIC_DRAW);
    GlCheckError("glBufferData");


    UserData->Vbo = Vbo;


    GLuint Vao;
    glGenVertexArrays(1, &Vao);
    GlCheckError("glGenVertexArray");
    
    glBindVertexArray(Vao);
    GlCheckError("glBindVertexArray");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(Vao);
    

    UserData->Vao = Vao;


}
//Funktion zur Initialisierung der OpenG
void InitOpenGL(GLFWwindow* Window, struct Cell Matrix[xDim][yDim])
{
    UserData_t* UserData = glfwGetWindowUserPointer(Window);
    InitShader(UserData);
    MakeVao(UserData, Matrix);
}

void DrawMatrix(GLFWwindow* Window, struct Cell Matrix[xDim][yDim])
{
    
    //Grundfarbe des Hintergrundes 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GlCheckError("glClearColor");
    glClear(GL_COLOR_BUFFER_BIT);
    GlCheckError("glClear");

    //Für jede Zelle, zeichne die zugehörigen 2 Dreiecke aus den Buffer wenn die Zelle am Leben ist
    for (int x = 0; x < xDim; x++)
    {
        for (int y = 0; y < yDim; y++)
        {
            if((Matrix[x][y].Alive) == true)
            {
                glDrawArrays(GL_TRIANGLES, 6 * (x * yDim + y), 6); //findet die zugehörigen Dreiecke im Buffer und zeichnet beide
                GlCheckError("glDrawArrays");
            }
            
        }
        
    }
    

 
}



