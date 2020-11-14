#include <GL\freeglut.h>
#include "Snake.h"
#include<iostream>

void display();
void reshape(int,int);
void init();
void drawCell(int,int);
void drawGrid();
void keyPressed(int,int,int);
void timer(int);
void drawFood();
bool checkCollision();
int left=-20;
int right=20;
int top=20;
int bottom=-20;
const float fps=10;
int dir=snake::INVALID;
int foodX=10,foodY=10;
//--=======^========@~
snake cobra;
//////////Main/////////
int main(int argc,char **v){
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
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    // glPointSize(113);
    // glBegin(GL_POINTS);
    // glVertex3f(0,0,0);
    // glVertex3f(-10,0,0);
    // glVertex3f(10,0,0);
    // glEnd();
    drawGrid();
    drawFood();
    if(checkCollision()){
        cobra.addNode();
        std::cout<<"Collision"<<std::endl;
        std::cout.flush();
    }
    cobra.setDirection(dir);
    cobra.drawSnake();
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
    int x=foodX;
    int y=foodY;
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
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
