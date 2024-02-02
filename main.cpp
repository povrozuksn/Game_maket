#include "TXLib.h"

struct Car
{
    HDC right;
    HDC left;
    HDC up;
    HDC down;
    HDC image;
    int w;
    int h;
    int x;
    int y;
    int v;
    bool visible;

    void drawCar()
    {
        if (visible)
        {
            if (image == right || image == left)
                {
                    txTransparentBlt (txDC(), x, y, w, h, image, 0, 0, TX_WHITE);
                }
            else if (image == up || image == down)
                {
                    txTransparentBlt (txDC(), x, y, h, w, image, 0, 0, TX_WHITE);
                }
        }
    }
};

struct Bul
{
    int x;
    int y;
    int v;
    bool visible;

    void drawBul()
    {
        if(visible)
        {
            txSetColor(TX_WHITE);
            txSetFillColor(TX_WHITE);
            txCircle(x, y, 5);
        }
    }

};

struct Mario
{
    int x;
    int y;
    int vy;
    HDC image;
    int level;

    void drawMario()
    {
        txTransparentBlt (txDC(), x, y, 100, 124, image, 0, 0, TX_BLACK);
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

    Button btn_start = {300, 100, 200, 50, "ÑÒÀÐÒ"};
    Button btn_help  = {300, 170, 200, 50, "ÑÏÐÀÂÊÀ"};
    Button btn_exit  = {300, 240, 200, 50, "ÂÛÕÎÄ"};

    Car car1 = {txLoadImage("Pictures/rightCar1.bmp"), txLoadImage("Pictures/leftCar1.bmp"), txLoadImage("Pictures/upCar1.bmp"), txLoadImage("Pictures/downCar1.bmp"), car1.up, 190, 95, 400, 400, 15, true};
    Car car2 = {txLoadImage("Pictures/rightCar2.bmp"), txLoadImage("Pictures/leftCar2.bmp"), txLoadImage("Pictures/upCar2.bmp"), txLoadImage("Pictures/downCar2.bmp"), car2.right, 190, 95, 400, 0, 15, true};

    Bul bul = {400, 300, 0, false};

    Mario mario = {200, 400, 20, txLoadImage("Pictures/mario.bmp"), 524};

    while (PAGE != "exit")
    {
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();
        txSetFillColor (TX_WHITE);

        //Ñòðàíèöà ÌÅÍÞ
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

        //Ñòðàíèöà HELP
        if(PAGE == "help")
        {
            txSetColor(TX_WHITE);
            txDrawText(0, 0, 800, 600, "Ñïðàâêà");
            if(GetAsyncKeyState (VK_ESCAPE))
            {
                PAGE = "menu";
            }
        }

        // Ñòðàíèöà ÈÃÐÀ
        if(PAGE == "game")
        {
            if(GetAsyncKeyState (VK_ESCAPE))
                {
                    PAGE = "menu";
                }
            txBitBlt(txDC(), 0, 0, 800, 600, fon);
            car1.drawCar();
            car2.drawCar();
            car2.x += car2.v;
            bul.drawBul();
            bul.y -= bul.v;
            mario.drawMario();
            mario.y += mario.vy;
            mario.vy += 2;

            if(mario.y+124 >= mario.level)
            {
                mario.vy = 0;
            }

            if(GetAsyncKeyState ('Y'))
            {
                mario.vy = -20;
            }

            if(GetAsyncKeyState ('A'))
            {
                car1.x -= car1.v;
            }
            else if(GetAsyncKeyState ('D'))
            {
                car1.x += car1.v;
            }

            if(car1.x+car1.h/2>400)
            {
                fon = fon2;
            }
            else
            {
                fon = fon1;
            }

            if(car1.x<0)
            {
                car1.x = 0;
            }
            if(car1.x+95>800)
            {
                car1.x = 800-95;
            }

            if(car2.x<0)
            {
                car2.v = -car2.v;
                car2.image = car2.right;
            }
            if(car2.x+190>800)
            {
                car2.v = -car2.v;
                car2.image = car2.left;
            }

            if(GetAsyncKeyState (VK_SPACE))
            {
                bul.x = car1.x+car1.h/2;
                bul.y = car1.y;
                bul.visible = true;
                bul.v = 10;
            }

            if(bul.x>=car2.x && bul.x<=car2.x+car2.w && bul.y>=car2.y && bul.y<=car2.y+car2.h)
            {
                car2.visible = false;
                bul.visible = false;
            }
        }

        txEnd();
        txSleep(50);
    }

    txDeleteDC (car1.right);
    txDeleteDC (car1.left);
    txDeleteDC (car1.up);
    txDeleteDC (car1.down);

txDisableAutoPause();
txTextCursor (false);
return 0;
}

