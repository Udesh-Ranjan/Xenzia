#include <GL/freeglut.h>
#include "Snake.h"

Node::Node(){
    prevX=prevY=x=y=0;
    prevDir=dir=snake::INVALID;
    next=nullptr;
}

Node::Node(double a,double b){
    prevX=x=a;
    prevY=y=b;
    prevDir=dir=snake::INVALID;
    next=nullptr;
}
Node::Node(double a,double b,int direction){
    prevX=x=a;
    prevY=y=b;
    switch(direction){
        case snake::UP:
            dir=snake::UP;break;
        case snake::DOWN:
            dir=snake::DOWN;break;
        case snake::LEFT:
            dir=snake::LEFT;break;
        case snake::RIGHT:
            dir=snake::RIGHT;break;
        default: dir=snake::INVALID;
    }
    prevDir=dir;
    next=nullptr;
}
void Node::drawNode(){
    glColor3f(1,0,0);
    glRectd(x,y,x+1,y+1);
}
void Node::setDirection(int direction){
    switch(direction){
        case snake::UP:
        if(dir!=snake::DOWN){
            prevDir=dir;
            dir=snake::UP;
        }
        break;
        case snake::DOWN:
        if(dir!=snake::UP){
            prevDir=dir;
            dir=snake::DOWN;
        }
        break;
        case snake::LEFT:
        if(dir!=snake::RIGHT){
            prevDir=dir;
            dir=snake::LEFT;
        }
        break;
        case snake::RIGHT:
        if(dir!=snake::LEFT){
            prevDir=dir;
            dir=snake::RIGHT;
        }
        break;
        default: prevDir=dir=snake::INVALID;
    }
}
snake::snake(){
    head.setDirection(snake::INVALID);
}
snake::snake(double x,double y){
    head.x=x;
    head.y=y;
    head.setDirection(snake::INVALID);
}
snake::snake(double x,double y,int dir){
    head.x=x;
    head.y=y;
    head.setDirection(dir);
}
void snake::drawSnake(){
    Node *next=&head;
    while(next!=nullptr){
        next->drawNode();
        next=next->next;
    }
}
void snake::addNode(){
    Node * temp=&head;
    while(temp->next!=nullptr)
    temp=temp->next;
    temp->next=new Node(temp->prevX,temp->prevY,temp->prevDir);
}
void snake::setDirection(int dir){
    Node *temp=&head;
    while(temp){
        temp->setDirection(dir);
        if(temp->dir==snake::UP){
            temp->prevY=temp->y;
            temp->prevX=temp->x;
            temp->y++;
        }
        else
        if(temp->dir==snake::DOWN){
            temp->prevY=temp->y;
            temp->prevX=temp->x;
            temp->y--;
        }
        else
        if(temp->dir==snake::RIGHT){
            temp->prevX=temp->x;
            temp->prevY=temp->y;
            temp->x++;
        }
        else
        if(temp->dir==snake::LEFT){
            temp->prevX=temp->x;
            temp->prevY=temp->y;
            temp->x--;
        }
        dir=temp->prevDir;
        temp=temp->next;
    }
}