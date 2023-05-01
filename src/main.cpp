#include <Arduino.h>
#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)
#include <Wire.h>
#include "tracks.h"
#include "place.h"
#include "icon_manual.h"
#include "icon_signal.h"

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    Wire.begin(); //D2, D1

    Serial.begin(9600);
    delay(500);
    Serial.print("Bereit");
    tft.init();
    tft.setRotation(3);

    uint16_t calData[5] = { 323, 3338, 395, 3323, 3 };

    //tft.calibrateTouch(calData, TFT_RED, TFT_WHITE, 10);

    tft.setTouch(calData);
}

enum ProgState
{
    Init,
    Normal,
    PathFinding
};

enum Icons
{
    Manual,
    LightSignal
};

struct MenuItem {
    bool isUpdated;
    bool isSelected;
    const Icons icon;
};

struct MenuItem MenuItems[] = {
    {
        .isUpdated = true,
        .isSelected = true,
        .icon = Icons::Manual
    },
    {
        .isUpdated = true,
        .isSelected = false,
        .icon = Icons::LightSignal
    }
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
    return false;
}


int lineThickness = 2;
uint32_t colorTrack = TFT_BLACK;
uint32_t colorSelected = TFT_GREEN; //TFT_ORANGE;
uint32_t colorBlocked = TFT_RED;
uint32_t colorMenu = TFT_BLACK;
uint32_t colorMenuSelected = TFT_ORANGE;
uint32_t colorMenuLine = TFT_DARKGREEN;

void drawTrack(Track *t)
{
    uint32_t trackColor1 = t->isTrack1Selected ? colorSelected : colorTrack;
    uint32_t trackColor2 = t->isTrack2Selected ? colorSelected : colorTrack;

    switch(t->type)
    {
        case Type::Gerade:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, trackColor1);
            }
            break;
        }

        case Type::Gerade90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = t->posX * 24;
                int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, trackColor1);
            }
            break;
        }

        case Type::Kurve:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 23;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 11 + (lineThickness / 2) - i;
                tft.drawLine(x1, y1, x2, y2, trackColor1);
            }
            break;
        }
        case Type::Kurve90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = (t->posY * 24) + 23;
                int x2 = (t->posX * 24) + 23;
                int y2 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                tft.drawLine(x1, y1, x2, y2, trackColor1);
            }
            break;
        }

        case Type::Kurve180:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = t->posX * 24;
                int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y2 = (t->posY * 24) + 23;
                tft.drawLine(x1, y1, x2, y2, trackColor1);
            }
            break;
        }
        
        case Type::Kurve270:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = (t->posX * 24);
                int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                int y2 = (t->posY * 24);
                tft.drawLine(x1, y1, x2, y2, trackColor1);
            }
            break;
        }
        
        case Type::Tunnel:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, trackColor1);

                int x1 = t->posX * 24;
                int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 7;
                tft.drawLine(x1, y, x2, y, trackColor2);
                
                x1 = t->posX * 24 + 16;
                y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                x2 = (t->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, trackColor2);
            }
            break;
        }
        
        case Type::Tunnel90:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x1 = t->posX * 24;
                int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, trackColor1);
                
                int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 7;
                tft.drawLine(x, y1, x, y2, trackColor2);
                
                x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                y1 = t->posY * 24 + 16;
                y2 = (t->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, trackColor2);
            }
            break;
        }

        case Type::WeicheL:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = t->posX * 24;
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);
                }
            }
            break;
        }

        case Type::WeicheL90:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24);
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor1);
                }
            }
            break;
        }

        case Type::WeicheL180:
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 11 + (lineThickness / 2) - i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);
                }
            }
            break;
            break;

        case Type::WeicheL270:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = (t->posY * 24) + 23;
                    int x2 = (t->posX * 24) + 23;
                    int y2 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor1);
                }
            }
            break;
        }
        
        case Type::WeicheR:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = (t->posY * 24) + 23;
                    int x2 = (t->posX * 24) + 23;
                    int y2 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);
                }
            }
            break;
        }
        
        case Type::WeicheR45:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(!t->direction)
                {
                    int x1 = (t->posX * 24);
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor1);
                }
            }
            break;
        }

        case Type::WeicheR90:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = t->posX * 24;
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor1);
                }
            }
            break;
        }

        case Type::WeicheR180:
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24);
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);
                }
            }
            break;
            break;

        
        case Type::WeicheR270:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 11 + (lineThickness / 2) - i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
        	        int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor1);
                }
            }
            break;
        }
        
        case Type::Kreuz90:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 11 + (lineThickness / 2) - i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);

                    x1 = t->posX * 24;
                    y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y2 = (t->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, trackColor2);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);

                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, trackColor2);
                    
                    x1 = t->posX * 24 + 16;
                    y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor2);
                }
            }
            break;
        }

        case Type::Kreuz270:
        {
            tft.fillRect(t->posX * 24, t->posY * 24, 24, 24, TFT_WHITE);
            tft.drawRect(t->posX * 24, t->posY * 24, 24, 24, TFT_BLUE);

            for(int i = 0; i < lineThickness; i ++)
            {
                if(t->direction)
                {
                    int x1 = (t->posX * 24);
                    int y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24)+ 11 - ((lineThickness - 2) / 2) + i;
                    int y2 = (t->posY * 24);
                    tft.drawLine(x1, y1, x2, y2, trackColor2);

                    x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y1 = (t->posY * 24) + 23;
                    x2 = (t->posX * 24) + 23;
                    y2 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, trackColor1);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, trackColor1);

                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, trackColor2);
                    
                    x1 = t->posX * 24 + 16;
                    y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, trackColor2);
                }
            }
            break;
        }
        
    }

    t->isUpdated = false;
}

void drawSignal(Signal *s)
{
    int startX = s->posX * 24;
    int startY = s->posY * 24;

    switch(s->position)
    {
        case Position::NO:
        {
            break;
        }
        
        case Position::OS:
        {
            break;
        }
        
        case Position::SW:
        {
            break;
        }
        
        case Position::WN:
        {
            tft.fillCircle(startX + 5, startY + 5, 3, s->lightState ? TFT_GREEN : TFT_RED);
            break;
        }
    }

    s->isUpdated = false;
}

void drawMenuItem(MenuItem *m, int index)
{
    tft.fillRect(288, index * 32, 320, index * 32 + 32, TFT_WHITE);

    switch(m->icon)
    {
        case Icons::Manual:
            tft.drawXBitmap(288, index * 32, icon_manual, 32, 32, m->isSelected ? colorMenuSelected : colorMenu);
            tft.drawLine(288, index * 32 + 31, 320, index * 32 + 31, colorMenuLine);
            break;

        case Icons::LightSignal:
            tft.drawXBitmap(288, index * 32, icon_signal, 32, 32, m->isSelected ? colorMenuSelected : colorMenu);
            tft.drawLine(288, index * 32 + 31, 320, index * 32 + 31, colorMenuLine);
            break;
    }

    m->isUpdated = false;
}

int lastTouch = 0;
int firstTrack = -1;
int lastTrack = -1;

bool filledScreen = false;
bool firstPathFinding = false;


void switchTrack(Track *t, bool state, bool wait = false)
{
    Serial.println("Weiche umgestellt");
    t->direction = state;
    t->isUpdated = true;

    Serial.print("state is ");
    Serial.println(t->direction ? "on" : "off");

    Serial.printf("Write to %2X\n", t->i2c_addr);
    byte data = t->nummer << 1; //(addresses[i] & 0b1111) << 1;
    data = data | t->direction;
    //Serial.print("Data ");
    //Serial.print(data, HEX);
    //Serial.println();
    Wire.beginTransmission(t->i2c_addr);
    Wire.write(data);
    Wire.endTransmission();

    if(wait) delay(100);
}

void switchSignal(Signal *s, bool state)
{
    Serial.println("Signal umgestellt");
    s->lightState = state;
    s->isUpdated = true;  

    Serial.print("state is ");
    Serial.println(s->lightState ? "green" : "red");

    Serial.printf("Write to %2X\n", s->i2c_addr);
    byte data = s->nummer; //(addresses[i] & 0b1111) << 1;
    data = data | s->lightState;
    Serial.print("Data ");
    Serial.print(data, HEX);
    Serial.println();
    Wire.beginTransmission(s->i2c_addr);
    Wire.write(data);
    Wire.endTransmission();
}

void doTracks()
{
    int TrackCount = (sizeof(tracks) / sizeof(tracks[0]));
    for(int i = 0; i < TrackCount; i++)
    {
        if(tracks[i].isUpdated)
            drawTrack(&tracks[i]);
    }
}

void doSignals()
{
    int SignalCount = (sizeof(signals) / sizeof(signals[0]));
    for(int i = 0; i < SignalCount; i++)
    {
        if(signals[i].isUpdated)
           drawSignal(&signals[i]);
    }
}

void doMenu()
{
    int menuCount = (sizeof(MenuItems) / sizeof(MenuItems[0]));
    for(int i = 0; i < menuCount; i++)
    {
        if(MenuItems[i].isUpdated)
           drawMenuItem(&MenuItems[i], i);
    }
}

void normalLoop()
{
    doTracks();
    doSignals();
    doMenu();

    uint16_t touchX;
    uint16_t touchY;
    if(millis() - lastTouch > 200 && getTouch(&touchX, &touchY))
    {
        lastTouch = millis();

        if(touchX > 287) //its Menu
        {
            int rest = touchY % 32;
            int index = (touchY - rest) / 32;
            int menuCount = (sizeof(MenuItems) / sizeof(MenuItems[0]));
            if(index > (menuCount -1)) return;
            MenuItem *item = &MenuItems[index];
            item->isSelected = !item->isSelected;
            item->isUpdated = true;
        } else { //its track
            int rest = touchX % 24;
            int col = (touchX - rest) / 24;
            rest = touchY % 24;
            int row = (touchY - rest) / 24;
            int counter = col * 10 + row;

            Serial.print("X:");
            Serial.print(col);
            Serial.print(" / Y:");
            Serial.println(row);

            if(MenuItems[1].isSelected)
            {
                int SignalCount = (sizeof(signals) / sizeof(signals[0]));
                for(int i = 0; i < SignalCount; i++)
                {
                    if(signals[i].posX == col && signals[i].posY == row)
                    {
                        switchSignal(&signals[i], !(signals[i].lightState));
                        return;
                    }
                }
            }


            Track *t = &tracks[counter];
            int type = t->type;

            if(type > 99) //Nur wenn Type eine Weiche ist (struct > 99)
            {
                switchTrack(t, !t->direction, true);
            } else if(t->type != Type::Leer && MenuItems[0].isSelected) {
                if(t->isTrack1Selected)
                {
                    t->isTrack1Selected = false;
                    t->isUpdated = true;
                    firstTrack = -1;
                } else {
                    t->isTrack1Selected = true;
                    t->isUpdated = true;
                    if(firstTrack == -1)
                    {
                        firstTrack = counter;
                        Serial.println("First Track Selected");
                    } else {
                        lastTrack = counter;
                        drawTrack(t);
                        progState = ProgState::PathFinding;
                        Serial.println("Mache jetzt PathFinding");
                    }
                }
            }
        }
    }
}

void addTrackSwitch(char name){
    char buffer[3];
    buffer[0] = name;
    buffer[1] = '4';
    buffer[2] = '\0';
    place *p4 = place_new(buffer);
    buffer[1] = '7';
    place *p7 = place_new(buffer);
    buffer[1] = '6';
    place *p6 = place_new(buffer);

    place_add_way(p4, p7, 0);
    place_add_way(p7, p4, 0);
    place_add_way(p4, p6, 0);
    place_add_way(p6, p4, 0);
}

void addTrackSwitchCross(char name)
{
    char buffer[3];
    buffer[0] = name;
    buffer[1] = '7';
    buffer[2] = '\0';
    place *p7 = place_new(buffer);
    buffer[1] = '6';
    place *p6 = place_new(buffer);
    buffer[1] = '5';
    place *p5 = place_new(buffer);
    buffer[1] = '8';
    place *p8 = place_new(buffer);

    place_add_way(p7, p5, 0);
    place_add_way(p5, p7, 0);
    place_add_way(p7, p8, 0);
    place_add_way(p8, p7, 0);
    
    place_add_way(p6, p8, 0);
    place_add_way(p8, p6, 0);
    place_add_way(p6, p5, 0);
    place_add_way(p5, p6, 0);
}

void connectTracks(char *start, char *end, int distance)
{
    place *p1 = place_get(start);
    place *p2 = place_get(end);
    place_add_way(p1, p2, distance);
    place_add_way(p2, p1, distance);
}

void initPath() {
    //addTrackSwitch('C');
    //addTrackSwitchCross('E');
    //place_new("Y1");
    //connectTracks("A0", "B0", 5); //x1

    addTrackSwitch('A');
    addTrackSwitchCross('B');
    addTrackSwitch('C');
    addTrackSwitch('D');
    addTrackSwitchCross('E');
    addTrackSwitch('F');

    //Big Connection West
    connectTracks("A6", "F6", 5);
    connectTracks("A7", "B8", 2);
    connectTracks("B7", "E7", 4);
    connectTracks("E8", "F7", 2);
    connectTracks("B6", "C7", 2);
    connectTracks("C4", "D4", 3);
    connectTracks("D7", "E6", 2);

    addTrackSwitch('G');
    addTrackSwitchCross('H');
    addTrackSwitch('I');

    //Big Connection South
    connectTracks("G7", "H8", 2);
    connectTracks("H6", "I7", 2);

    //Connect Big West and South
    connectTracks("F4", "G4", 5);
    connectTracks("E5", "H5", 5);
    connectTracks("D6", "I6", 5);
}

int pathFound = -1;

void loop()
{
    switch (progState)
    {
        case ProgState::Init:
        {
            Serial.println("Init");
            initPath();
            Serial.println("Init fertig");
            progState = ProgState::Normal;
            break;
        }

        case ProgState::Normal:
            if(!filledScreen)
            {                
                tft.fillScreen(TFT_WHITE);
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.drawLine(287, 0, 287, 240, colorMenuLine);
                filledScreen = true;
            }
            normalLoop();
            break;

        case ProgState::PathFinding:
        {
            doTracks();
            if(pathFound == -1)
            {
                Track track1 = tracks[firstTrack];
                Track track2 = tracks[lastTrack];

                Serial.print("Planned: ");
                Serial.print(track1.track);
                Serial.print(" -> ");
                Serial.println(track2.track);

                char route[100];
                int sw = millis();
                int length = place_get_route(track1.track, track2.track, route);
                int sw2 = millis() - sw;
                Serial.print("Route (");
                Serial.print(length);
                Serial.print(" e, ");
                Serial.print(sw2);
                Serial.print(" ms) -> ");
                Serial.println(route);

                char needle[5];
                int trackCount = (sizeof(tracks) / sizeof(tracks[0]));

                for(int i = 0; i < trackCount; i++)
                {
                    Track *t = &tracks[i];

                    if(t->type < 100)
                    {
                        sprintf(needle, "%s", t->track);

                        if(strlen(t->track) > 1 && strstr(route, needle) != NULL)
                        {
                            t->isTrack1Selected = true;
                            t->isUpdated = true;
                        }
                        if(t->type == Type::Tunnel || t->type == Type::Tunnel90)
                        {
                            sprintf(needle, "%s", t->track2);

                            if(strlen(t->track2) > 1 && strstr(route, needle) != NULL)
                            {
                                t->isTrack2Selected = true;
                                t->isUpdated = true;
                            }
                        }
                    } else {
                        if(strlen(t->track) > 1)
                        {
                            needle[0] = t->track[0];
                            needle[1] = '\0';
                            char *heuhaufen = route;
                            int counter = 0;
                            
                            while(true)
                            {
                                char *fund = strstr(heuhaufen, needle);
                                if(fund == NULL) break;
                                heuhaufen = fund + 2;
                                counter += fund[1] - 48;
                            }

                            Serial.print(t->track[0]);
                            Serial.print(" found ");
                            Serial.println(counter);

                            if(counter > 9)
                            {
                                bool newState = counter % 2 != 0;
                                t->isUpdated = true;
                                
                                if(t->type >= 200)
                                {
                                    if(counter == 15 || counter == 12)
                                        t->isTrack1Selected = true;
                                    else
                                        t->isTrack2Selected = true;

                                    if(t->direction != newState)
                                    {
                                        switchTrack(t, newState, true);
                                    }
                                } else {
                                    t->isTrack1Selected = true;
                                    if(t->direction != newState)
                                    {
                                        switchTrack(t, newState, true);
                                    }
                                }
                            }
                        }
                    }
                }

                pathFound = millis();
            } else {
                if(millis() - pathFound > 2000)
                {
                    int trackCount = (sizeof(tracks) / sizeof(tracks[0]));
                    for(int i = 0; i < trackCount; i++)
                    {
                        Track *t = &tracks[i];
                        if(t->isTrack1Selected)
                        {
                            t->isTrack1Selected = false;
                            t->isUpdated = true;
                        }
                        if(t->isTrack2Selected)
                        {
                            t->isTrack2Selected = false;
                            t->isUpdated = true;
                        }
                    }
                    
                    progState = ProgState::Normal;
                    firstTrack = -1;
                    lastTrack = -1;
                    pathFound = -1;
                }
            }

            break;
        }
    }
}
