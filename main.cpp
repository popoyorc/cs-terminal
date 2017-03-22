#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <fstream>

//CONTROLS
#define key_SPACE 32
#define key_Q 113
#define key_P 112
#define key_R 114
#define key_1 49
#define key_2 50
#define key_3 51
#define key_4 52
#define key_W 119
#define key_A 97
#define key_S 115
#define key_D 100
#define key_X 120

bool bombSet = false;
int keypress=0;
unsigned int money;
struct t_sight{int x,y;};
struct t_weapon{unsigned int MAX_AMMO,NUM_AMMO,NUM_PROJECTILE; unsigned char COLOR; char NAME[13],SOUND[6];};
t_sight sight;
t_weapon weapon;


void clrscr();
void runGame();
void initGame();
void openShop();
void Keypressed();
void renderSight();
void removeSight();
void setcolor(WORD color);
void gotoxy(int x, int y);
void shoot(unsigned char x, unsigned char y);
void txtPlot( unsigned char x, unsigned char y, unsigned char Color);
void clrbox(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol);
void box(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[]);
void setWeapon(unsigned int a,unsigned int b,unsigned int c, unsigned char Color, char name[], char sound[]);


void box(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[])
{  unsigned i,j,m;
    {

       m=(sx-x);                       //differential
       j=m/8;                          //adjust
       j=j-1;                          //more adjustment
       gotoxy(x,y);printf("É");       //Top left corner of box
       gotoxy(sx,y);printf("»");      //Top right corner of box
       gotoxy(x,sy);printf("È");      //Bottom left corner of box
       gotoxy(sx,sy);printf("¼");     //Bottom right corner of box

       for (i=x+1;i<sx;i++)
       {
          gotoxy(i,y);printf("Í");     // Top horizontol line
          gotoxy(i,sy);printf("Í");    // Bottom Horizontal line
       }

       for (i=y+1;i<sy;i++)
       {
          gotoxy(x,i);printf("º");     //Left Vertical line
          gotoxy(sx,i);printf("º");    //Right Vertical Line
       }

          gotoxy(x+j,y);printf(text_); //put Title
          gotoxy(1,24);
    }
}

int main()
{
    runGame();
    return 0;
}

void runGame(){

    initGame();
    time_t start,end;
    time (&start);
    unsigned int counter = 0;
    unsigned int bombCounter = 30;
    unsigned int old_dif = 0;
    while(keypress != key_X){
        Keypressed();
        renderSight();
        Sleep(50);
        removeSight();
        time (&end);
        int dif = difftime (end,start);

        if(old_dif != dif){
            counter +=1;
            if(bombSet){
                    bombCounter -=1;
            }
            old_dif = dif;
        }
        if(counter == 10){
            money+=10;
            counter = 0;
        }

        if(bombSet){
            setcolor(31);gotoxy(60,22);printf("TIME BOMB  : %i", bombCounter);setcolor(15);
            if(bombCounter == 0 ){
                keypress = 120;
            }
        }
        setcolor(31);gotoxy(60,1);printf("TIME   : %i", dif);setcolor(15);
        setcolor(31);gotoxy(60,2);printf("MONEY  : %d", money);setcolor(15);
        setcolor(31);gotoxy(7,22);printf("AMMO  : %d", weapon.NUM_AMMO);setcolor(15);
        setcolor(31);gotoxy(32,22);printf("WEAPON : %s", weapon.NAME);setcolor(15);
        setcolor(31);gotoxy(7,23);printf("Sight  X=%d,Y=%d ",sight.x,sight.y );setcolor(15);
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}

        //     colors:
        //     0 = Black
        //     1 = Blue
        //     2 = Green
        //     3 = Cyan
        //     4 = Red
        //     5 = Magenta
        //     6 = Yellow
        //     7 = LightGray
        //     8 = DarkGray
        //     9 = LightBlue
        //     10 = LightGreen
        //     11 = LightCyan
        //     12 = LightRed
        //     13 = LightMagenta
        //     14 = LightYellow
        //     15 = White


void setForeGroundAndBackGroundColor(int ForeGroundColor,int BackGroundColor)
{
   int color=16*BackGroundColor+ForeGroundColor;
   setcolor(color);
}

void setWeapon(unsigned int a,unsigned int b,unsigned int c, unsigned char Color, char name[], char sound[]){
    weapon.NUM_AMMO = a;
    weapon.MAX_AMMO = b;
    weapon.NUM_PROJECTILE = c;
    weapon.COLOR = Color;
    strncpy(weapon.NAME, name, sizeof(weapon.NAME) - 1);
    strncpy(weapon.SOUND, sound, sizeof(weapon.SOUND) - 1);
}

void openShop(){
    setcolor(31);gotoxy(0, 0);printf("ITEM SHOP");
    setcolor(30);gotoxy(12, 0);printf("1. Hand Gun");
    setcolor(30);gotoxy(25, 0);printf("2. Riffle");
    setcolor(30);gotoxy(36, 0);printf("3. Bombs");
    int gunType = getch();
    int gun=0;
        switch(gunType){

        case key_1:
                setcolor(30);gotoxy(12, 1);printf("1. Desert Eagle");
                setcolor(30);gotoxy(12, 2);printf("2. 9mm");
                setcolor(30);gotoxy(12, 3);printf("3. 38 cal");
                setcolor(30);gotoxy(12, 4);printf("4. Knife");
                switch(gun=getch()){
                case key_1:
                    setWeapon(7,7,1,1,"Desert Eagle","BANG!!!");
                    break;
                case key_2:
                    setWeapon(12,12,1,1,"9MM","BANG!!!");
                    break;
                case key_3:
                    setWeapon(8,8,1,1,"38 cal","BANG!!!");
                    break;
                case key_4:
                    setWeapon(1,1,0,15,"Knife","SLICE!!");
                    break;
                }
            break;
        case key_2:
                setcolor(30);gotoxy(25, 1);printf("1. M16");
                setcolor(30);gotoxy(25, 2);printf("2. M50");
                setcolor(30);gotoxy(25, 3);printf("3. Shotgun");
                setcolor(30);gotoxy(25, 4);printf("4. One Shot");
                switch(gun=getch()){
                case key_1:
                    setWeapon(300,300,1,4,"M16","BANG!!!");
                    break;
                case key_2:
                    setWeapon(100,100,10,4,"M50","BANG!!!");
                    break;
                case key_3:
                    setWeapon(20,20,1,15,"Shotgun","BANG!!!");
                    break;
                case key_4:
                    setWeapon(10,10,1,6,"One Shot","BANG!!!");
                    break;
                }
            break;
        case key_3:
                setcolor(30);gotoxy(36, 1);printf("1. Grenade");
                setcolor(30);gotoxy(36, 2);printf("2. Smoke");
                setcolor(30);gotoxy(36, 3);printf("3. Bomb");
                switch(gun=getch()){
                case key_1:
                    setWeapon(2,2,1,4,"Grenade","BOOM!!!");
                    break;
                case key_2:
                    setWeapon(3,3,1,4,"Smoke","BOOM!!!");
                    break;
                case key_3:
                    setWeapon(2,2,1,4,"Bomb","BOOM!!!");
                    break;
                }
            break;
        }
    setcolor(15);
    clrscr();
}

void Keypressed(){
    if(kbhit()){
        keypress = getch();
        switch(keypress){

        case key_Q:
            openShop();
            break;

        case key_P:
                if(weapon.NUM_AMMO > 0){
                shoot(sight.x, sight.y);
                }
                if(strcmp("Bomb",weapon.NAME) ==0){
                    bombSet = true;
                }
            break;
        case key_SPACE:
            break;
        case key_R:
            weapon.NUM_AMMO = weapon.MAX_AMMO;
            break;

        case key_W:
            sight.y-=1;if(sight.y<2)sight.y=2;
            break;

        case key_A:
            sight.x-=1;if(sight.x<0)sight.x=0;
            break;

        case key_S:
            sight.y+=1;if(sight.y>18)sight.y=18;
            break;

        case key_D:
            sight.x+=1;if(sight.x>79)sight.x=79;
            break;
        }
    }
}

void renderSight(){
    txtPlot(sight.x,sight.y,15);
}

void removeSight(){
    txtPlot( sight.x,sight.y,0);
}

void shoot(unsigned char x, unsigned char y){
        weapon.NUM_AMMO = weapon.NUM_AMMO - weapon.NUM_PROJECTILE;
        setcolor(15);gotoxy(x,y);printf("*");setcolor(weapon.COLOR);gotoxy(x + 3,y);printf(weapon.SOUND);
        Sleep(100);
        setcolor(0);gotoxy(x,y);printf("*   %s",weapon.SOUND);
}

void txtPlot( unsigned char x, unsigned char y, unsigned char Color)
{
        setcolor(Color);gotoxy(x,y);printf("*");
}
void  initGame()
{
    sight.x = 40;
    sight.y = 9;
    setWeapon(7,7,1,1,"Desert Eagle","BANG!!!");
    money = 100;
    setcolor(15);
    clrscr();
}
void clrscr()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
    return;
}

void clrbox(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol)
{
    int x,y;
    setcolor(bkcol);                       //Set to color bkcol

    for (y=y1;y<y2;y++)                    //Fill Y Region Loop
    {
        for (x=x1;x<x2;x++)               //Fill X region Loop
        {
          gotoxy(x,y);printf(" ");       //Draw Solid space
        }
    }
}
