#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#define MaxLength 100
#define MaxFrameX 120
#define MaxFrameY 30

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void GoToxy(int x, int y)
{
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console, CursorPosition);
}

class point{
    private:
        int x;
        int y;
    public:
        point(){x=y=10;}
        point(int x,int y)
        {
            this->x=x;
            this->y=y;
        }
        void SetPoint(int x,int y)
        {
            this->x=x;
            this->y=y;
        }
        int GetPointX() {return x;}
        int GetPointY() {return y;}
        void MoveUp() {y--; if(y<0) y=MaxFrameY;}
        void MoveDown() {y++; if(y>MaxFrameY) y=0;}
        void MoveRight() {x++; if(x>MaxFrameX) x=0;}
        void MoveLeft() {x--; if(x<0) x=MaxFrameX;}
        void Erase()
        {
            GoToxy(x,y);
            cout<<" ";
        }
        void Draw(char ch='#')
        {
            GoToxy(x,y);
            cout<<ch;
        }
        void CopyPosition(point *p)
        {
            p->x=x;
            p->y=y;
        }
        int IsEqual(point *p)
        {
            if(p->x==x && p->y==y)
                return 1;
            return 0;
        }
        void Debug()
        {
            cout<<"("<<x<<","<<y<<")";
        }
};

class Snake{
    private:
        point *body[MaxLength];
        int length;
        char Dir;
        point fruit;
        int state;
        int started;
        int blink;
    public:
        Snake()
        {
            length=1;
            body[0]= new point(15,15);
            for(int i=1;i<MaxLength;i++)
                body[i]=NULL;

            fruit.SetPoint(rand()%MaxFrameX, rand()%MaxFrameY);
            state=0;
            started=0;
        }
        void AddCellToBody(int x,int y)
        {
            body[length++]=new point(x,y);
        }
        void TurnUp(){ if(Dir!='s') Dir='w';}
        void TurnDown(){ if(Dir!='w') Dir='s';}
        void TurnRight(){ if(Dir!='a') Dir='d';}
        void TurnLeft(){ if(Dir!='d') Dir='a';}
        void WelcomeScreen()
        {
            SetConsoleTextAttribute(console,15);
            cout<<"Go to Study Man";
        }
        void Move()
        {
            system("cls");
            if(state == 0){
                if(!started){
                    //WelcomeScreen();
                    cout<<"Press Any Key to start";
                    getch();
                    started=1;
                    state=1;
                }}
                else{
                    cout<<"Snake Dead! Game Over";
                    cout<<"\nPress Any Key to start";
                    getch();
                    state=1;
                    length=1;
                }

            for(int i=length-1;i>0;i--)
            {
                body[i-1]->CopyPosition(body[i]);
            }
            switch(Dir)
            {
                case 'w':
                    body[0]->MoveUp();
                    break;
                case 's':
                    body[0]->MoveDown();
                    break;
                case 'a':
                    body[0]->MoveLeft();
                    break;
                case 'd':
                    body[0]->MoveRight();
                    break;
            }
            if(SelfCollision())
                state=0;

            if(fruit.GetPointX()==body[0]->GetPointX() && fruit.GetPointY()==body[0]->GetPointY())
            {
                AddCellToBody(0,0);
                fruit.SetPoint(rand()%MaxFrameX, rand()%MaxFrameY);
            }
            for(int i=0;i<length;i++)
                body[i]->Draw();

            SetConsoleTextAttribute(console,242);
            if(!blink)
                fruit.Draw('0');
            blink = !blink;
            SetConsoleTextAttribute(console,252);
            Sleep(100);
        }
        int SelfCollision()
        {
            for(int i=0;i<length;i++)
                if(body[0]->IsEqual(body[i]))
                    return 1;
            return 0;
        }

};

int main()
{
    srand((unsigned)time(NULL));
    Snake snake;
    char t='l';
    do{
        if(kbhit()){
        t=getch();
        }
        switch(t){
            case 'w':
            case 'W':
                snake.TurnUp();
                break;

            case 's':
            case 'S':
                snake.TurnDown();
                break;

            case 'a':
            case 'A':
                snake.TurnLeft();
                break;

            case 'd':
            case 'D':
                snake.TurnRight();
                break;
        }
        snake.Move();
    }
    while(t!='e');
    return 0;
}
