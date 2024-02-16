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

    int count_btn = 5;
    Button btn[count_btn];

    btn[0]  = {300, 100, 200, 50, "—“¿–“"};
    btn[1]  = {300, 170, 200, 50, "—œ–¿¬ ¿"};
    btn[2]  = {300, 240, 200, 50, "¬€’Œƒ"};
    btn[3]  = {300, 310, 200, 50, "œ¿–¿Ã≈“–€"};
    btn[4]  = {300, 380, 200, 50, " Œ¡ ¿¬“Œ–≈"};

    Ship ship1 = {txLoadImage("Pictures/boat.bmp"), ship1.right, ship1.right, 59, 186, 400, 500, 15, true};

    int count_ship = 3;
    Ship ship[count_ship];
    ship[0] = {txLoadImage("Pictures/ship_r.bmp"), txLoadImage("Pictures/ship_l.bmp"), txLoadImage("Pictures/ship_r.bmp"), 190, 59, 400, 0, 5, true};
    ship[1] = {ship[0].right, ship[0].left, ship[0].right, 190, 59, 0, 40, 5, true};
    ship[2] = {ship[0].right, ship[0].left, ship[0].right, 190, 59, 600, 80, 5, true};

    Bul bul = {400, 300, 0, txLoadImage("Pictures/torpeda.bmp"), false};

    int popadanie = 0;
    char str[50];

    int x_mouse;
    int y_mouse;

    while (PAGE != "exit")
    {
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();
        txSetFillColor (TX_WHITE);

        //—Ú‡ÌËˆ‡ Ã≈Õﬁ
        if(PAGE == "menu")
        {
            for(int i=0; i<count_btn; i++)
            {
                btn[i].draw();
            }

            if( txMouseButtons() == 1 &&
                txMouseX() > btn[0].x && txMouseX() < btn[0].x + btn[0].w &&
                txMouseY() > btn[0].y && txMouseY() < btn[0].y + btn[0].h )
            {
                PAGE = "game";
            }
            if( txMouseButtons() == 1 &&
                txMouseX() > btn[1].x && txMouseX() < btn[1].x + btn[1].w &&
                txMouseY() > btn[1].y && txMouseY() < btn[1].y + btn[1].h )
            {
                PAGE = "help";
            }
            if( txMouseButtons() == 1 &&
                txMouseX() > btn[2].x && txMouseX() < btn[2].x + btn[2].w &&
                txMouseY() > btn[2].y && txMouseY() < btn[2].y + btn[2].h )
            {
                PAGE = "exit";
            }
        }

        //—Ú‡ÌËˆ‡ HELP
        if(PAGE == "help")
        {
            txSetColor(TX_WHITE);
            txDrawText(0, 0, 800, 600, "—Ô‡‚Í‡");
            if(GetAsyncKeyState (VK_ESCAPE))
            {
                PAGE = "menu";
            }
        }

        // —Ú‡ÌËˆ‡ »√–¿
        if(PAGE == "game")
        {
            if(GetAsyncKeyState (VK_ESCAPE))
                {
                    PAGE = "menu";
                }
            txBitBlt(txDC(), 0, 0, 800, 600, fon);
            ship1.drawship();

            for(int i=0; i<count_ship; i++)
            {
                ship[i].drawship();
            }

            for(int i=0; i<count_ship; i++)
            {
                ship[i].x += ship[i].v;
            }

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

            for (int i=0; i<count_ship; i++)
            {
                if(ship[i].x<-300)
                {
                    ship[i].v = -ship[i].v;
                    ship[i].image = ship[i].right;
                }
                if(ship[i].x+190>1300)
                {
                    ship[i].v = -ship[i].v;
                    ship[i].image = ship[i].left;
                }
            }

            if(GetAsyncKeyState (VK_SPACE))
            {
                bul.x = ship1.x+ship1.w/2;
                bul.y = ship1.y;
                bul.visible = true;
                bul.v = 10;
            }

             for (int i=0; i<count_ship; i++)
            {
                if(bul.x>=ship[i].x && bul.x<=ship[i].x+ship[i].w && bul.y>=ship[i].y && bul.y<=ship[i].y+ship[i].h)
                {
                    ship[i].visible = false;
                    bul.visible = false;
                    ship[i].x = 1000;
                    txSleep(50);
                    popadanie += 1;
                    ship[i].visible = true;
                }
            }

            sprintf(str, "◊ËÒÎÓ ÔÓÔ‡‰‡ÌËÈ - %d", popadanie);
            txTextOut(0, 400, str);

            x_mouse = txMouseX();
            sprintf(str, "X mouse - %d", x_mouse);
            txTextOut(0, 0, str);

            y_mouse = txMouseY();
            sprintf(str, "Y mouse - %d", y_mouse);
            txTextOut(0, 20, str);
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

