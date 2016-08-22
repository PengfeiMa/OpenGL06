#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QWidget>
#include <qopengl.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <GL/glu.h>
#include <QImage>


namespace UI {
class NeHeWidget;
}

class NeHeWidget : public QGLWidget
{
    Q_OBJECT

public:

  NeHeWidget( QWidget* parent = 0, const char* name = 0, bool fs = false );
  void keyPressEvent( QKeyEvent *e );
  ~NeHeWidget();

protected:

  bool fullscreen;
  GLfloat rTri;
  GLfloat rQuad;

  GLfloat xRot, yRot, zRot;
  GLfloat zoom;//场景深入屏幕的距离
    GLfloat xSpeed, ySpeed;
    GLuint texture[3];//存储纹理
    GLuint filter;//表明的是使用哪个纹理

    bool light;//现在是否使用光源
    bool blend;//说明现在是否使用融合

  void loadGLTextures();//在这个函数中我们会载入指定的图片并生成相应当纹理。

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );


};

#endif // NEHEWIDGET_H
