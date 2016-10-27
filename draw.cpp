#include "draw.h"
#include "gConst.h"
#include "grid.h"

#include <iostream>
using namespace std;

#include <QGLWidget>
#include <QTimer>

Draw::Draw(QWidget *parent):QGLWidget(parent)
{
    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(update()));
    time->start(10);
}

void Draw::draw(int xy)
{
    char** board = map.GetBoard();
    map.Move();

    for(int i = 0; i < xy; i++)
    {
        for(int j = 0; j < xy; j++)
        {
            Coords c(i,j);

            if(board[i][j] == PREY)              //prey: cyan
                glColor3f(0.0f, 1.0f, 1.0f);
            else if(board[i][j] == PREDATOR)     //predator: purple
                glColor3f(0.5f, 0.0f, 1.0f);
            else if(board[i][j] == EMPTY)        //empty: black
                glColor3f(0.0f, 0.0f, 0.0f);
            else if(board[i][j] == BOMBER)       //bomber: red
                glColor3f(1.0f, 0.0f, 0.0f);
            else if(board[i][j] == GOD)          //god: green
                glColor3f(0.0f, 1.0f, 0.0f);

            glVertex2f(     i*xy,    j*xy); // BOTTOM LEFT
            glVertex2f((i+1)*xy ,    j*xy); // BOTTOM RIGHT
            glVertex2f((i+1)*xy ,(j+1)*xy); // TOP RIGHT
            glVertex2f(     i*xy,(j+1)*xy); // TOP LEFT
        }
    }
}


void Draw::initializeGL()
{
    glClearColor(0,0,0,0); // Sets background to black
}

void Draw::resizeGL(int w, int h)
{
    double Aspect;

    if(h==0)
        h=1;

    glViewport(0,0, w, h);

    Aspect = (double)w/(double)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Draw::paintGL()
{
    double xy = X_SIZE;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glOrtho(0, xy*xy, 0, xy*xy, -1.0, 1.0);

    glBegin(GL_QUADS); // Calls Quad

    draw(xy);

    glEnd();

}
