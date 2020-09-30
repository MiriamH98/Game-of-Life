#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "OpenGL.h"



//typedef die Matrix um Pointer casten zu können
//typedef int Array2D[xdim][ydim];

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int Nof(int x, int y, int Matrix[xdim][ydim], bool topedge)
{
    if (topedge==false)
    {
        int result = Matrix[x][y+1];
        return result;
    }
    else
    {
        int result = Matrix[x][0];
        return result;
    }
}
int Wof(int x, int y, int Matrix[xdim][ydim], bool leftedge)
{
    if (leftedge==false)
    {
        int result = Matrix[x-1][y];
        return result;
    }
    else
    {
        int result = Matrix[xdim-1][y];
        return result;
    }
}
int Sof(int x, int y, int Matrix[xdim][ydim], bool bottomedge)
{
    if (bottomedge==false)
    {
        int result = Matrix[x][y-1];
        return result;
    }
    else
    {
        int result = Matrix[x][ydim-1];
        return result;
    }
}
int Eof(int x, int y, int Matrix[xdim][ydim], bool rightedge)
{
    if (rightedge==false)
    {
        int result = Matrix[x+1][y];
        return result;
    }
    else
    {
        int result = Matrix[0][y];
        return result;
    }
}
int NWof(int x, int y, int Matrix[xdim][ydim], bool topedge, bool leftedge)
{
    if (topedge==false)
    {
        if (leftedge==false)
        {
            int result = Matrix[x-1][y+1];
            return result;
        }
        else
        {
        int result = Matrix[xdim-1][y+1];
        return result;
        }
    }
    else
    {
        if (leftedge==false)
        {
            int result = Matrix[x-1][0];
            return result;
        }
        else
        {
            int result = Matrix[xdim-1][0];
            return result;
        }
    }
}
int NEof(int x, int y, int Matrix[xdim][ydim], bool topedge, bool rightedge)
{
    if (topedge==false)
    {
        if (rightedge==false)
        {
            int result = Matrix[x+1][y+1];
            return result;
        }
        else
        {
            int result = Matrix[0][y+1];
            return result;
        }
    }
    else
    {
        if (rightedge==false)
        {
            int result = Matrix[x+1][0];
            return result;
        }
        else
        {
            int result = Matrix[0][0];
            return result;
        }
    }
}
int SWof(int x, int y, int Matrix[xdim][ydim], bool bottomedge, bool leftedge)
{
    if (bottomedge==false)
    {
        if (leftedge==false)
        {
            int result = Matrix[x-1][y-1];
            return result;
        }
        else
        {
            int result = Matrix[xdim-1][y-1];
            return result;
        }
    }
    else
    {
        if (leftedge==false)
        {
            int result = Matrix[x-1][ydim-1];
            return result;
        }
        else
        {
            int result = Matrix[xdim-1][ydim-1];
            return result;
        }
    }
}
int SEof(int x, int y, int Matrix[xdim][ydim], bool bottomedge, bool rightedge)
{
    if (bottomedge==false)
    {
        if (rightedge==false)
        {
            int result = Matrix[x+1][y-1];
            return result;
        }
        else
        {
            int result = Matrix[0][y-1];
            return result;
        }
    }
    else
    {
        if (rightedge==false)
        {
            int result = Matrix[x+1][ydim-1];
            return result;
        }
        else
        {
            int result = Matrix[0][ydim-1];
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

/* Test, ob LifeMatrix1 zufälligen Inhalt hat
for (int x = 0; x < xdim; x++)
{
    for (int y = 0; y < ydim; y++)
    {
        printf("%d", LifeMatrix1[x][y]);
    }
    
}*/

/*
//Printen der Matrix
Array2D *currentMatrix = &LifeMatrix1;
    for(int x = 0; x < xdim; x++)
    {
        for(int y = 0; y < ydim; y++)
        {
            printf("%d", *(currentMatrix)[x][y]);
        }
    }
*/
//iteriere von der einen Matrix auf die andere

    for(int x = 0; x < xdim; x++)
    {
        if(x==0)
            {leftedge = true;}
        else
            {leftedge = false;}

        if(x==xdim-1)
            {rightedge = true;}
        else
            {rightedge = false;}
        

        for(int y = 0; y < ydim; y++)
        {
            if(y==0)
                {bottomedge = true;}
            else
                {bottomedge = false;}

            if(y==ydim-1)
                {topedge = true;}
            else
                {topedge = false;}
            
            edgesum = 0;
            edgesum += Nof(x, y, LifeMatrix1, topedge);
            edgesum += Sof(x, y, LifeMatrix1, bottomedge);
            edgesum += Wof(x, y, LifeMatrix1, leftedge);
            edgesum += Eof(x, y, LifeMatrix1, rightedge);
            edgesum += NEof(x, y, LifeMatrix1, topedge, rightedge);
            edgesum += SEof(x, y, LifeMatrix1, bottomedge, rightedge);
            edgesum += SWof(x, y, LifeMatrix1, bottomedge, leftedge);
            edgesum += NWof(x, y, LifeMatrix1, topedge, leftedge);
            
            if((LifeMatrix1[x][y] == 1 && edgesum == 2)||edgesum == 3)//3 nachbarn oder 2 und am leben
            {
                LifeMatrix2[x][y] = 1;
            }
            else
            {
                LifeMatrix2[x][y] = 0;
            }
            
        }
                
    } 
//Printen der Matrix
/*Array2D *currentMatrix = &LifeMatrix1;
    for(int x = 0; x < xdim; x++)
    {
        for(int y = 0; y < ydim; y++)
        {
            printf((*currentMatrix)[x][y]);
        }
    }
*/

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
    // WICHTIG! Nötig für Speicherzugriff OpenGL!
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    

    while(!glfwWindowShouldClose(window))
    {
        DrawMatrix(window);
        
        // Swap the buffers to avoid tearing:
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
   

return 0;
}
