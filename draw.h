#ifndef DRAW_H
#define DRAW_H

#include <QGLWidget>
#include <QTimer>

#include "grid.h"

class Draw: public QGLWidget
{
public:
    //Draw();
    Draw(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void draw(int xy);
    Grid map;
    QTimer *time;

};

#endif // DRAW_H
