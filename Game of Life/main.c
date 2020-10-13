#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "OpenGL.h"
#include <string.h>


struct cell
{ //int x,y
    uint32_t drawable;
    bool alive;
    bool nextround;
    int size;
    int grid;
};

//typedef die Matrix um Pointer casten zu können
//typedef int Array2D[xdim][ydim];

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

//8 Funktionen, die den Wert der der Himmelsrichtung entsprechenden Nachbarn zurück gibt
//fängt Edge-Cases ab und gibt Wert anderen Seite zurück
bool Nof(int x, int y, struct cell Matrix[xdim][ydim], bool topedge)
{
    if (topedge==false)
    {
        bool result = Matrix[x][y+1].alive;
        return result;
    }
    else
    {
        bool result = Matrix[x][0].alive;
        return result;
    }
}
bool Wof(int x, int y, struct cell Matrix[xdim][ydim], bool leftedge)
{
    if (leftedge==false)
    {
        bool result = Matrix[x-1][y].alive;
        return result;
    }
    else
    {
        bool result = Matrix[xdim-1][y].alive;
        return result;
    }
}
bool Sof(int x, int y, struct cell Matrix[xdim][ydim], bool bottomedge)
{
    if (bottomedge==false)
    {
        bool result = Matrix[x][y-1].alive;
        return result;
    }
    else
    {
        bool result = Matrix[x][ydim-1].alive;
        return result;
    }
}
bool Eof(int x, int y, struct cell Matrix[xdim][ydim], bool rightedge)
{
    if (rightedge==false)
    {
        bool result = Matrix[x+1][y].alive;
        return result;
    }
    else
    {
        bool result = Matrix[0][y].alive;
        return result;
    }
}
bool NWof(int x, int y, struct cell Matrix[xdim][ydim], bool topedge, bool leftedge)
{
    if (topedge==false)
    {
        if (leftedge==false)
        {
            bool result = Matrix[x-1][y+1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[xdim-1][y+1].alive;
        return result;
        }
    }
    else
    {
        if (leftedge==false)
        {
            bool result = Matrix[x-1][0].alive;
            return result;
        }
        else
        {
            bool result = Matrix[xdim-1][0].alive;
            return result;
        }
    }
}
bool NEof(int x, int y, struct cell Matrix[xdim][ydim], bool topedge, bool rightedge)
{
    if (topedge==false)
    {
        if (rightedge==false)
        {
            bool result = Matrix[x+1][y+1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[0][y+1].alive;
            return result;
        }
    }
    else
    {
        if (rightedge==false)
        {
            bool result = Matrix[x+1][0].alive;
            return result;
        }
        else
        {
            bool result = Matrix[0][0].alive;
            return result;
        }
    }
}
bool SWof(int x, int y, struct cell Matrix[xdim][ydim], bool bottomedge, bool leftedge)
{
    if (bottomedge==false)
    {
        if (leftedge==false)
        {
            bool result = Matrix[x-1][y-1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[xdim-1][y-1].alive;
            return result;
        }
    }
    else
    {
        if (leftedge==false)
        {
            bool result = Matrix[x-1][ydim-1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[xdim-1][ydim-1].alive;
            return result;
        }
    }
}
bool SEof(int x, int y, struct cell Matrix[xdim][ydim], bool bottomedge, bool rightedge)
{
    if (bottomedge==false)
    {
        if (rightedge==false)
        {
            bool result = Matrix[x+1][y-1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[0][y-1].alive;
            return result;
        }
    }
    else
    {
        if (rightedge==false)
        {
            bool result = Matrix[x+1][ydim-1].alive;
            return result;
        }
        else
        {
            bool result = Matrix[0][ydim-1].alive;
            return result;
        }
    }
}
/*
float square[]=
{
    0.0f, 1.0f 0.0f,  //NW
    0.0f, 0.0f, 0.0f,   //SW
    1.0f, 0.0f, 0.0f,   //SO

    0.0f,  1.0f, 0.0f,  //NW
    1.0f,  1.0f, 0.0f,  //NO
    1.0f, 0.0f, 0.0f,   //SO
};
    for i := 0; i < len(points); i++ {
        var position float32
        var size float32
        switch i % 3 {
        case 0:
                //size = 1.0 / float32(columns)
                position = float32(x) * size
        case 1:
                //size = 1.0 / float32(rows)
                position = float32(y) * size
        default:
                continue
        }

        if points[i] < 0 {
                points[i] = (position * 2) - 1
        } else {
                points[i] = ((position + size) * 2) - 1
        }
    }
*/
void CalcSquareCoord(user_data_t* user_data, float points[18], int x, int y)
{
    float position = 0.0f;
    float sizex = 2.0f / (float)xdim; 
    float sizey = 2.0f / (float)ydim; 
    points[] = square[];
 for (int i = 0; i < 18; i++)
 {
        //0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16
    switch(i % 3)
    {
        case 0:
                
            position = (float)(x) * sizex;
            if(points[i] > 0)
            {
                points[i] = (position + sizex) - 1;//1
            }
            else
            {
                points[i] = position - 1;//0
            }
            break;

        case 1:
                
            position = (float)(y) * sizey;
            if(points[i] > 0)
            {
                points[i] = (position + sizey) - 1;//1
            }
            else
            {
                points[i] = position - 1;//0
            }
            break;
            
        default:
        
            break;
    }
 }
}


int main()
{

    //2 Matrizen zum gegenseitigen Überschreiben und beibehalten der alten Werte für bestimmte Zeit
    srand(time(NULL));
    struct cell LifeMatrix[xdim][ydim];
     for(int x = 0; x < xdim; x++)
    {
        for(int y = 0; y < ydim; y++)
        {
            LifeMatrix[x][y].alive = rand() % 2;
        }
    }   

    //Randfelder theoretisch ohne Nachbarn
    bool leftedge = false;
    bool rightedge = false;
    bool topedge = false;
    bool bottomedge = false;
    short edgesum = 0;



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
            edgesum += Nof(x, y, LifeMatrix, topedge);
            edgesum += Sof(x, y, LifeMatrix, bottomedge);
            edgesum += Wof(x, y, LifeMatrix, leftedge);
            edgesum += Eof(x, y, LifeMatrix, rightedge);
            edgesum += NEof(x, y, LifeMatrix, topedge, rightedge);
            edgesum += SEof(x, y, LifeMatrix, bottomedge, rightedge);
            edgesum += SWof(x, y, LifeMatrix, bottomedge, leftedge);
            edgesum += NWof(x, y, LifeMatrix, topedge, leftedge);
            
            if((LifeMatrix[x][y].alive == true && edgesum == 2)||edgesum == 3)//3 nachbarn oder 2 und am leben
            {
                LifeMatrix[x][y].nextround = 1;
            }
            else
            {
                LifeMatrix[x][y].nextround = 0;
            }
            
        }
                
    } 


    //Quelle: https://www.glfw.org/documentation.html#example-code, Code Treumer/Lorenz
    //Create window
    GLFWwindow* window;
    user_data_t user_data =
    {
        .width = 800,
        .height = 800,
    };

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
    window = glfwCreateWindow(user_data.width, user_data.height, "Game of Life", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    // WICHTIG! Nötig für Speicherzugriff OpenGL!
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, user_data.width, user_data.height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    glfwSetWindowUserPointer(window, &user_data);
    
    InitOpenGL(window, square);
    

    while(!glfwWindowShouldClose(window))
    {
           
      /*  
       CalcSquareCoordinates(x, y);
      */
        DrawMatrix(window, square);
        
        
        // Swap the buffers to avoid tearing:
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
   
   //glad_glAttachShader(GL_VERTEX_SHADER);
   //glad_glAttachShader(GL_FRAGMENT_SHADER);

    return 0;
}
