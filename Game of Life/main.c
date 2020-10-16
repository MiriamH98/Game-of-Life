#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "OpenGL.h"
#include <string.h>


float Square[18] =
{
    0.0f, 1.0f, 0.0f,   //NW
    0.0f, 0.0f, 0.0f,   //SW
    1.0f, 0.0f, 0.0f,   //SO

    0.0f,  1.0f, 0.0f,  //NW
    1.0f,  1.0f, 0.0f,  //NO
    1.0f,  0.0f, 0.0f,  //SO
};
//typedef die Matrix um Pointer casten zu können
//typedef int Array2D[xDim][yDim];

void ErrorCallback(int Error, const char* Description)
{
    fprintf(stderr, "Error: %s\n", Description);
}

void framebuffer_size_callback(GLFWwindow* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

void FillDrawable(float Drawable[18])
{
    for (int i = 0; i < 18; i++)
    {
        Drawable[i] = 0.0f;
    }
    
}
//8 Funktionen, die den Wert der der Himmelsrichtung entsprechenden Nachbarn zurück gibt
//fängt Edge-Cases ab und gibt Wert anderen Seite zurück
bool Nof(int x, int y, struct Cell Matrix[xDim][yDim], bool TopEdge)
{
    if (TopEdge==false)
    {
        bool Result = Matrix[x][y+1].Alive;
        return Result;
    }
    else
    {
        bool Result = Matrix[x][0].Alive;
        return Result;
    }
}
bool Wof(int x, int y, struct Cell Matrix[xDim][yDim], bool LeftEdge)
{
    if (LeftEdge==false)
    {
        bool Result = Matrix[x-1][y].Alive;
        return Result;
    }
    else
    {
        bool Result = Matrix[xDim-1][y].Alive;
        return Result;
    }
}
bool Sof(int x, int y, struct Cell Matrix[xDim][yDim], bool BottomEdge)
{
    if (BottomEdge==false)
    {
        bool Result = Matrix[x][y-1].Alive;
        return Result;
    }
    else
    {
        bool Result = Matrix[x][yDim-1].Alive;
        return Result;
    }
}
bool Eof(int x, int y, struct Cell Matrix[xDim][yDim], bool RightEdge)
{
    if (RightEdge==false)
    {
        bool Result = Matrix[x+1][y].Alive;
        return Result;
    }
    else
    {
        bool Result = Matrix[0][y].Alive;
        return Result;
    }
}
bool NWof(int x, int y, struct Cell Matrix[xDim][yDim], bool TopEdge, bool LeftEdge)
{
    if (TopEdge==false)
    {
        if (LeftEdge==false)
        {
            bool Result = Matrix[x-1][y+1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[xDim-1][y+1].Alive;
        return Result;
        }
    }
    else
    {
        if (LeftEdge==false)
        {
            bool Result = Matrix[x-1][0].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[xDim-1][0].Alive;
            return Result;
        }
    }
}
bool NEof(int x, int y, struct Cell Matrix[xDim][yDim], bool TopEdge, bool RightEdge)
{
    if (TopEdge==false)
    {
        if (RightEdge==false)
        {
            bool Result = Matrix[x+1][y+1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[0][y+1].Alive;
            return Result;
        }
    }
    else
    {
        if (RightEdge==false)
        {
            bool Result = Matrix[x+1][0].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[0][0].Alive;
            return Result;
        }
    }
}
bool SWof(int x, int y, struct Cell Matrix[xDim][yDim], bool BottomEdge, bool LeftEdge)
{
    if (BottomEdge==false)
    {
        if (LeftEdge==false)
        {
            bool Result = Matrix[x-1][y-1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[xDim-1][y-1].Alive;
            return Result;
        }
    }
    else
    {
        if (LeftEdge==false)
        {
            bool Result = Matrix[x-1][yDim-1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[xDim-1][yDim-1].Alive;
            return Result;
        }
    }
}
bool SEof(int x, int y, struct Cell Matrix[xDim][yDim], bool BottomEdge, bool RightEdge)
{
    if (BottomEdge==false)
    {
        if (RightEdge==false)
        {
            bool Result = Matrix[x+1][y-1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[0][y-1].Alive;
            return Result;
        }
    }
    else
    {
        if (RightEdge==false)
        {
            bool Result = Matrix[x+1][yDim-1].Alive;
            return Result;
        }
        else
        {
            bool Result = Matrix[0][yDim-1].Alive;
            return Result;
        }
    }
}
//Funktion zur Berechnung der Quadrat-Koordinaten  
void CalcSquareCoord(float Points[18], int x, int y)
{
    float Position = 0.0f;
    float SizeX = 2.0f / (float)xDim; 
    float SizeY = 2.0f / (float)yDim; 
    
      
    
 for (int i = 0; i < 18; i++)//Schleife durch points
 {  
     
    switch(i % 3)
    {
        case 0: //case ändert X-Koordinate
                
            Position = (float)(x) * SizeX;
            if(Square[i] > 0)
            {
                Points[i] = (Position + SizeX) - 1; //ändert in 1.0 
            }
            else
            {
                Points[i] = Position - 1; //ändert in 0.0
            }
           
            break;

        case 1: //case ändert Y-Koordinate
                
            Position = (float)(y) * SizeY;
            if(Square[i] > 0)
            {
                Points[i] = (Position + SizeY) - 1; //ändert in 1.0
            }
            else
            {
                Points[i] = Position - 1; //ändert in 0.0
            }
            
            break;
            
        default: //case behält Z-Koordinate bei
        
            break;
    }
 }
}
//Funktion zur Berechnung der Nachbarn und so Implementierung der Game of Life Regeln
void IterateCells(struct Cell LifeMatrix[xDim][yDim])
{
    //Randfelder theoretisch ohne Nachbarn
    bool LeftEdge = false;
    bool RightEdge = false;
    bool TopEdge = false;
    bool BottomEdge = false;
    short EdgeSum = 0;



    //iteriere von der ersten Ge erationauf die anächste
    for(int x = 0; x < xDim; x++)
    {
        if(x==0)
            {LeftEdge = true;}
        else
            {LeftEdge = false;}

        if(x==xDim-1)
            {RightEdge = true;}
        else
            {RightEdge = false;}
        

        for(int y = 0; y < yDim; y++)
        {
            if(y==0)
                {BottomEdge = true;}
            else
                {BottomEdge = false;}

            if(y==yDim-1)
                {TopEdge = true;}
            else
                {TopEdge = false;}
            
            EdgeSum = 0;
            EdgeSum += Nof(x, y, LifeMatrix, TopEdge);
            EdgeSum += Sof(x, y, LifeMatrix, BottomEdge);
            EdgeSum += Wof(x, y, LifeMatrix, LeftEdge);
            EdgeSum += Eof(x, y, LifeMatrix, RightEdge);
            EdgeSum += NEof(x, y, LifeMatrix, TopEdge, RightEdge);
            EdgeSum += SEof(x, y, LifeMatrix, BottomEdge, RightEdge);
            EdgeSum += SWof(x, y, LifeMatrix, BottomEdge, LeftEdge);
            EdgeSum += NWof(x, y, LifeMatrix, TopEdge, LeftEdge);
            
            if((LifeMatrix[x][y].Alive == true && EdgeSum == 2)||EdgeSum == 3)//3 nachbarn oder 2 und am leben
            {
                LifeMatrix[x][y].NextRound = true;
            }
            else
            {
                LifeMatrix[x][y].NextRound = false;
            }

            
            
        }
                
    } 
    for(int x = 0; x < xDim; x++)
    {
        for(int y = 0; y < yDim; y++)
        {
            LifeMatrix[x][y].Alive = LifeMatrix[x][y].NextRound;
        }        
    }
}

int main()
{

    //2 Matrizen zum gegenseitigen Überschreiben und beibehalten der alten Werte für bestimmte Zeit
    srand(time(NULL));
    struct Cell LifeMatrix[xDim][yDim];

    for(int x = 0; x < xDim; x++)
    {
        for(int y = 0; y < yDim; y++)
        {
            FillDrawable(LifeMatrix[x][y].Drawable);
            LifeMatrix[x][y].Alive = rand() % 2;
            CalcSquareCoord(LifeMatrix[x][y].Drawable, x, y);
        }
    }   
 


    //Quelle: https://www.glfw.org/documentation.html#example-code, Code Treumer/Lorenz
    //Erstellen des Fensters
    GLFWwindow* Window;
    UserData_t UserData =
    {
        .Width = 800,
        .Height = 800,
    };

    //Initialisieren der Bibliothek
    if(!glfwInit())
        printf("Failed to initialize GLFW");

    //Setzen auf Version 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    glfwSetErrorCallback(ErrorCallback);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Erstellen eines glfw Fenster
    Window = glfwCreateWindow(UserData.Width, UserData.Height, "Game of Life", NULL, NULL);
    
    glfwMakeContextCurrent(Window);
    //Verhindern eines Speicherzugriffsfehler
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, UserData.Width, UserData.Height);

    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback); 
    glfwSetWindowUserPointer(Window, &UserData);


    InitOpenGL(Window, LifeMatrix);
    

    while(!glfwWindowShouldClose(Window))
    { 
        DrawMatrix(Window, LifeMatrix);
       // delay(3000);    
        IterateCells(LifeMatrix);

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    glfwDestroyWindow(Window);
    glfwTerminate();
   

    return 0;
}
 