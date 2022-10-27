/*
 The iterated function system fern.

 Source file to be used with
 Cunningham, Computer Graphics: Programming in OpenGL for Visual Communication, Prentice-Hall, 2007

 Intended for class use only
 */
#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <time.h>
#include <GL/glut.h>





 //∂®“Â ‰≥ˆ¥∞ø⁄µƒ¥Û–°
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500

GLenum  G_shadingMode;    //«–ªª¡Ω÷÷√˜∞µƒ£ Ω

//…„œÒª˙¿ÎŒÔÃÂµƒæ‡¿Î
float G_fDistance = 3.6f;
//ŒÔÃÂµƒ–˝◊™Ω«∂»
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

////////////////////////////////////////////////
//π‚’’≤Œ ˝
float G_vLit0Position[4] = { 5.0f, 0.0f, 5.0f, 1.0f };
float G_vLit0Ambient[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float G_vLit0Diffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float G_vLit0Specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
float G_vMaterialSpecu[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

float G_vLit1Position[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

////////////////////////////////////////////////
void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);

//œÏ”¶º¸≈Ã ‰»Î, ¥”∂¯…Ë∂®ŒÔÃÂ“∆Ω¸“∆‘∂“‘º∞–˝◊™µƒªÿµ˜∫Ø ˝
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);


////////////////////////////////////////////////
//÷˜∫Ø ˝
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    //≥ı ºªØOPENGLœ‘ æ∑Ω Ω
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //…Ë∂®OPENGL¥∞ø⁄Œª÷√∫Õ¥Û–°
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    //¥Úø™¥∞ø⁄
    glutCreateWindow("OpenGL");
    printf("…œ°¢œ¬º¸---»∆x÷·–˝◊™\n");
    printf("◊Û°¢”“º¸---»∆y÷·–˝◊™\n");
    printf("a/Aº¸------¿≠Ω¸/Õ∆‘∂\n");
    printf("1/2º¸------Flat/SmoothªÊ÷∆ƒ£ Ω\n");

    //µ˜”√≥ı ºªØ∫Ø ˝
    myinit();

    //…Ë∂®¥∞ø⁄¥Û–°±‰ªØµƒªÿµ˜∫Ø ˝
    glutReshapeFunc(myReshape);

    //…Ë∂®º¸≈Ãøÿ÷∆µƒªÿµ˜∫Ø ˝
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    //ø™ ºOPENGLµƒ—≠ª∑
    glutDisplayFunc(display);
    //    glutIdleFunc(display);

    glutMainLoop();

    return 0;
}

////////////////////////////////////////////////
//”√ªß≥ı ºªØ∫Ø ˝
void myinit(void)
{
    //your initialization code
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    //    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);    //À´√Êπ‚’’°£≤Ë∫¯µƒ∑®∑ΩœÚ∫√œÒ «∑¥µƒ.

    glShadeModel(GL_SMOOTH);
    //    glShadeModel(GL_FLAT);
}

//¥∞ø⁄¥Û–°±‰ªØ ±µƒªÿµ˜∫Ø ˝
void myReshape(GLsizei w, GLsizei h)
{
    //…Ë∂® ”«¯
    glViewport(0, 0, w, h);

    //…Ë∂®Õ∏ ”∑Ω Ω
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 30.0);
    //    gluPerspective(60.0, 1.0, 1.0, 30.0);
    //  glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 30.0);
}

//√øËÂOpenGL∂ºª·µ˜”√’‚∏ˆ∫Ø ˝£¨”√ªß”¶∏√∞—œ‘ æ¥˙¬Î∑≈‘⁄’‚∏ˆ∫Ø ˝÷–
void display(void)
{
    //…Ë÷√«Â≥˝∆¡ƒªµƒ—’…´£¨≤¢«Â≥˝∆¡ƒª∫Õ…Ó∂»ª∫≥Â
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //    glClearDepth(0.8f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(G_shadingMode);

    ////////////////////////////////////////////////
    //…Ë÷√π‚’’
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, G_vLit0Position);        //…Ë÷√π‚‘¥µƒŒª÷√
    glLightfv(GL_LIGHT0, GL_AMBIENT, G_vLit0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, G_vLit0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, G_vLit0Specular);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, G_vMaterialSpecu);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0f);

    //…Ë÷√≥…ƒ£–Õæÿ’Ûƒ£ Ω
    glMatrixMode(GL_MODELVIEW);

    //‘ÿ»Îµ•ŒªªØæÿ’Û
    glLoadIdentity();

    //◊¯±Í÷––ƒœÚZ÷·∆Ω“∆-G_fDistance ( π◊¯±Í÷––ƒŒª”⁄…„œÒª˙«∞∑Ω)
    glTranslatef(0.0, 0.0, -G_fDistance);
    glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
    glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);

    ////////////////////////////////////////////////
    //ªÊ÷∆ŒÔÃÂ

    //ª≠“ª∏ˆ»˝Ω«–Œ

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0, -1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-2.0, 1.0f, 0.0f);
    glEnd();

    //ª≠“ª∏ˆ≤Ë∫¯
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.8f, 0.0f, 0.0f);
    glutWireTeapot(1.0);
    //glutSolidTeapot(1.0);
    //glutSolidTeapot(0.5);
    //glutSolidSphere(1.0, 20, 20);

    //Ωªªª«∞∫Ûª∫≥Â«¯
    glutSwapBuffers();
}


void processSpecialKeys(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        G_fAngle_horizon -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        G_fAngle_horizon += 5.0f;
        break;
    case GLUT_KEY_UP:
        G_fAngle_vertical -= 5.0f;
        break;
    case GLUT_KEY_DOWN:
        G_fAngle_vertical += 5.0f;
        break;
    }
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
    case 97:    //"a"
        G_fDistance -= 0.3f;
        break;
    case 65:        //"A"
        G_fDistance += 0.3f;
        break;
    case 49:    //"1"
        G_shadingMode = GL_FLAT;
        break;
    case 50:    //"2"
        G_shadingMode = GL_SMOOTH;
        break;
    case 27:    //"esc"
        exit(0);
    }

    glutPostRedisplay();
}
