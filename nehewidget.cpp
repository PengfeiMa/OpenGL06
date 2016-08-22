#include "nehewidget.h"



GLfloat lightAmbient[4] = { 0.5, 0.5, 0.5, 1.0 };//环境光
GLfloat lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };//漫射光
GLfloat lightPosition[4] = { 0.0, 0.0, 2.0, 1.0 };//光源位置

NeHeWidget::NeHeWidget( QWidget* parent, const char* name, bool fs )
    : QGLWidget( parent )
{
    xRot = yRot = zRot = 0.0;
    zoom = -5.0;
    xSpeed = ySpeed = 0.0;
    filter = 0;

    light = false;
    blend = false;

    rTri = 0.0;
    rQuad = 0.0;
    fullscreen = fs;
    setGeometry( 0, 0, 640, 480 );//设置窗口的位置，即左上角为(0,0)点，大小为640*480。
//  setCaption( "NeHe's OpenGL Framework" );//设置窗口的标题为“NeHe's OpenGL Framework”。
    setWindowTitle("NeHe's OpenGL Framework");
    if ( fullscreen )
         showFullScreen();

}//这个是构造函数，parent就是父窗口部件的指针，name就是这个窗口部件的名称，fs就是窗口是否最大化。
NeHeWidget::~NeHeWidget()
{
}//这个是析构函数。


void NeHeWidget::initializeGL()
{
    loadGLTextures();  //  载入纹理。

    glEnable( GL_TEXTURE_2D );
    glShadeModel( GL_SMOOTH );//这一行启用smooth shading(阴影平滑)
    qglClearColor( Qt::black );//这一行设置清除屏幕时所用的颜色也不是最暗
    glClearDepth( 1.0 );//设置深度缓存。
    glEnable( GL_DEPTH_TEST );//启用深度测试。
    glDepthFunc( GL_LEQUAL );//所作深度测试的类型。
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    glLightfv( GL_LIGHT1, GL_AMBIENT, lightAmbient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition );

    glEnable( GL_LIGHT1 );//启用光源

    glColor4f( 1.0, 1.0, 1.0, 0.4 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );


}


void NeHeWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//清楚屏幕和深度缓存。
    glLoadIdentity();//重置当前的模型观察矩阵。

    glTranslatef( 0.0,  0.0, zoom );

    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );

    glBindTexture( GL_TEXTURE_2D, texture[filter] );
    glBegin( GL_QUADS );//  开始绘制四边形。
    glNormal3f( 0.0, 0.0, 1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );

    glNormal3f( 0.0, 0.0, -1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );

    glNormal3f( 0.0, 1.0, 0.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );

    glNormal3f( 0.0, -1.0, 0.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );

    glNormal3f( 1.0, 0.0, 0.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );

    glNormal3f( -1.0, 0.0, 0.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glEnd(); //四边形绘制结束

    xRot += xSpeed;
     yRot += ySpeed;




}

void NeHeWidget::loadGLTextures()
{
    QImage tex[3], buf[3];
   if ( !buf[0].load("D:/D/OpenGLlearn/OpenGL05/q8.jpg"  ) )//载入纹理图片。这里使用了QImage类。
   {
       qWarning( "Could not read image file, using single-color instead." );
       QImage dummy( 128, 128, QImage::Format_RGB32 );
       dummy.fill( Qt::green );
       buf[0] = dummy;       
   }
   tex[0] = QGLWidget::convertToGLFormat( buf[0] );

   if ( !buf[1].load("D:/D/OpenGLlearn/OpenGL05/q7.jpg"  ) )//载入纹理图片。这里使用了QImage类。
   {
       qWarning( "Could not read image file, using single-color instead." );
       QImage dummy( 128, 128, QImage::Format_RGB32 );
       dummy.fill( Qt::green );
       buf[1] = dummy;       
   }
   tex[1] = QGLWidget::convertToGLFormat( buf[1] );

   if ( !buf[2].load("D:/D/OpenGLlearn/OpenGL05/q6.jpg"  ) )//载入纹理图片。这里使用了QImage类。
   {
       qWarning( "Could not read image file, using single-color instead." );
       QImage dummy( 128, 128, QImage::Format_RGB32 );
       dummy.fill( Qt::green );
       buf[2] = dummy;      
   }
   tex[2] = QGLWidget::convertToGLFormat( buf[2] );



   glGenTextures( 3, &texture[0] );//创建3个纹理
   glBindTexture( GL_TEXTURE_2D, texture[0] );
   glTexImage2D( GL_TEXTURE_2D, 0, 3, tex[0].width(), tex[0].height(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, tex[0].bits() );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

   glBindTexture( GL_TEXTURE_2D, texture[1] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex[1].width(), tex[1].height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex[1].bits() );

    glBindTexture( GL_TEXTURE_2D, texture[2] );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, tex[2].width(), tex[2].height(), GL_RGBA, GL_UNSIGNED_BYTE, tex[2].bits() );
 }

void NeHeWidget::resizeGL( int width, int height )
{
  if ( height == 0 )
  {
    height = 1;
  }
  glViewport( 0, 0, (GLint)width, (GLint)height );
  glMatrixMode( GL_PROJECTION );//选择投影矩阵。
  glLoadIdentity();//重置投影矩阵
  gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );//建立透视投影矩阵。
  //很重要

  glMatrixMode( GL_MODELVIEW );//选择模型观察矩阵。
}


void NeHeWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
      {
          case Qt::Key_L:
            light = !light;
            if ( !light )
            {
              glDisable( GL_LIGHTING );
            }
            else
            {
              glEnable( GL_LIGHTING );
            }
            updateGL();
            break;         // 按下了L键，就可以切换是否打开光源。
          case Qt::Key_F:
            filter += 1;;
            if ( filter > 2 )
            {
              filter = 0;
            }
            updateGL();
            break;       //按下了F键，就可以转换一下所使用的纹理（就是变换了纹理滤波方式的纹理）。
          case Qt::Key_PageUp:
            zoom -= 0.2;
            updateGL();
            break;      //按下了PageUp键，将木箱移向屏幕内部。
          case Qt::Key_PageDown:
            zoom += 0.2;
            updateGL();
            break;   // 按下了PageDown键，将木箱移向屏幕外部。
          case Qt::Key_Up:
            xSpeed -= 0.01;
            updateGL();
            break;
        //按下了Up方向键，减少xSpeed。
          case Qt::Key_Down:
            xSpeed += 0.01;
            updateGL();
            break;
       // 按下了Dowm方向键，增加xSpeed。
          case Qt::Key_Right:
            ySpeed += 0.01;
            updateGL();
            break;
        //按下了Right方向键，增加ySpeed。
          case Qt::Key_Left:
            ySpeed -= 0.01;
            updateGL();
            break;
       // 按下了Left方向键，减少ySpeed。

        case Qt::Key_F2:
            fullscreen = !fullscreen;
            if ( fullscreen )
            {
              showFullScreen();
            }
            else
            {
              showNormal();
              setGeometry( 0, 0, 640, 480 );
            }
            update();
            break;
          case Qt::Key_Escape:
            close();
          case Qt::Key_R:
            update();break;
    case Qt::Key_B:
        blend = !blend;
        if ( blend )
        {
          glEnable( GL_BLEND );
          glDisable( GL_DEPTH_TEST );
        }
        else
        {
          glDisable( GL_BLEND );
          glEnable( GL_DEPTH_TEST );
        }
        updateGL();



      }


}

