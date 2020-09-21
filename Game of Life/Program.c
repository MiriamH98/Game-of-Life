#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "glad.h"


//definiere Matrix Größe
#define xdim 10
#define ydim 10

//typedef die Matrix um Pointer casten zu können
typedef int Array2D[xdim][ydim];

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int Nof(int x, int y, Array2D *Matrix, bool topedge)
{
    if (topedge=false)
    {
        int result = (*Matrix)[x][y+1];
        return result;
    }
    else
    {
        int result = (*Matrix)[x][0];
        return result;
    }
}
int Wof(int x, int y, Array2D *Matrix, bool leftedge)
{
    if (leftedge=false)
    {
        int result = (*Matrix)[x-1][y];
        return result;
    }
    else
    {
        int result = (*Matrix)[xdim-1][y];
        return result;
    }
}
int Sof(int x, int y, Array2D *Matrix, bool bottomedge)
{
    if (bottomedge=false)
    {
        int result = (*Matrix)[x][y-1];
        return result;
    }
    else
    {
        int result = (*Matrix)[x][ydim-1];
        return result;
    }
}
int Eof(int x, int y, Array2D *Matrix, bool rightedge)
{
    if (rightedge=false)
    {
        int result = (*Matrix)[x+1][y];
        return result;
    }
    else
    {
        int result = (*Matrix)[0][y];
        return result;
    }
}
int NWof(int x, int y, Array2D *Matrix, bool topedge, bool leftedge)
{
    if (topedge=false)
    {
        if (leftedge=false)
        {
            int result = (*Matrix)[x-1][y+1];
            return result;
        }
        else
        {
        int result = (*Matrix)[xdim-1][y+1];
        return result;
        }
    }
    else
    {
        if (leftedge=false)
        {
            int result = (*Matrix)[x-1][0];
            return result;
        }
        else
        {
            int result = (*Matrix)[xdim-1][0];
            return result;
        }
    }
}
int NEof(int x, int y, Array2D *Matrix, bool topedge, bool rightedge)
{
    if (topedge=false)
    {
        if (rightedge=false)
        {
            int result = (*Matrix)[x+1][y+1];
            return result;
        }
        else
        {
            int result = (*Matrix)[0][y+1];
            return result;
        }
    }
    else
    {
        if (rightedge=false)
        {
            int result = (*Matrix)[x+1][0];
            return result;
        }
        else
        {
            int result = (*Matrix)[0][0];
            return result;
        }
    }
}
int SWof(int x, int y, Array2D *Matrix, bool bottomedge, bool leftedge)
{
    if (bottomedge=false)
    {
        if (leftedge=false)
        {
            int result = (*Matrix)[x-1][y-1];
            return result;
        }
        else
        {
            int result = (*Matrix)[xdim-1][y-1];
            return result;
        }
    }
    else
    {
        if (leftedge=false)
        {
            int result = (*Matrix)[x-1][ydim-1];
            return result;
        }
        else
        {
            int result = (*Matrix)[xdim-1][ydim-1];
            return result;
        }
    }
}
int SEof(int x, int y, Array2D *Matrix, bool bottomedge, bool rightedge)
{
    if (bottomedge=false)
    {
        if (rightedge=false)
        {
            int result = (*Matrix)[x+1][y-1];
            return result;
        }
        else
        {
            int result = (*Matrix)[0][y-1];
            return result;
        }
    }
    else
    {
        if (rightedge=false)
        {
            int result = (*Matrix)[x+1][ydim-1];
            return result;
        }
        else
        {
            int result = (*Matrix)[0][ydim-1];
            return result;
        }
    }
}
int main()
{



    //2 Matrizen zum gegenseitigen Überschreiben und beibehalten der alten Werte für bestimmte Zeit
    int LifeMatrix1[xdim][ydim];//why not bool?
    int LifeMatrix2[xdim][ydim];

    //Randfelder theoretisch ohne Nachbarn
    bool leftedge = false;
    bool rightedge = false;
    bool topedge = false;
    bool bottomedge = false;
    short edgesum = 0;

//füllen der Matix mit random bool Werten
    srand(time(NULL));
    for(int x = 0; x < xdim; x++)
    {
        for(int y = 0; y < ydim; y++)
        {
            LifeMatrix1[x][y] = rand() % 2;
        }
    }
/*
//Printen der Matrix
Array2D *currentMatrix = &LifeMatix1
    for(int x = 0; x < xdim; x++)
    {
        for(int y = 0; y < ydim; y++)
        {
            printf((*currentMatrix)[x][y]);
        }
    }
*/
//iteriere von der einen Matrix auf die andere
Array2D *currentMatrix = &LifeMatrix1;
Array2D *nextMatrix = &LifeMatrix2;
    for(int x = 0; x < xdim; x++)
    {
        if(x=0)
            {leftedge = true;}
        else
            {leftedge = false;}

        if(x=xdim-1)
            {rightedge = true;}
        else
            {rightedge = false;}
        

        for(int y = 0; y < ydim; y++)
        {
            if(y=0)
                {bottomedge = true;}
            else
                {bottomedge = false;}

            if(y=ydim-1)
                {topedge = true;}
            else
                {topedge = false;}
            
            edgesum = 0;
            edgesum += Nof(x, y, *currentMatrix, topedge);
            edgesum += Sof(x, y, *currentMatrix, bottomedge);
            edgesum += Wof(x, y, *currentMatrix, leftedge);
            edgesum += Eof(x, y, *currentMatrix, rightedge);
            edgesum += NEof(x, y, *currentMatrix, topedge, rightedge);
            edgesum += SEof(x, y, *currentMatrix, bottomedge, rightedge);
            edgesum += SWof(x, y, *currentMatrix, bottomedge, leftedge);
            edgesum += NWof(x, y, *currentMatrix, topedge, leftedge);
            /*
            if((*currentmatrix[x][y] =1 && edgesum = 2)||edgesum = 3)//3 nachbarn oder 2 und am leben
            {
                *nextmatrix[x][y] = 1;
            }
            else
            {
                *nextmatrix[x][y] = 0;
            }
            */
        }
                
    }

    //Quelle: https://www.glfw.org/documentation.html#example-code, Code Treumer/Lorenz
    //Create window
    GLFWwindow* window;

    //Initialize library
    if(!glfwInit())
        printf("Failed to initialize GLFW");

    //We want at least OpenGL 4.1:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    glfwSetErrorCallback(error_callback);
    
    //Enable forward-compatibility and use the core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a GLFW window
    window = glfwCreateWindow(800, 600, "Game of Life", NULL, NULL);
    
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);


    while(!glfwWindowShouldClose(window))
    {
        //DrawMatrix(window, xdim, ydim);
        glClearColor(1.0,1.0,1.0,1.0);
        // Swap the buffers to avoid tearing:
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
