#include<iostream>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<vector>
using namespace std;

void WindowSize(unsigned height, unsigned width) {
    HANDLE windowsize = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    SMALL_RECT rect;
    rect.Top = rect.Left = 0;
    rect.Bottom = height;
    rect.Right = width;
    SetConsoleWindowInfo(windowsize, true, &rect);
    coord.X = height;
    coord.Y = width;
    SetConsoleScreenBufferSize(windowsize, coord);
}
void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

class CObject
{
protected:
    float X, Y,lastX,lastY;
    char Z;
public:
    CObject(float x = 0, float y = 0,char z =NULL)
    {
        X = x;
        Y = y;
        Z = z;
        lastX = x;
        lastY = y;
    }

    float getX()
    {
        return X;
    }
    float getY()
    {
        return Y;
    }
    float getlastX()
    {
        return lastX;
    }
    float getlastY()
    {
        return lastY;
    }
    char getZ()
    {
        return Z;
    }
    void setX(int x)
    {
        X = x;
    }
    void setY(int y)
    {
        Y = y;
    }
    void setlastPos(float lastx, float lasty)
    {
        lastX = lastx;
        lastY = lasty;
    }
    void setPos(float x,float y)
    {
        X = x;
        Y = y;
    }
    void setZ(char z)
    {
        Z = z;
    }
    virtual void draw()
    {
        gotoxy(lastX, lastY); cout << " ";
        gotoxy(X, Y); cout << Z; 
    }
};
class CTime
{
protected:
    int time;
    float elapsed;
public:
    CTime()
    {
        time = GetTickCount64();
        elapsed = 0;
    }
    float getTimer()
    {
        elapsed = (GetTickCount64() - time) / 1000;
        return elapsed;
    }
    void startTime()
    {
        time = GetTickCount64();
    }
};
class CGarisHorizontal : public CObject
{
protected:
    int panjang;
public:
    CGarisHorizontal(int x = 0, int y = 0, char z = NULL, int p = 0) :CObject(x, y, z)
    {
        panjang = p;
    }
    int getPanjang()
    {
        return panjang;
    }
    void setPanjang(int p)
    {
        panjang = p;
    }
    void draw()
    {
        for (int i = 0; i < panjang; i++) 
        {
            gotoxy(lastX + i, lastY); cout << " ";
            gotoxy(X + i, Y); cout << Z;
        }
    }
};
class CGarisVertikal : public CGarisHorizontal
{
public:
    CGarisVertikal(int x = 0, int y = 0, char z = NULL, int p = 0) : CGarisHorizontal(x, y, z, p) {}
    void draw()
    {
        for (int i = 0; i < panjang; i++)
        {
            gotoxy(lastX, lastY + i); cout << " ";
            gotoxy(X, Y + i); cout << Z;
        }
    }
};
class CGarisDiagonal :public CGarisHorizontal
{
public:
    CGarisDiagonal(int x = 0, int y = 0, char z = NULL, int p = 0) : CGarisHorizontal(x, y, z, p) { }
    void draw()
    {
        if (panjang > 0) {
            for (int i = 0; i < panjang; i++)
            {
                gotoxy(lastX+i, lastY + i); cout << " ";
                gotoxy(X + i, Y + i); cout << Z;
            }
        }
        else if (panjang < 0) {
            for (int i = 0; i > panjang; i--)
            {
                gotoxy(lastX - i, lastY + i); cout << " ";
                gotoxy(X - i, Y + i); cout << Z;

            }
        }
    }
};
class CKotakKosong : public CGarisHorizontal
{
protected:
    int tinggi;
public:
    CKotakKosong(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0) :CGarisHorizontal(x, y, z, p)
    {
        tinggi = t;
    }
    int getTinggi()
    {
        return tinggi;
    }
    void setTinggi(int t)
    {
        tinggi = t;
    }
    void draw()
    {
        for (int i = 0; i < panjang; i++)
        {
            for (int j = 0; j < tinggi; j++)
            {
                gotoxy(lastX + i, lastY + j); cout << " ";
                gotoxy(X + i, Y + j);
                if (i == 0 || i == panjang - 1 || j == 0 || j == tinggi - 1)
                {
                    cout << Z;
                }
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
};
class CKotakBerisi : public CKotakKosong
{
public:
    CKotakBerisi(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0) :CKotakKosong(x, y, z, p, t) {}
    void draw()
    {
        for (int i = 0; i < panjang; i++)
        {
            for (int j = 0; j < tinggi; j++)
            {
                gotoxy(lastX + i, lastY + j); cout << " ";
                gotoxy(X + i, Y + j);
                cout << Z;
            }
            cout << endl;
        }
    }
};
class CNormalEnemy : public CKotakBerisi
{
public:
    CKotakKosong body;
    CObject a, b;
    int DX, DY;
    int health;
    CNormalEnemy(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0, float dx = -1, float dy = 0):CKotakBerisi(x, y, z, p, t)
    {
        srand(time(NULL));
        X = 115;
        Y = rand() % 25 + 1;
        DX = dx;
        DY = dy;
        health = rand() % 4 + 3;
    }
    void update()
    {
        body.setlastPos(X, Y);
        a.setlastPos(X, Y);
        b.setlastPos(X, Y + 4);
        X += DX;
        Y += DY;
        if (X <= 0 || health <= 0)
        {
            X = 115;
            Y = rand() % 25 + 1;
            health = rand() % 4 + 3;
        }
    }
    void draw()
    {
        body.setPos(X, Y);
        body.setZ('o');
        body.setPanjang(5);
        body.setTinggi(5);
        a.setPos(X, Y);
        a.setZ('-');
        a.setPos(X, Y + 4);
        b.setPos(X, Y);
        b.setZ('-');
        body.draw();
        a.draw();
        b.draw();
        if (X - 2 >= 0) {
            gotoxy(X + 2, Y + 2);
            cout << health;
        }
    }
};
class CZigZagEnemy :public CKotakBerisi
{
public:
    int DX, DY;
    CGarisHorizontal side1, side2;
    CObject a, b, c, d, e, f;
    int health;
    CZigZagEnemy(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0, float dx = -1, float dy = -1) :CKotakBerisi(x, y, z, p, t)
    {
        srand(time(NULL));
        X = 115;
        Y = rand() % 25 + 1;
        DX = dx;
        DY = dy;
        health = rand() % 5 + 3;
    }
    void update()
    {
        side1.setlastPos(X, Y);
        side2.setlastPos(X, Y + 4);
        a.setlastPos(X + 1, Y + 1);
        b.setlastPos(X + 3, Y + 1);
        c.setlastPos(X, Y + 2);
        d.setlastPos(X + 4, Y + 2);
        e.setlastPos(X + 1, Y + 3);
        f.setlastPos(X + 3, Y + 3);
        X += DX;
        Y += DY;
        if (X <= 0 || health <= 0)
        {
            X = 115;
            Y = rand() % 25 + 1;
            health = rand() % 5 + 3;
            int r = rand() % 2 + 1;
            if (r == 1)
                DY = 1;
            else if (r == 2)
                DY = -1;
        }
        if (Y >= 26)
            DY = -1;
        if (Y <= 0)
            DY = 1;
    }
    void draw()
    {
        side1.setPos(X, Y);
        side1.setZ('=');
        side1.setPanjang(4);
        side2.setPos(X, Y + 4);
        side2.setZ('=');
        side2.setPanjang(4);
        a.setPos(X + 1, Y + 1);
        a.setZ('*');
        b.setPos(X + 3, Y + 1);
        b.setZ('*');
        c.setPos(X, Y + 2);
        c.setZ('*');
        d.setPos(X + 4, Y + 2);
        d.setZ('*');
        e.setPos(X + 1, Y + 3);
        e.setZ('*');
        f.setPos(X + 3, Y + 3);
        f.setZ('*');
        side1.draw();
        side2.draw();
        a.draw(); 
        b.draw(); 
        c.draw();
        d.draw(); 
        e.draw(); 
        f.draw();
        if (X - 2 >= 0) {
            gotoxy(X + 2, Y + 2);
            cout << health;
        }
    }
};
class CSeekerEnemy :public CKotakBerisi
{
public:
    int DX, DY;
    CGarisHorizontal body1;
    CGarisHorizontal body2;
    CGarisVertikal behind;
    CObject a, b, c;
    int health;
    CSeekerEnemy(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0, float dx = -2, float dy = 0) :CKotakBerisi(x, y, z, p, t)
    {
        srand(time(NULL));
        X = 115;
        Y = rand() % 25 + 1;
        DX = dx;
        DY = dy;
        health = rand() % 2 + 3;
    }
    void setMovement(int dx,int dy)
    {
        DX = dx;
        DY = dy;
    }
    void update()
    {
        body1.setlastPos(X, Y);
        body2.setlastPos(X, Y + 4);
        behind.setlastPos(X+4, Y+1);
        a.setlastPos(X + 1, Y + 1);
        b.setlastPos(X + 1, Y + 3);
        c.setlastPos(X, Y + 2);
        X += DX;
        Y += DY;
        if (X <= 0 || health <= 0)
        {
            X = 115;
            Y = rand() % 25 + 1;
            health = rand() % 2 + 3;
        }
    }
    void draw()
    {
        body1.setPos(X, Y);
        body1.setZ('-');
        body1.setPanjang(5);
        body2.setPos(X, Y + 4);
        body2.setZ('-');
        body2.setPanjang(5);
        body1.draw();
        body2.draw();
        behind.setPos(X + 4, Y + 1);
        behind.setZ('|');
        behind.setPanjang(3);
        a.setPos(X + 1, Y + 1);
        a.setZ('/');
        b.setPos(X + 1, Y + 3);
        b.setZ('\\');
        c.setPos(X, Y + 2);
        c.setZ('{');
        behind.draw();
        c.draw();
        a.draw();
        if (X-2 >= 0) {
            gotoxy(X + 3, Y + 2);
            cout << health;
        }
        b.draw();
    }
};
class CShieldEnemy :public CKotakBerisi
{
public:
    int DX, DY;
    CGarisVertikal body1, body2, shield;
    CGarisHorizontal top1, top2;
    CObject a, b, c, d;
    CTime detik;
    bool active;
    int health;
    CShieldEnemy(int x = 0, int y = 0, char z = NULL, int p = 0, int t = 0, float dx = -1, float dy = 0) :CKotakBerisi(x, y, z, p, t)
    {
        srand(time(NULL));
        X = 115;
        Y = rand() % 20 + 1;
        DX = dx;
        DY = dy;
        health = rand() % 6 + 3;
        active = false;
    }
    bool getStatus()
    {
        return active;
    }
    void update()
    {
        body1.setlastPos(X, Y);
        body2.setlastPos(X + 4, Y);
        top1.setlastPos(X, Y);
        top2.setlastPos(X, Y + 4);
        a.setlastPos(X, Y);
        b.setlastPos(X, Y + 4);
        c.setlastPos(X + 4, Y);
        d.setlastPos(X + 4, Y + 4);
        X += DX;
        Y += DY;
        if (X <= 0||health<=0)
        {
            X = 115;
            Y = rand() % 20 + 1;
            health = rand() % 6 + 3;
        }
    }
    void draw()
    {
        body1.setPos(X, Y);
        body1.setZ('|');
        body1.setPanjang(5);
        body2.setPos(X + 4, Y);
        body2.setZ('|');
        body2.setPanjang(5);
        top1.setPos(X, Y);
        top1.setZ('-');
        top1.setPanjang(5);
        top2.setPos(X, Y + 4);
        top2.setZ('-');
        top2.setPanjang(5);
        a.setPos(X, Y);
        a.setZ('/');
        b.setPos(X, Y + 4);
        b.setZ('\\');
        c.setPos(X + 4, Y);
        c.setZ('\\');
        d.setPos(X + 4, Y + 4);
        d.setZ('/');
        body1.draw(); 
        body2.draw(); 
        top1.draw(); 
        top2.draw(); 
        a.draw(); 
        b.draw();
        c.draw();
        d.draw(); 
        if (X - 2 >= 0) {
            gotoxy(X + 3, Y + 2);
            cout << health;
        }
        if (detik.getTimer() == 4)
        {
            active = true;
            detik.startTime();
       }
        if (active == true)
        {
            DX = 0;
            shield.setPos(X - 1, Y);
            shield.setZ('#');
            shield.setPanjang(5);
            shield.draw();
            if (detik.getTimer() == 2) {
                active = false;
                detik.startTime();
                DX = -1;
            }
        }
    }
};
class CPlayer : public CKotakBerisi
{
public:
    CGarisVertikal behind1, behind2;
    CGarisDiagonal body1, body2;
    CGarisHorizontal gun1, gun2;
    CObject head;
    int DX, DY;
    vector<CObject> bullet;
    CPlayer(int x = 1, int y = 1, char z = NULL, int p = 0, int t = 0,int dx=0,int dy=0):CKotakBerisi(x,y,z,p,t)
    {
        DX = dx;
        DY = dy;
      
    }
    void move(char inp)
    {
        if (_kbhit())
        {
            inp = _getch();
            if (inp == 'W' || inp == 'w')
            {
                DX = 0;
                DY = -1;
            }
            else if (inp == 'A' || inp == 'a')
            {
                DX = -1;
                DY = 0;
            }
            else if (inp == 'S' || inp == 's')
            {
                DX = 0;
                DY = 1;
            }
            else if (inp == 'D' || inp == 'd')
            {
                DX = 1;
                DY = 0;
            }
            else if (inp == ' ')
            {
              bullet.push_back(CObject(head.getX(), head.getY(), '-'));
            }
        }
    }
    void update()
    {
        behind1.setlastPos(X, Y);
        behind2.setlastPos(X + 1, Y - 1);
        body1.setlastPos(X + 2, Y - 1);
        body2.setlastPos(X + 2, Y + 3);
        gun1.setlastPos(X + 3, Y - 1);
        gun2.setlastPos(X + 3, Y + 3);
        head.setlastPos(X + 4, Y + 1);
        X += DX;
        Y += DY;
        for (int i = 0; i < bullet.size(); i++)
        {
            bullet[i].setlastPos(bullet[i].getX(), bullet[i].getY());
            bullet[i].setX(bullet[i].getX() + 1);
            if (bullet[i].getX() > 119)
            {
                bullet.erase(bullet.begin() + i);
                bullet.shrink_to_fit();
            }
          
        }
        if (X <= 0)
        {
            DX = 0;
        }
        else if (X >= 115)
        {
            DX = 0;
        }
        else if (Y <= 1)
        {
            DY = 0;
        }
        else if (Y >= 26)
        {
            DY = 0;
        }
    }
    void draw(){
        behind1.setPos(X, Y);
        behind1.setZ('-');
        behind1.setPanjang(3);
        behind2.setPos(X + 1, Y - 1);
        behind2.setZ('|');
        behind2.setPanjang(5);
        body1.setPos(X + 2, Y - 1);
        body1.setZ('\\');
        body1.setPanjang(2);
        body2.setPos(X + 2, Y +3);
        body2.setZ('/');
        body2.setPanjang(-2);
        gun1.setPos(X + 3, Y - 1);
        gun1.setZ('=');
        gun1.setPanjang(2);
        gun2.setPos(X + 3, Y + 3);
        gun2.setZ('=');
        gun2.setPanjang(2);
        head.setPos(X + 4, Y + 1);
        head.setZ(')');
        head.draw();
        body2.draw();
        body1.draw();
        behind2.draw();
        behind1.draw();
        gun1.draw();
        gun2.draw();
        if (bullet.empty() == false)
        {
            for (int i = 0; i < bullet.size(); i++)
            {
                if (i < bullet.size()) {
                    bullet[i].draw();
                }
            }
        }
    }
};
class CGame
{
public:
    char inp=1;
    int counter = 0,score=0;
    CNormalEnemy enemy;
    CSeekerEnemy seek;
    CZigZagEnemy zigzag;
    CShieldEnemy shield;
    CPlayer play;
    void move()
    {
        play.move(inp);
    }
    void draw()
    {
        enemy.draw();
        seek.draw();
        zigzag.draw();
        shield.draw();
        play.draw();
    }
    void update()
    {
        shield.update();
        zigzag.update();
        if (seek.body1.getY() > play.body1.getY()) {

            seek.setMovement(-1, -1);
        }
        else if (seek.body1.getY() < play.body1.getY())
        {
            seek.setMovement(-1, 1);
        }
        else if (seek.body1.getY() == play.body1.getY())
        {
            seek.setMovement(-1, 0);
        }
        seek.update();
        play.update();
        enemy.update();
        if ((play.body1.getX() == enemy.body.getX() && play.body1.getY() == enemy.body.getY()) || (play.body1.getX() == enemy.a.getX() && play.body1.getY() == enemy.a.getY()) || (play.body1.getX() == enemy.b.getX() && play.body1.getY() == enemy.b.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.body2.getX() == enemy.body.getX() && play.body2.getY() == enemy.body.getY()) || (play.body2.getX() == enemy.a.getX() && play.body2.getY() == enemy.a.getY()) || (play.body2.getX() == enemy.b.getX() && play.body2.getY() == enemy.b.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.head.getX() == enemy.body.getX() && play.head.getY() == enemy.body.getY()) || (play.head.getX() == enemy.a.getX() && play.head.getY() == enemy.a.getY()) || (play.head.getX() == enemy.b.getX() && play.head.getY() == enemy.b.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun1.getX() == enemy.body.getX() && play.gun1.getY() == enemy.body.getY()) || (play.gun1.getX() == enemy.a.getX() && play.gun1.getY() == enemy.a.getY()) || (play.gun1.getX() == enemy.b.getX() && play.gun1.getY() == enemy.b.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun2.getX() == enemy.body.getX() && play.gun2.getY() == enemy.body.getY()) || (play.gun2.getX() == enemy.a.getX() && play.gun2.getY() == enemy.a.getY()) || (play.gun2.getX() == enemy.b.getX() && play.gun2.getY() == enemy.b.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        if ((play.body1.getX() == zigzag.side1.getX() && play.body1.getY() == zigzag.side1.getY()) || (play.body1.getX() == zigzag.side2.getX() && play.body1.getY() == zigzag.side2.getY()) || (play.body1.getX() == zigzag.a.getX() && play.body1.getY() == zigzag.a.getY()) || (play.body1.getX() == zigzag.b.getX() && play.body1.getY() == zigzag.b.getY()) || (play.body1.getX() == zigzag.c.getX() && play.body1.getY() == zigzag.c.getY()) || (play.body1.getX() == zigzag.d.getX() && play.body1.getY() == zigzag.d.getY()) || (play.body1.getX() == zigzag.e.getX() && play.body1.getY() == zigzag.e.getY()) || (play.body1.getX() == zigzag.f.getX() && play.body1.getY() == zigzag.f.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.body2.getX() == zigzag.side1.getX() && play.body2.getY() == zigzag.side1.getY()) || (play.body2.getX() == zigzag.side2.getX() && play.body2.getY() == zigzag.side2.getY()) || (play.body2.getX() == zigzag.a.getX() && play.body2.getY() == zigzag.a.getY()) || (play.body2.getX() == zigzag.b.getX() && play.body2.getY() == zigzag.b.getY()) || (play.body2.getX() == zigzag.c.getX() && play.body2.getY() == zigzag.c.getY()) || (play.body2.getX() == zigzag.d.getX() && play.body2.getY() == zigzag.d.getY()) || (play.body2.getX() == zigzag.e.getX() && play.body2.getY() == zigzag.e.getY()) || (play.body2.getX() == zigzag.f.getX() && play.body2.getY() == zigzag.f.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.head.getX() == zigzag.side1.getX() && play.head.getY() == zigzag.side1.getY()) || (play.head.getX() == zigzag.side2.getX() && play.head.getY() == zigzag.side2.getY()) || (play.head.getX() == zigzag.a.getX() && play.head.getY() == zigzag.a.getY()) || (play.head.getX() == zigzag.b.getX() && play.head.getY() == zigzag.b.getY()) || (play.head.getX() == zigzag.c.getX() && play.head.getY() == zigzag.c.getY()) || (play.head.getX() == zigzag.d.getX() && play.head.getY() == zigzag.d.getY()) || (play.head.getX() == zigzag.e.getX() && play.head.getY() == zigzag.e.getY()) || (play.head.getX() == zigzag.f.getX() && play.head.getY() == zigzag.f.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun1.getX() == zigzag.side1.getX() && play.gun1.getY() == zigzag.side1.getY()) || (play.gun1.getX() == zigzag.side2.getX() && play.gun1.getY() == zigzag.side2.getY()) || (play.gun1.getX() == zigzag.a.getX() && play.gun1.getY() == zigzag.a.getY()) || (play.gun1.getX() == zigzag.b.getX() && play.gun1.getY() == zigzag.b.getY()) || (play.gun1.getX() == zigzag.c.getX() && play.gun1.getY() == zigzag.c.getY()) || (play.gun1.getX() == zigzag.d.getX() && play.gun1.getY() == zigzag.d.getY()) || (play.gun1.getX() == zigzag.e.getX() && play.gun1.getY() == zigzag.e.getY()) || (play.gun1.getX() == zigzag.f.getX() && play.gun1.getY() == zigzag.f.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun2.getX() == zigzag.side1.getX() && play.gun2.getY() == zigzag.side1.getY()) || (play.gun2.getX() == zigzag.side2.getX() && play.gun2.getY() == zigzag.side2.getY()) || (play.gun2.getX() == zigzag.a.getX() && play.gun2.getY() == zigzag.a.getY()) || (play.gun2.getX() == zigzag.b.getX() && play.gun2.getY() == zigzag.b.getY()) || (play.gun2.getX() == zigzag.c.getX() && play.gun2.getY() == zigzag.c.getY()) || (play.gun2.getX() == zigzag.d.getX() && play.gun2.getY() == zigzag.d.getY()) || (play.gun2.getX() == zigzag.e.getX() && play.gun2.getY() == zigzag.e.getY()) || (play.gun2.getX() == zigzag.f.getX() && play.gun2.getY() == zigzag.f.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        if ((play.body1.getX() == seek.body1.getX() && play.body1.getY() == seek.body1.getY()) || (play.body1.getX() == seek.body2.getX() && play.body1.getY() == seek.body2.getY()) || (play.body1.getX() == seek.a.getX() && play.body1.getY() == seek.a.getY()) || (play.body1.getX() == seek.b.getX() && play.body1.getY() == seek.b.getY()) || (play.body1.getX() == seek.c.getX() && play.body1.getY() == seek.c.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.body2.getX() == seek.body1.getX() && play.body2.getY() == seek.body1.getY()) || (play.body2.getX() == seek.body2.getX() && play.body2.getY() == seek.body2.getY()) || (play.body2.getX() == seek.a.getX() && play.body2.getY() == seek.a.getY()) || (play.body2.getX() == seek.b.getX() && play.body2.getY() == seek.b.getY()) || (play.body2.getX() == seek.c.getX() && play.body2.getY() == seek.c.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.head.getX() == seek.body1.getX() && play.head.getY() == seek.body1.getY()) || (play.head.getX() == seek.body2.getX() && play.head.getY() == seek.body2.getY()) || (play.head.getX() == seek.a.getX() && play.head.getY() == seek.a.getY()) || (play.head.getX() == seek.b.getX() && play.head.getY() == seek.b.getY()) || (play.head.getX() == seek.c.getX() && play.head.getY() == seek.c.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun1.getX() == seek.body1.getX() && play.gun1.getY() == seek.body1.getY()) || (play.gun1.getX() == seek.body2.getX() && play.gun1.getY() == seek.body2.getY()) || (play.gun1.getX() == seek.a.getX() && play.gun1.getY() == seek.a.getY()) || (play.gun1.getX() == seek.b.getX() && play.gun1.getY() == seek.b.getY()) || (play.gun1.getX() == seek.c.getX() && play.gun1.getY() == seek.c.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun2.getX() == seek.body1.getX() && play.gun2.getY() == seek.body1.getY()) || (play.gun2.getX() == seek.body2.getX() && play.gun2.getY() == seek.body2.getY()) || (play.gun2.getX() == seek.a.getX() && play.gun2.getY() == seek.a.getY()) || (play.gun2.getX() == seek.b.getX() && play.gun2.getY() == seek.b.getY()) || (play.gun2.getX() == seek.c.getX() && play.gun2.getY() == seek.c.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        if ((play.body1.getX() == shield.body1.getX() && play.body1.getY() == shield.body1.getY()) || (play.body1.getX() == shield.body2.getX() && play.body1.getY() == shield.body2.getY()) || (play.body1.getX() == shield.a.getX() && play.body1.getY() == shield.a.getY()) || (play.body1.getX() == shield.b.getX() && play.body1.getY() == shield.b.getY()) || (play.body1.getX() == shield.top1.getX() && play.body1.getY() == shield.top1.getY()) || (play.body1.getX() == shield.top2.getX() && play.body1.getY() == shield.top2.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.body2.getX() == shield.body1.getX() && play.body2.getY() == shield.body1.getY()) || (play.body2.getX() == shield.body2.getX() && play.body2.getY() == shield.body2.getY()) || (play.body2.getX() == shield.a.getX() && play.body2.getY() == shield.a.getY()) || (play.body2.getX() == shield.b.getX() && play.body2.getY() == shield.b.getY()) || (play.body2.getX() == shield.top1.getX() && play.body2.getY() == shield.top1.getY()) || (play.body2.getX() == shield.top2.getX() && play.body2.getY() == shield.top2.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.head.getX() == shield.body1.getX() && play.head.getY() == shield.body1.getY()) || (play.head.getX() == shield.body2.getX() && play.head.getY() == shield.body2.getY()) || (play.head.getX() == shield.a.getX() && play.head.getY() == shield.a.getY()) || (play.head.getX() == shield.b.getX() && play.head.getY() == shield.b.getY()) || (play.head.getX() == shield.top1.getX() && play.head.getY() == shield.top1.getY()) || (play.head.getX() == shield.top2.getX() && play.head.getY() == shield.top2.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun1.getX() == shield.body1.getX() && play.gun1.getY() == shield.body1.getY()) || (play.gun1.getX() == shield.body2.getX() && play.gun1.getY() == shield.body2.getY()) || (play.gun1.getX() == shield.a.getX() && play.gun1.getY() == shield.a.getY()) || (play.gun1.getX() == shield.b.getX() && play.gun1.getY() == shield.b.getY()) || (play.gun1.getX() == shield.top1.getX() && play.gun1.getY() == shield.top1.getY()) || (play.gun1.getX() == shield.top2.getX() && play.gun1.getY() == shield.top2.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }
        else if ((play.gun2.getX() == shield.body1.getX() && play.gun2.getY() == shield.body1.getY()) || (play.gun2.getX() == shield.body2.getX() && play.gun2.getY() == shield.body2.getY()) || (play.gun2.getX() == shield.a.getX() && play.gun2.getY() == shield.a.getY()) || (play.gun2.getX() == shield.b.getX() && play.gun2.getY() == shield.b.getY()) || (play.gun2.getX() == shield.top1.getX() && play.gun2.getY() == shield.top1.getY()) || (play.gun2.getX() == shield.top2.getX() && play.gun2.getY() == shield.top2.getY()))
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Died...";
        }

        for (int i = 0; i < play.bullet.size(); i++)
        {
            if ((play.bullet[i].getX() == enemy.body.getX() && play.bullet[i].getY() == enemy.body.getY()) || (play.bullet[i].getX() == enemy.body.getX() && play.bullet[i].getY() == enemy.body.getY() + 1) || (play.bullet[i].getX() == enemy.body.getX() && play.bullet[i].getY() == enemy.body.getY() + 2) || (play.bullet[i].getX() == enemy.body.getX() && play.bullet[i].getY() == enemy.body.getY() + 3) || (play.bullet[i].getX() == enemy.body.getX() && play.bullet[i].getY() == enemy.body.getY() + 4) || (play.bullet[i].getX() == enemy.a.getX() && play.bullet[i].getY() == enemy.a.getY()) || (play.bullet[i].getX() == enemy.b.getX() && play.bullet[i].getY() == enemy.b.getY()))
            {
                enemy.health -= 1;
                if (play.bullet[i].getX() > 119)
                {
                    play.bullet.erase(play.bullet.begin() + i);
                    play.bullet.shrink_to_fit();
                }

            }
            else if ((play.bullet[i].getX() == zigzag.side1.getX() && play.bullet[i].getY() == zigzag.side1.getY()) || (play.bullet[i].getX() == zigzag.side2.getX() && play.bullet[i].getY() == zigzag.side2.getY()) || (play.bullet[i].getX() == zigzag.a.getX() && play.bullet[i].getY() == zigzag.a.getY()) || (play.bullet[i].getX() == zigzag.b.getX() && play.bullet[i].getY() == zigzag.b.getY()) || (play.bullet[i].getX() == zigzag.c.getX() && play.bullet[i].getY() == zigzag.c.getY()) || (play.bullet[i].getX() == zigzag.d.getX() && play.bullet[i].getY() == zigzag.d.getY()) || (play.bullet[i].getX() == zigzag.e.getX() && play.bullet[i].getY() == zigzag.e.getY()) || (play.bullet[i].getX() == zigzag.f.getX() && play.bullet[i].getY() == zigzag.f.getY()))
            {
                zigzag.health -= 1;
                if (play.bullet[i].getX() > 119)
                {
                    play.bullet.erase(play.bullet.begin() + i);
                    play.bullet.shrink_to_fit();
                }

            }
            else if ((play.bullet[i].getX() == seek.body1.getX() && play.bullet[i].getY() == seek.body1.getY()) || (play.bullet[i].getX() == seek.body2.getX() && play.bullet[i].getY() == seek.body2.getY()) || (play.bullet[i].getX() == seek.a.getX() && play.bullet[i].getY() == seek.a.getY()) || (play.bullet[i].getX() == seek.b.getX() && play.bullet[i].getY() == seek.b.getY()) || (play.bullet[i].getX() == seek.c.getX() && play.bullet[i].getY() == seek.c.getY()))
            {
                seek.health -= 1;
                if (play.bullet[i].getX() > 119)
                {
                    play.bullet.erase(play.bullet.begin() + i);
                    play.bullet.shrink_to_fit();
                }
            }
            if (shield.getStatus() == true)
            {
                if (play.bullet[i].getX() == shield.shield.getX() && play.bullet[i].getY() == shield.shield.getY())
                {
                    if (play.bullet[i].getX() > 119)
                    {
                        play.bullet.erase(play.bullet.begin() + i);
                        play.bullet.shrink_to_fit();
                    }
                }
            }
            else if (shield.getStatus() == false)
            {
                if ((play.bullet[i].getX() == shield.body1.getX() && play.bullet[i].getY() == shield.body1.getY()) || (play.bullet[i].getX() == shield.body2.getX() && play.bullet[i].getY() == shield.body2.getY()) || (play.bullet[i].getX() == shield.top1.getX() && play.bullet[i].getY() == shield.top1.getY()) || (play.bullet[i].getX() == shield.top2.getX() && play.bullet[i].getY() == shield.top2.getY()) || (play.bullet[i].getX() == shield.a.getX() && play.bullet[i].getY() == shield.b.getY()) || (play.bullet[i].getX() == shield.b.getX() && play.bullet[i].getY() == shield.b.getY())) 
                    {
                     shield.health -= 1;
                     if (play.bullet[i].getX() > 119)
                     {
                         play.bullet.erase(play.bullet.begin() + i);
                         play.bullet.shrink_to_fit();
                     }
                    }
            }
        }
        gotoxy(0, 25); cout << "Score: " << score;
        gotoxy(0, 26); cout << "Tembus: " << counter;
        if (enemy.health == 0 || seek.health == 0 || zigzag.health == 0 || shield.health == 0)
        {
            score++;
        }
        if (enemy.getX() <= 1 || seek.getX() <= 1 || zigzag.getX() <= 1 || shield.getX() <= 1)
        {
            counter++;
        }
        if (counter == 5)
        {
            inp = 27;
            system("cls");
            gotoxy(0, 0);
            cout << "You Lose";
        }
    }
    void run()
    {
        while (inp!=27)
        {
            Sleep(50);
            draw();
            update();
            move();
        }
    }
};
void main()
{
    hidecursor();
    WindowSize(100, 30);
    CGame game;
    game.run();
  
    system("pause");
}