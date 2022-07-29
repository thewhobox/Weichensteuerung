#include <Arduino.h>
#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)
#include <Wire.h>
#include "gleise.h"

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    Wire.begin(); //D2, D1

    Serial.begin(9600);
    delay(1000);
    Serial.print("Bereit");
    tft.init();
    tft.setRotation(3);

    uint16_t calData[5] = { 323, 3338, 395, 3323, 3 };
    tft.setTouch(calData);
}

enum ProgState
{
    Init,
    Normal
};

int progState = ProgState::Init;
int stateCount = 0;




bool getTouch(uint16_t *x, uint16_t *y)
{
    uint16_t x2;
    uint16_t y2;
    bool touched = tft.getTouch(&x2, &y2);
    if(touched)
    {
        *x = -0.080 * x2 + 11.84 + x2;
        *y = -0.075 * y2 + 9.725 + y2;
    }
    return touched;
}


int lineThickness = 2;
uint32_t colorGleis = TFT_BLACK;
uint32_t colorStraight = TFT_BLACK;
uint32_t colorBlocked = TFT_WHITE;


void drawGleis(Gleis *g)
{
    switch(g->type)
    {
        case Type::Gerade:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = g->posY * 24;
                int y2 = (g->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, colorGleis);
            }
            break;
        }

        case Type::Gerade90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = g->posX * 24;
                int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, colorGleis);
            }
            break;
        }

        case Type::Kurve:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 23;
                int y1 = g->posY * 24;
                int y2 = (g->posY * 24) + 11 + (lineThickness / 2) - i;
                tft.drawLine(x1, y1, x2, y2, colorGleis);
            }
            break;
        }
        case Type::Kurve90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = (g->posY * 24) + 23;
                int x2 = (g->posX * 24) + 23;
                int y2 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                tft.drawLine(x1, y1, x2, y2, colorGleis);
            }
            break;
        }

        case Type::Kurve180:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = g->posX * 24;
                int y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y2 = (g->posY * 24) + 23;
                tft.drawLine(x1, y1, x2, y2, colorGleis);
            }
            break;
        }
        
        case Type::Kurve270:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (g->posX * 24);
                int y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                int y2 = (g->posY * 24);
                tft.drawLine(x1, y1, x2, y2, colorGleis);
            }
            break;
        }
        
        case Type::Tunnel:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = g->posY * 24;
                int y2 = (g->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, colorGleis);

                int x1 = g->posX * 24;
                int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 7;
                tft.drawLine(x1, y, x2, y, colorGleis);
                
                x1 = g->posX * 24 + 16;
                y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                x2 = (g->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, colorGleis);
            }
            break;
        }
        
        case Type::Tunnel90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = g->posX * 24;
                int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, colorGleis);
                
                int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = g->posY * 24;
                int y2 = (g->posY * 24) + 7;
                tft.drawLine(x, y1, x, y2, colorGleis);
                
                x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                y1 = g->posY * 24 + 16;
                y2 = (g->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, colorGleis);
            }
            break;
        }

        case Type::WeicheL:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = g->posX * 24;
                    int y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
                    int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, colorGleis);
                }
            }
            break;
        }

        case Type::WeicheL90:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24);
                    int y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (g->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                }
            }
            break;
        }

        case Type::WeicheL270:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = (g->posY * 24) + 23;
                    int x2 = (g->posX * 24) + 23;
                    int y2 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                }
            }
            break;
        }
        
        case Type::WeicheR:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = (g->posY * 24) + 23;
                    int x2 = (g->posX * 24) + 23;
                    int y2 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, colorGleis);
                }
            }
            break;
        }
        
        case Type::WeicheR270:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 11 + (lineThickness / 2) - i;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
        	        int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                }
            }
            break;
        }
        
        case Type::Kreuz:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24);
                    int y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (g->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, colorGleis);

                    x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y1 = (g->posY * 24) + 23;
                    x2 = (g->posX * 24) + 23;
                    y2 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, colorGleis);

                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                    
                    x1 = g->posX * 24 + 16;
                    y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                }
            }
            break;
        }
        
        case Type::Kreuz90:
        {
            tft.fillRect(g->posX * 24, g->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(g->posX * 24, g->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(g->direction)
                {
                    int x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 11 + (lineThickness / 2) - i;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);

                    x1 = g->posX * 24;
                    y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y2 = (g->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, colorGleis);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, colorGleis);

                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                    
                    x1 = g->posX * 24 + 16;
                    y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, colorGleis);
                }
            }
            break;
        }
    }
}

void handleGleis(Gleis *g)
{
    switch(g->state)
    {
        case State::Initial:
        case State::Updated:
        {
           drawGleis(g);
           g->state = State::Untouched;
           break;
        }

        case State::Untouched:
            break;
    }
}

bool isTouched = false;

void normalLoop()
{
    int gleisCount = (sizeof(gleise) / sizeof(gleise[0]));
    for(int i = 0; i < gleisCount; i++)
    {
        handleGleis(&gleise[i]);
    }
    
    uint16_t touchX;
    uint16_t touchY;
    if(!isTouched && getTouch(&touchX, &touchY))
    {
        isTouched = true;
        int rest = touchX % 24;
        int col = (touchX - rest) / 24;
        rest = touchY % 24;
        int row = (touchY - rest) / 24;
        int counter = col * 10 + row;

        Gleis *gleis = &gleise[counter];
        int type = gleis->type;

        if(type > 99) //Nur wenn Type eine Weiche ist (struct > 99)
        {
            Serial.println("Weiche umgestellt");
            gleis->direction = !gleis->direction;
            gleis->state = State::Updated;
            Serial.print("Button ");
            
            Serial.print("state is ");
            Serial.println(gleis->direction ? "on" : "off");

            Serial.printf("Write to %2X\n", gleis->i2c_addr);
            byte data = gleis->nummer; //(addresses[i] & 0b1111) << 1;
            data = data | gleis->direction;
            Serial.print("Data ");
            Serial.print(data, HEX);
            Serial.println();
            Wire.beginTransmission(gleis->i2c_addr);
            Wire.write(data);
            Wire.endTransmission();
            delay(200);
        }
    } else {
        isTouched = false;
    }
}

bool filledScreen = false;

void loop()
{
    // put your main code here, to run repeatedly:
    switch (progState)
    {
        case ProgState::Init:
        {
            progState = ProgState::Normal;
            break;
        } 

        case ProgState::Normal:
            if(!filledScreen)
            {                
                tft.fillScreen(TFT_WHITE);
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.drawLine(288, 0, 288, 240, TFT_DARKGREEN);
                filledScreen = true;
            }
            normalLoop();
            break;
    }
}
