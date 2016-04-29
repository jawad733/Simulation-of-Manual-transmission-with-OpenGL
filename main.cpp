

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define SOLID_CLOSED_CYLINDER1(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
glTranslatef(-3.0f,-2.0f,-10.0f);\
gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
glRotatef(180, 1,0,0); \
gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
glRotatef(180, 1,0,0); \
glTranslatef(0.0f, 0.0f, HEIGHT); \
gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
glTranslatef(0.0f, 0.0f, -HEIGHT);

#define SOLID_CLOSED_CYLINDER2(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
glTranslatef(-3.0f,4.0f,-13.0f);\
gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
glRotatef(180, 1,0,0); \
gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
glRotatef(180, 1,0,0); \
glTranslatef(0.0f, 0.0f, HEIGHT); \
gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
glTranslatef(0.0f, 0.0f, -HEIGHT);

#define SOLID_CLOSED_CYLINDER3(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
glTranslatef(-3.0f,4.0f,-5.0f);\
gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
glRotatef(180, 1,0,0); \
gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
glRotatef(180, 1,0,0); \
glTranslatef(0.0f, 0.0f, HEIGHT); \
gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
glTranslatef(0.0f, 0.0f, -HEIGHT);

/**

  Draw a gear wheel.  You'll probably want to call this function when
  building a display list since we do a lot of trig here.

  Input:  inner_radius - radius of hole at center
          outer_radius - radius at center of teeth
          width - width of gear
          teeth - number of teeth
          tooth_depth - depth of tooth

 **/

static void
gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
  GLint teeth, GLfloat tooth_depth)
{
  GLint i;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;

  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2.0;
  r2 = outer_radius + tooth_depth / 2.0;

  da = 2.0 * M_PI / teeth / 4.0;

  glShadeModel(GL_FLAT);

  glNormal3f(0.0, 0.0, 1.0);

  /* draw front face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  /* draw front sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  glNormal3f(0.0, 0.0, -1.0);

  /* draw back face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
  }
  glEnd();

  /* draw back sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  /* draw outward faces of teeth */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
    glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
    glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

  glShadeModel(GL_SMOOTH);

  /* draw inside radius cylinder */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glNormal3f(-cos(angle), -sin(angle), 0.0);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
  }
  glEnd();

}

static GLfloat view_rotx = 0.0, view_roty = 90.0, view_rotz = 0.0;
static GLint gear1, gear2, gear3, gear4, gear5,gear6,gear7,gear8,gear9,gear10;
static GLfloat angle = 0.0;

static GLuint limit;
static GLuint count = 1;

int flag1 ;

static GLfloat color1[4] =
  {0.5, 0.5, 0.5, 1.0};
static GLfloat color2[4] =
  {0.3, 0.3, 0.3, 1.0};
static GLfloat color3[4] =
  {0.5, 0.5, 0.5, 1.0};

static void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glPushMatrix();
  glRotatef(view_rotx, 1.0, 0.0, 0.0);
  glRotatef(view_roty, 0.0, 1.0, 0.0);
  glRotatef(view_rotz, 0.0, 0.0, 1.0);


    //Input Shaft
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
    GLUquadric *quadric2 = gluNewQuadric();
    gluQuadricDrawStyle(quadric2, GLU_FILL);
    SOLID_CLOSED_CYLINDER2(quadric2, 1.0f, 1.0f, 5.0f, 20, 20)
    gluDeleteQuadric(quadric2);
    glPopMatrix();

    //Counter Shaft
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    GLUquadric *quadric1 = gluNewQuadric();
    gluQuadricDrawStyle(quadric1, GLU_FILL);
    SOLID_CLOSED_CYLINDER1(quadric1, 1.0f, 1.0f, 20.0f, 20, 20)
    gluDeleteQuadric(quadric1);
    glPopMatrix();

    //Output shaft
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    GLUquadric *quadric3 = gluNewQuadric();
    gluQuadricDrawStyle(quadric3, GLU_FILL);
    SOLID_CLOSED_CYLINDER3(quadric3, 1.0f, 1.0f, 15.0f, 20, 20)
    gluDeleteQuadric(quadric3);
    glPopMatrix();

  //First gear on counter shaft
  glPushMatrix();
  glTranslatef(-3.0, -2.0, -9.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glCallList(gear1);
  glPopMatrix();

    /*glColor3f(0.7,0.7,0.7);
    glLineWidth(5.0);
  glBegin(GL_LINES);
  glVertex3f(-8.0,-8.0,0.0);
  glVertex3f(8.0,8.0,0.0);
  glEnd();*/

  //Second gear on counter shaft
  glPushMatrix();
  glTranslatef(-3.0, -2.0, -4.0);
  glRotatef(angle - 9.0, 0.0, 0.0, 1.0);
  glCallList(gear2);
  glPopMatrix();

  //Third gear on counter shaft
  glPushMatrix();
  glTranslatef(-3.0, -2.0, 0.0);
  glRotatef(angle - 9.0, 0.0, 0.0, 1.0);
  glCallList(gear8);
  glPopMatrix();

  //Fourth gear on counter shaft
  glPushMatrix();
  glTranslatef(-3.0, -2.0, 4.0);
  glRotatef(angle - 9.0, 0.0, 0.0, 1.0);
  glCallList(gear4);
  glPopMatrix();

  //Fifth gear on counter shaft
  glPushMatrix();
  glTranslatef(-3.0, -2.0, 8.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glCallList(gear3);
  glPopMatrix();

  //First gear on output shaft
  glPushMatrix();
  glTranslatef(-3.0, 4.0, -4.0);
  glRotatef(-angle/2.0 - 9.0, 0.0, 0.0, 1.0);
  glCallList(gear5);
  glPopMatrix();

  //Second gear on output shaft
  glPushMatrix();
  glTranslatef(-3.0, 4.0, 0.0);
  glRotatef(-angle/1.4 - 20.0, 0.0, 0.0, 1.0);
  glCallList(gear7);
  glPopMatrix();

  //Third gear on output shaft
  glPushMatrix();
  glTranslatef(-3.0, 4.0, 4.0);
  glRotatef(-angle*1.4 - 20.0, 0.0, 0.0, 1.0);
  glCallList(gear9);
  glPopMatrix();

  //Fourth gear on output shaft
  glPushMatrix();
  glTranslatef(-3.0, 4.0, 8.0);
  glRotatef(-angle*2.0 - 20.0, 0.0, 0.0, 1.0);
  glCallList(gear10);
  glPopMatrix();

  //Input Shaft Gear
  glPushMatrix();
  glTranslatef(-3.0, 4.0, -9.0);
  glRotatef(-2.0*angle - 9.0, 0.0, 0.0, 1.0);
  glCallList(gear6);
  glPopMatrix();


  glPopMatrix();

  glutSwapBuffers();

  count++;
  if (count == limit) {
    exit(0);
  }
}

void bitmap_output(int x,int y,char *string,void * font)
 {
 int len,i;
 glRasterPos2f(x,y);
 len=(int)strlen(string);
 for(i=0;i<len;i++)
 {
 glutBitmapCharacter(font,string[i]);
 }
}


void name(void)
{
 glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1000,0,700,-500,500);
	glClearColor(0.1,0.1,0.1,1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1,1,1);
 bitmap_output(250,530,"A MINI PROJECT ON...",GLUT_BITMAP_TIMES_ROMAN_24);
 glColor3f(0.5,0.8,0);
 bitmap_output(220,480,"MANUAL TRANSMISSION",GLUT_BITMAP_TIMES_ROMAN_24);
 glColor3f(0,1,1);
 bitmap_output(100,390,"By",GLUT_BITMAP_HELVETICA_18);
 glColor3f(1,0,0);
 bitmap_output(100,360,"Jawad Ahmed (1PE13CS064)",GLUT_BITMAP_HELVETICA_18);
 glColor3f(1,1,0);
  bitmap_output(100,330,"Bhargav (1PE13CS044)",GLUT_BITMAP_HELVETICA_18);
 glColor3f(0,1,1);

 glColor3f(1,0,1);
 //bitmap_output(350,240,"Guides",GLUT_BITMAP_TIMES_ROMAN_24);
 glColor3f(1,0,0);
 //bitmap_output(120,200,"Name Desg.",GLUT_BITMAP_TIMES_ROMAN_24);
 glColor3f(1,0,0);
 //bitmap_output(620,200,"Name Desg.",GLUT_BITMAP_TIMES_ROMAN_24);

 glColor3f(1,1,1);
 bitmap_output(250,90,"<---Press Enter to continue--->",GLUT_BITMAP_TIMES_ROMAN_24);
 glFlush();
 glutSwapBuffers();
}

 void display(void)
 {
    if(flag1==0){
        name();
    }else {
        draw();
    }
 }

 static void
init(void);
static void
reshape(int width, int height);

static void
idle(void)
{
  angle += 2.0;
  glutPostRedisplay();
}

/* change view angle, exit upon ESC */
/* ARGSUSED1 */
static void
key(unsigned char k, int x, int y)
{
  switch (k) {
  case 'z':
    view_rotz += 5.0;
    break;
  case 'Z':
    view_rotz -= 5.0;
    break;
  case 27:  /* Escape */
    exit(0);
    break;
    case 13:
        flag1=1;
        init();
        reshape(700,700);
        break;
  default:
    return;
  }
  glutPostRedisplay();
}

/* change view angle */
/* ARGSUSED1 */
static void
special(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;
    break;
  case GLUT_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

/* new window size or exposure */
static void
reshape(int width, int height)
{
    if(flag1==1){
  GLfloat h = (GLfloat) height / (GLfloat) width;

  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -50.0);
 }
}

static void
init(void)
{
  if(flag1==1){
  static GLfloat pos[4] =
  {5.0, 5.0, 10.0, 0.0};
  static GLfloat color4[4] =
  {0.5, 0.5, 0.5, 1.0};
  static GLfloat color5[4] =
  {0.8, 0.8, 0.8, 1.0};
  static GLfloat color6[4] =
  {0.2, 0.2, 0.2, 1.0};
  static GLfloat color7[4] =
  {0.5, 0.5, 0.5, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  /* make the gears */
  //First gear on counter shaft
 gear1 = glGenLists(1);
  glNewList(gear1, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  gear(1.0, 3.3, 1.5, 20, 0.7);
  glEndList();

  //Second gear on counter shaft
  gear2 = glGenLists(1);
  glNewList(gear2, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(1.0, 2.0, 1.5, 20, 0.5);
  glEndList();

  //Third gear on counter shaft
  gear8 = glGenLists(1);
  glNewList(gear8, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(1.0, 2.7, 1.5, 20, 0.5);
  glEndList();


  //Fourth gear on counter shaft
  gear4 = glGenLists(1);
  glNewList(gear4, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(0.5, 3.3, 1.5, 20, 0.7);
  glEndList();

  //Fifth gear on counter shaft
  gear3 = glGenLists(1);
  glNewList(gear3, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color6);
  gear(0.5, 4.0, 1.5, 20, 0.7);
  glEndList();

  //First gear on output shaft
  gear5 = glGenLists(1);
  glNewList(gear5, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(0.5, 4.0, 1.5, 20, 0.7);
  glEndList();

  //Second gear on output shaft
  gear7 = glGenLists(1);
  glNewList(gear7, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(0.5, 3.3, 1.5, 20, 0.5);
  glEndList();

  //Third gear on output shaft
  gear9 = glGenLists(1);
  glNewList(gear9, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(0.5, 2.7, 1.5, 20, 0.5);
  glEndList();

  //Fourth gear on output shaft
  gear10 = glGenLists(1);
  glNewList(gear10, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
  gear(0.5, 2.0, 1.5, 20, 0.5);
  glEndList();

  //Input Shaft Gear
  gear6 = glGenLists(1);
  glNewList(gear6, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color7);
  gear(0.5, 2.4, 1.5, 20, 0.7);
  glEndList();


  glEnable(GL_NORMALIZE);
  }
}

void
visible(int vis)
{
  if (vis == GLUT_VISIBLE)
    glutIdleFunc(idle);
  else
    glutIdleFunc(NULL);
}

main(int argc, char *argv[])
{
    flag1=0;
  glutInit(&argc, argv);
  if (argc > 1) {
    /* do 'n' frames then exit */
    limit = atoi(argv[1]) + 1;
  } else {
    limit = 0;
  }
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  glutInitWindowSize(700
                     ,700);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Gears");
  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutSpecialFunc(special);
  glutVisibilityFunc(visible);

  glutMainLoop();
  return 0;
}
