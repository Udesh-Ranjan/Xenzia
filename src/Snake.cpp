#include <GL/freeglut.h>
#include "Snake.h"

Node::Node(){
    prevX=prevY=x=y=0;
    prevDir=dir=snake::INVALID;
    next=nullptr;
    red=green=blue=1;
}

Node::Node(double a,double b){
    prevX=x=a;
    prevY=y=b;
    prevDir=dir=snake::INVALID;
    next=nullptr;
    red=green=blue=1;
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
    red=green=blue=1;
}
void Node::drawNode(){
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
snake::snake(int top,int bottom,int left,int right){
    topBond=top;
    bottomBond=bottom;
    leftBond=left;
    rightBond=right;
    head.setDirection(snake::INVALID);
}
snake::snake(double x,double y,int top,int bottom,int left,int right){
    head.x=x;
    head.y=y;
    topBond=top;
    bottomBond=bottom;
    leftBond=left;
    rightBond=right;
    head.setDirection(snake::INVALID);
}
snake::snake(double x,double y,int dir,int top,int bottom,int left,int right){
    head.x=x;
    head.y=y;
    topBond=top;
    bottomBond=bottom;
    leftBond=left;
    rightBond=right;
    head.setDirection(dir);
}
void snake::drawSnake(){
    Node *next=&head;
    bool flag=true;
    while(next!=nullptr){
        if(flag){
            glColor3f(0,1,0);
            flag=false;
        }
        else{
            glColor3f(1,1,0);
        }
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
    if(temp==nullptr)
    return;
    temp->setDirection(dir);
    
    bool exe=false;
    if(temp->y>=topBond-1 &&temp->dir==snake::UP){
        temp->prevY=temp->y;
        temp->prevX=temp->x;
        temp->y=bottomBond;
        exe=true;
    }
    else
    if(temp->y<=bottomBond &&temp->dir==snake::DOWN){
        temp->prevY=temp->y;
        temp->prevX=temp->x;
        temp->y=topBond-1;
        exe=true;
    }
    if(temp->x>=rightBond-1 &&temp->dir==snake::RIGHT){
        temp->prevY=temp->y;
        temp->prevX=temp->x;
        temp->x=leftBond;
        exe=true;
    }
    else
    if(temp->x<=leftBond &&temp->dir==snake::LEFT){
        temp->prevY=temp->y;
        temp->prevX=temp->x;
        temp->x=rightBond-1;
        exe=true;
    }

    if(!exe){
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
    }
    int prevX=temp->prevX;
    int prevY=temp->prevY;
    int currX,currY;
    temp=temp->next;
    while(temp){
        currX=temp->x;
        currY=temp->y;
        temp->x=prevX;
        temp->y=prevY;
        temp->prevX=currX;
        temp->prevY=currY;
        prevX=currX;
        prevY=currY;
        temp=temp->next;
    }
}
bool snake::collision(){
    Node *temp=head.next;
    while(temp){
        if(head.x==temp->x&&head.y==temp->y)
        return true;
        temp=temp->next;
    }
    return false;
}