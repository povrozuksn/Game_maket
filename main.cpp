#include "TXLib.h"

struct Ship
{
    HDC right;
    HDC left;
    HDC image;
    int w;
    int h;
    int x;
    int y;
    int v;
    bool visible;

    void drawship()
    {
        if (visible)
        {
            txTransparentBlt (txDC(), x, y, w, h, image, 0, 0, TX_WHITE);
        }
    }
};

struct Bul
{
    int x;
    int y;
    int v;
    HDC image;
    bool visible;

    void drawBul()
    {
        if(visible)
        {
            txTransparentBlt (txDC(), x, y, 20, 78, image, 0, 0, TX_WHITE);
        }
    }

};

struct Button
{
    int x;
    int y;
    int w;
    int h;
    const char* text;

    void draw()
    {
       txSetColor(TX_RED, 5);
       txSetFillColor(TX_WHITE);
       txRectangle(x, y, x+w, y+h);
       txDrawText(x, y, x+w, y+h, text);

    }
};


int main()
{
txCreateWindow (800, 600);

    txSetColor (TX_WHITE, 5);

    string PAGE = "menu";

    HDC fon1 = txLoadImage("Pictures/fon1.bmp");
    HDC fon2 = txLoadImage("Pictures/fon2.bmp");
    HDC fon = fon1;

    Button btn_start = {300, 100, 200, 50, "СТАРТ"};
    Button btn_help  = {300, 170, 200, 50, "СПРАВКА"};
    Button btn_exit  = {300, 240, 200, 50, "ВЫХОД"};

    Ship ship1 = {txLoadImage("Pictures/boat.bmp"), ship1.right, ship1.right, 59, 186, 400, 500, 15, true};
    Ship ship2 = {txLoadImage("Pictures/ship_r.bmp"), txLoadImage("Pictures/ship_l.bmp"), ship2.right, 190, 59, 400, 0, 5, true};

    Bul bul = {400, 300, 0, txLoadImage("Pictures/torpeda.bmp"), false};

    int popadanie = 0;
    char str[50];

    while (PAGE != "exit")
    {
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();
        txSetFillColor (TX_WHITE);

        //Страница МЕНЮ
        if(PAGE == "menu")
        {
            btn_start.draw();
            btn_help.draw();
            btn_exit.draw();
            if( txMouseButtons() == 1 &&
                txMouseX() > btn_start.x && txMouseX() < btn_start.x + btn_start.w &&
                txMouseY() > btn_start.y && txMouseY() < btn_start.y + btn_start.h )
            {
                PAGE = "game";
            }
            if( txMouseButtons() == 1 &&
                txMouseX() > btn_help.x && txMouseX() < btn_help.x + btn_help.w &&
                txMouseY() > btn_help.y && txMouseY() < btn_help.y + btn_help.h )
            {
                PAGE = "help";
            }
            if( txMouseButtons() == 1 &&
                txMouseX() > btn_exit.x && txMouseX() < btn_exit.x + btn_exit.w &&
                txMouseY() > btn_exit.y && txMouseY() < btn_exit.y + btn_exit.h )
            {
                PAGE = "exit";
            }
        }

        //Страница HELP
        if(PAGE == "help")
        {
            txSetColor(TX_WHITE);
            txDrawText(0, 0, 800, 600, "Справка");
            if(GetAsyncKeyState (VK_ESCAPE))
            {
                PAGE = "menu";
            }
        }

        // Страница ИГРА
        if(PAGE == "game")
        {
            if(GetAsyncKeyState (VK_ESCAPE))
                {
                    PAGE = "menu";
                }
            txBitBlt(txDC(), 0, 0, 800, 600, fon);
            ship1.drawship();
            ship2.drawship();
            ship2.x += ship2.v;
            bul.drawBul();
            bul.y -= bul.v;

            if(GetAsyncKeyState ('A'))
            {
                ship1.x -= ship1.v;
            }
            else if(GetAsyncKeyState ('D'))
            {
                ship1.x += ship1.v;
            }

            if(ship1.x+ship1.h/2>400)
            {
                fon = fon2;
            }
            else
            {
                fon = fon1;
            }

            if(ship1.x<0)
            {
                ship1.x = 0;
            }
            if(ship1.x+59>800)
            {
                ship1.x = 800-59;
            }

            if(ship2.x<-300)
            {
                ship2.v = -ship2.v;
                ship2.image = ship2.right;
            }
            if(ship2.x+190>1300)
            {
                ship2.v = -ship2.v;
                ship2.image = ship2.left;
            }

            if(GetAsyncKeyState (VK_SPACE))
            {
                bul.x = ship1.x+ship1.w/2;
                bul.y = ship1.y;
                bul.visible = true;
                bul.v = 10;
            }

            if(bul.x>=ship2.x && bul.x<=ship2.x+ship2.w && bul.y>=ship2.y && bul.y<=ship2.y+ship2.h)
            {
                ship2.visible = false;
                bul.visible = false;
                txSleep(50);
                popadanie += 1;
            }



            sprintf(str, "Число попаданий - %d", popadanie);
            txTextOut(0, 400, str);
        }

        txEnd();
        txSleep(50);
    }

    txDeleteDC (ship1.right);
    txDeleteDC (ship1.left);

txDisableAutoPause();
txTextCursor (false);
return 0;
}

