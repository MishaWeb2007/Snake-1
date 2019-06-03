/*****************
 * Snake         *
 * by CX9PS3     *
 * License:GPLv3 *
 *****************
 */

//load headers

#if defined(_WIN32) || defined (_WIN64) 
    #include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <GL/glut.h>
//set size for game field and size of window
#define m 20
#define n 30
#define scale 25
int w=scale * n;
int h=scale * m;

int SnakeSpeed;
int dir,length=1,Score=0;

//set coordinates for snake elements
struct 
{
   int x;
   int y;
}s[100];

int AppleX,AppleY;

//create apple in random position in field
void NewApple()
{
    srand(time(NULL));
    AppleX=rand()%n;
    AppleY=rand()%m;
}



//set coordinates for apple and color 
void DrawApple()
{
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(AppleX*scale,AppleY*scale,(AppleX+1)*scale,(AppleY+1)*scale);
}
//TODO Make beutyfull background
/*struct  Flowers
{
    int x;
    int y;
    float r;
    float g;
    float b;
} Flower[50];
float RGBConventer(float a)
{
    return a/255;
}
void CreateFlower(int i)
{
    srand(time(NULL));
    Flower[i].x=rand()%n;
    Flower[i].y=rand()%m;
    Flower[i].r=RGBConventer(rand()%255);
    Flower[i].g=RGBConventer(rand()%255);
    Flower[i].b=RGBConventer(rand()%255);
    
}
void DrawFlowers()
{
    for(int i=0;i<50;i++)
    {
        CreateFlower(i);
        
    }
    for(int i=0;i<50;i++)
    {
        glColor3f(Flower[i].r,Flower[i].g,Flower[i].b);
        glRectf(Flower[i].x*scale/2,Flower[i].y*scale/2,(Flower[i].x+1)*scale/2,((Flower[i].y+1)*scale)/2);
    }
}
*/


//set coordinates for text and color,this text show player score
void DrawScore(int x,int y,int score)
{
    //integer to char 
    char str;
    str=score+'0';
    

    glColor3f(1.0, 0.0,0.0); 
    glRasterPos2d(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str);
    
}
void Snake()
{

    //set coordinates for elements of snake
    for(int i=length;i>0;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }

    //set direction for snake
    switch (dir)
    {
    case 0 :
       s[0].y+=1;
       break;
    case 1 :
       s[0].x-=1;
       break;
    case 2 :
       s[0].x+=1;
       break;
    case 3 :
       s[0].y-=1;
       break;
    default:
        break;
    }


    ///collision with apple
    if((s[0].x==AppleX)&&(s[0].y==AppleY))
    {
        length++;
        Score++;
        NewApple();
    }


    //collision with border of field 
    if(s[0].x>n) dir = 1;
    if(s[0].y>m) dir = 3;
    if(s[0].x<0) dir = 2;
    if(s[0].y<0) dir = 0;

    //collision snake head with another parts of snake
    for (int i =  1; i < length; i++)
    {
        if((s[0].x==s[i].x)&&(s[0].y==s[i].y)&& length>4)
        {
            length=1;
            Score=0;
        }
    }
    
}
//set controls 
void Keyboard(int key,int x,int y)
{
    switch (key)
    {
    case 101: dir = 0; break;//up
    case 103: dir = 3; break;//left
    case 100: dir = 1; break;//right
    case 102: dir = 2; break;//down
    case GLUT_KEY_F1: glutFullScreen();break;//enable fullscreen
    case GLUT_KEY_F2:glutPositionWindow(0,0);glutReshapeWindow(w, h);break;//disable fullscreen
    case GLUT_KEY_F12:exit(EXIT_SUCCESS);break;//exit from game
    }
}

//set snake color and position
void DrawSnake()
{
    glColor3f(1.0f,0.415f,0.415f);
    for(int i=0;i<length;i++)
    {
        glRectf(s[i].x*scale,s[i].y*scale,(s[i].x+1)*scale,(s[i].y+1)*scale);

    }
}

//draw lines on field 
void DrawScene()
{
    glColor3f(0.48f,0.8f,0.5f);
    glBegin(GL_LINES);
    for(int i=0;i<w;i+=scale)
    {
        glVertex2f(i,0);
        glVertex2f(i,h);
    }
   for(int i=0;i<h;i+=scale)
    {
        glVertex2f(0,i);
        glVertex2f(w,i);
    }
    glEnd();
}
//render all
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.443f,0.766f,0.443f,0.0f);
    //DrawFlowers();
    DrawApple();
    DrawScene();
    DrawSnake();
    DrawScore(w-20,h-20,Score);
    glFlush();
}
void timer()
{
    display();
    Snake();
    glutTimerFunc(SnakeSpeed,timer,0);
}
void ShowHelp()
{
    printf("--easy - easy difficult\n");
    printf("--normal - middle difficult\n");
    printf("--hard - hard difficult\n");
    printf("--help - show this\n");
    printf("Controls:\n");
    printf("F1 - fullscreen on\n");
    printf("F2 - fullscreen off\n");
    printf("F12 - exit from game\n");
    printf("Arrows - control snake\n");
}
int main(int argc,char *argv[])
{

    //program flags 
    if(argc>1)
    {
        if(!strcmp(argv[1],"--easy"))
        {
            printf("You choose easy mode \n");
            SnakeSpeed=75;
        }
       else  if(!strcmp(argv[1],"--normal"))
        {
            printf("You choose normal mode \n");
            SnakeSpeed=50;
        }
       else  if(!strcmp(argv[1],"--hard"))
        {
            printf("You choose hard mode \n");
            SnakeSpeed=35;
        }
       else  if(!strcmp(argv[1],"--help"))
        {
            ShowHelp();
            return 1;
        }
        else
        {
           printf("Error,Unknown key of command\n");
           ShowHelp();
           return 1;
        }
        
    }
    else
    {
           printf("Error!Use flags!!!\n");
           return 1;   
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(w,h);
    glutCreateWindow("Snake");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
    s[0].x=10;
    s[0].y=10;
    NewApple();
    glutDisplayFunc(display);
    glutTimerFunc(SnakeSpeed,timer,0);
    glutSpecialFunc(Keyboard);
    glutMainLoop();
}