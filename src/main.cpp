#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Snake.h"
#include <GL\freeglut.h>

void display();
void reshape(int width,int height);
void init();
void drawCell(int xCell,int yCell);
void drawGrid();
void keyPressed(int key,int mouseX,int mouseY);
void timer(int);
void drawFood();
bool checkCollision();
int rand(int low,int high);
void swap(int *first,int *second);
bool isOccupied(int xCell,int yCell);

int left=-20;
int right=20;
int top=20;
int bottom=-20;
const float fps=5;
int dir=snake::INVALID;
int foodX=10,foodY=10;
int hitCount=0;
bool alive=true;
//--=======^========@~
snake cobra(top,bottom,left,right);

//////////Main/////////
int main(int argc,char **v){
    srand(time(0));
    glutInit(&argc,v);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake Game");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyPressed);
    glutTimerFunc(10,timer,0);
    glutMainLoop();
    init();
    return 0;
}
bool flag=false;
bool gameDestroyed=false;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawFood();
    cobra.setDirection(dir);
    cobra.drawSnake();
    if(checkCollision()){
        cobra.addNode();
        cobra.vec.push_back(1);
        std::cout<<"Collision"<<std::endl;
        std::cout.flush();
        hitCount=0;
        for(int i=0;i<700;i++){
            foodX=rand(left,right-1);
            foodY=rand(bottom,top-1);
            if(isOccupied(foodX,foodY)){
                hitCount++;
            }
            else
            break;
            if(hitCount>=600){
                flag=false;
                for(int x=left;x<right;x++){
                    for(int y=top-1;y>=bottom;y--){
                        if(!isOccupied(x,y)){
                            foodX=x;
                            foodY=y;
                            flag=true;
                            break;
                        }
                    }
                }
                if(flag==false){
                    gameDestroyed=true;
                }
                break;
            }
        }
        if(gameDestroyed){
            std::cout<<"Game is destroyed "<<"[ *}"<<std::endl;
            exit(0);
        }
    }
    if(cobra.collision()){
        std::cout<<"Snake Crashed"<<std::endl;
        exit(0);
    }
    // std::cout<<"Displaying snake"<<std::endl;
    std::cout<<cobra.head.x<<"-curr-"<<cobra.head.y<<std::endl;
    std::cout<<cobra.head.prevX<<"-prev-"<<cobra.head.prevY<<std::endl;
    std::cout.flush();
    glFlush();
}
void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20,20,-20,20);
    glMatrixMode(GL_MODELVIEW);
    // drawGrid();
}
void init(){
    glClearColor(0,0,0,1);
}
void drawGrid(){
    for(int y=top-1;y>=bottom;y--){
        for(int x=left;x<right;x++){
            drawCell(x,y);
        }
    }
}
void drawCell(int x,int y){
    if(x==left||x==right-1||y==top-1||y==bottom){
        glLineWidth(3.0);
        glColor3f(0,0,1);
    }
    else{
        glLineWidth(1.0);
        glColor3f(1,0,0);
    }
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
    
}
void keyPressed(int key,int x,int y){
    if(key==GLUT_KEY_UP){
        if(dir!=snake::DOWN)
        dir=snake::UP;
    }
    else
    if(key==GLUT_KEY_DOWN){
        if(dir!=snake::UP)
        dir=snake::DOWN;
    }
    if(key==GLUT_KEY_LEFT){
        if(dir!=snake::RIGHT)
        dir=snake::LEFT;
    }
    if(key==GLUT_KEY_RIGHT){
        if(dir!=snake::LEFT)
        dir=snake::RIGHT;
    }
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/fps,timer,0);
}
void drawFood(){
    glColor3f(0,1,0);
    int x=foodX;
    int y=foodY;
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
    glColor3f(0,0,1);
    glLineWidth(0.002);
    glRectd(x,y,x+1,y+1);
    glLineWidth(1);
}
bool checkCollision(){
    if(cobra.head.x==foodX&&cobra.head.y==foodY)
    return true;
    return false;
}
bool isOccupied(int x,int y){
    Node * temp=&cobra.head;
    while(temp){
        if(temp->x==x&&temp->y==y)
        return true;
        temp=temp->next;
    }
    return false;
}
bool isFullScreenOcupied(){
    return false;
}
int rand(int min,int max){
    if(min>max)
    swap(&min,&max);
    return rand()%(max-min + 1) + min;
}
int _temp;
void swap(int *x,int *y){
    _temp=*x;
    *x=*y;
    *y=_temp;
}