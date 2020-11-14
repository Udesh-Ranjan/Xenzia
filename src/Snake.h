class Node{
    public :
    double x,y,prevX,prevY;
    int dir,prevDir;
    Node *next;
    Node();
    Node(double,double);
    Node(double,double,int);
    void drawNode();
    void setDirection(int);
};

class snake{
    public:
    static const int UP=0;
    static const int DOWN=1;
    static const int LEFT=3;
    static const int RIGHT=4;
    static const int INVALID=-1;
    Node head;
    snake();
    snake(double,double);
    snake(double,double,int);
    void drawSnake();
    void addNode();
    void setDirection(int dir);
};