//
// Created by tymbys on 25.07.19.
//

#ifndef TEST1_FB_H
#define TEST1_FB_H

#include <stdint.h>
#include <iostream>

class fb { // singleton
   unsigned char FontHeight = 10, FontWidth = 10;


public:
    static fb &GetInstance() { // public singleton instance accessor
        static fb instance; // initialized on first call to GetInstance
        return instance;
    }

    static const uint32_t Width = 128;
    static const uint32_t Height = 64;
    static const uint32_t CACHSIZE = Width * (int) (Height / 8 + 8);

    unsigned char FBCache[CACHSIZE]={0};


    void OLED_DrawPoint_fast(unsigned char x, unsigned char y, unsigned char mode)
    {
        int index;
        unsigned char offset=0, data=0, dx=0;

        if ( x >= Width ) return;	//åñëè ïåðåäàëè â ôóíêöèþ ìóòü - âûõîäèì
        if ( y >= Height ) return;


        //index = (((int)(y)/8)*Width)+x;    //ñ÷èòàåì íîìåð áàéòà â ìàññèâå ïàìÿòè äèñïëåÿ
        //offset  = y-((y/8)*8);          //ñ÷èòàåì íîìåð áèòà â ýòîì áàéòå

        index = ((int)(x/8))+(int)(Width/8 )*y;    //ñ÷èòàåì íîìåð áàéòà â ìàññèâå ïàìÿòè äèñïëåÿ
        offset  = x-(((int)(x/8))*8);
        offset = 7 - offset;
        dx=x/8;
//        offset  = dx + x -dx*8;
//        offset  = dx ;

//        std::cout << "x/8 : " << x/8 <<  std::endl;

        std::cout << "index:" << index << " offset: "<< (int)offset << " X: " << (int)x << " Y: " << (int)y <<  std::endl;

        data = FBCache[index];         //áåðåì áàéò ïî íàéäåííîìó èíäåêñó

        //data = ( 0x01 << offset );

        if ( mode == 0 ) data &= ( ~( 0x01 << offset ) );	//ðåäàêòèðóåì áèò â ýòîì áàéòå
        else if ( mode == 1 ) data |= ( 0x01 << offset );
        //else if ( mode  == PIXEL_XOR ) data ^= ( 0x01 << offset );

        FBCache[index] = data;
    }


    void OLED_DrawLine_fast (int x1, int y1, int x2, int y2, unsigned char mode)  	//Draws a line between two points on the display - ïî Áðåçåíõåéìó
    {
        signed int dy = 0;
        signed int dx = 0;
        signed int stepx = 0;
        signed int stepy = 0;
        signed int fraction = 0;

        if (x1>Width || x2>Width || y1>Height || y2>Height) return;

        dy = y2 - y1;
        dx = x2 - x1;
        if (dy < 0)
        {
            dy = -dy;
            stepy = -1;
        }
        else stepy = 1;
        if (dx < 0)
        {
            dx = -dx;
            stepx = -1;
        }
        else stepx = 1;
        dy <<= 1;
        dx <<= 1;
        OLED_DrawPoint_fast(x1,y1,mode);
        if (dx > dy)
        {
            fraction = dy - (dx >> 1);
            while (x1 != x2)
            {
                if (fraction >= 0)
                {
                    y1 += stepy;
                    fraction -= dx;
                }
                x1 += stepx;
                fraction += dy;
                OLED_DrawPoint_fast(x1,y1,mode);
            }
        }
        else
        {
            fraction = dx - (dy >> 1);
            while (y1 != y2)
            {
                if (fraction >= 0)
                {
                    x1 += stepx;
                    fraction -= dy;
                }
                y1 += stepy;
                fraction += dx;
                OLED_DrawPoint_fast(x1,y1,mode);
            }
        }
    }

};





#endif //TEST1_FB_H
