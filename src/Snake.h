class Node{
    public :
    double x,y,prevX,prevY;
    int dir,prevDir;
    float red,green,blue;
    Node *next;
    Node();
    Node(double,double);
    Node(double,double,int);
    void drawNode();
    void setDirection(int);
    void setColor(float red,float green,float blue);
};

class snake{
    public:
    static const int UP=0;
    static const int DOWN=1;
    static const int LEFT=3;
    static const int RIGHT=4;
    static const int INVALID=-1;
    int leftBond,rightBond,topBond,bottomBond;
    Node head;
    snake(int top,int bottom,int left, int right);
    snake(double,double,int top,int bottom,int left, int right);
    snake(double,double,int,int top,int bottom,int left, int right);
    void drawSnake();
    void addNode();
    void setDirection(int dir);
    bool collision();
};