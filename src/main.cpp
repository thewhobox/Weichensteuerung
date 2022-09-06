#include <Arduino.h>
#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)
#include <Wire.h>
#include "tracks.h"
#include "place.h"
#include "icon_manual.h"

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
    Manual
};

struct MenuItem {
    State state;
    bool isSelected;
    const Icons icon;
};

struct MenuItem MenuItems[] = {
    {
        .state = State::Initial,
        .isSelected = true,
        .icon = Icons::Manual
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
}


int lineThickness = 2;
uint32_t colorTrack = TFT_BLACK;
uint32_t colorSelected = TFT_GREEN; //TFT_ORANGE;
uint32_t colorMenu = TFT_BLACK;
uint32_t colorMenuSelected = TFT_ORANGE;
uint32_t colorMenuLine = TFT_DARKGREEN;

void drawTrack(Track *t)
{
    switch(t->type)
    {
        case Type::Gerade:
        {
            for(int i = 0; i < lineThickness; i ++)
            {
                int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);

                int x1 = t->posX * 24;
                int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (t->posX * 24) + 7;
                tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                
                x1 = t->posX * 24 + 16;
                y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                x2 = (t->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                
                int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = t->posY * 24;
                int y2 = (t->posY * 24) + 7;
                tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                
                x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                y1 = t->posY * 24 + 16;
                y2 = (t->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
                    int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                }
            }
            break;
        }

        case Type::WeicheL180:
            Serial.println("WeicheL180 wird noch nicht unterstützt");
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                }
            }
            break;
        }

        case Type::WeicheR90:
            Serial.println("WeicheR90 wird noch nicht unterstützt");
            break;

        case Type::WeicheR180:
            Serial.println("WeicheR180 wird noch nicht unterstützt");
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                } else {
        	        int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected ? colorSelected : colorTrack);
                }
            }
            break;
        }
        
        case Type::Kreuz:
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);

                    x1 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y1 = (t->posY * 24) + 23;
                    x2 = (t->posX * 24) + 23;
                    y2 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);

                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                    
                    x1 = t->posX * 24 + 16;
                    y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);

                    x1 = t->posX * 24;
                    y1 = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y2 = (t->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                } else {
        	        int x = (t->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = t->posY * 24;
                    int y2 = (t->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, t->isSelected == Selection::Selected ? colorSelected : colorTrack);

                    int x1 = t->posX * 24;
                    int y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (t->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                    
                    x1 = t->posX * 24 + 16;
                    y = (t->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (t->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, t->isSelected == Selection::Selected2 ? colorSelected : colorTrack);
                }
            }
            break;
        }
    }
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
    }
}

void handleTrack(Track *t)
{
    switch(t->state)
    {
        case State::Initial:
        case State::Updated:
        {
           drawTrack(t);
           t->state = State::Untouched;
           break;
        }

        case State::Untouched:
            break;
    }
}

void handleSignal(Signal *s)
{
    switch(s->state)
    {
        case State::Initial:
        case State::Updated:
        {
           drawSignal(s);
           s->state = State::Untouched;
           break;
        }

        case State::Untouched:
            break;
    }
}

void handleMenu(MenuItem *m, int index)
{
    switch(m->state)
    {
        case State::Initial:
        case State::Updated:
        {
           drawMenuItem(m, index);
           m->state = State::Untouched;
           break;
        }

        case State::Untouched:
            break;
    }
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
    t->state = State::Updated;      

    Serial.print("state is ");
    Serial.println(t->direction ? "on" : "off");

    Serial.printf("Write to %2X\n", t->i2c_addr);
    byte data = t->nummer; //(addresses[i] & 0b1111) << 1;
    data = data | t->direction;
    Serial.print("Data ");
    Serial.print(data, HEX);
    Serial.println();
    Wire.beginTransmission(t->i2c_addr);
    Wire.write(data);
    Wire.endTransmission();

    if(wait) delay(100);
}

void doTracks()
{
    int TrackCount = (sizeof(tracks) / sizeof(tracks[0]));
    for(int i = 0; i < TrackCount; i++)
    {
        handleTrack(&tracks[i]);
    }
}

void doSignals()
{
    int SignalCount = (sizeof(signals) / sizeof(signals[0]));
    for(int i = 0; i < SignalCount; i++)
    {
        handleSignal(&signals[i]);
    }
}

void doMenu()
{
    int menuCount = (sizeof(MenuItems) / sizeof(MenuItems[0]));
    for(int i = 0; i < menuCount; i++)
    {
        handleMenu(&MenuItems[i], i);
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
            item->state = State::Updated;
        } else { //its track
            int rest = touchX % 24;
            int col = (touchX - rest) / 24;
            rest = touchY % 24;
            int row = (touchY - rest) / 24;
            int counter = col * 10 + row;

            Track *t = &tracks[counter];
            int type = t->type;

            if(type > 99) //Nur wenn Type eine Weiche ist (struct > 99)
            {
                switchTrack(t, !t->direction, true);
            } else if(t->type != Type::Leer && MenuItems[0].isSelected) {
                if(t->isSelected == Selection::Selected)
                {
                    t->isSelected = Selection::NotSelected;
                    t->state = State::Updated;
                    firstTrack = -1;
                } else {
                    t->isSelected = Selection::Selected;
                    t->state = State::Updated;
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
    buffer[1] = '0';
    buffer[2] = '\0';
    place *p1 = place_new(buffer);
    buffer[1] = '1';
    place *p2 = place_new(buffer);
    buffer[1] = '2';
    place *p3 = place_new(buffer);

    place_add_way(p1, p2, 0);
    place_add_way(p2, p1, 0);
    place_add_way(p1, p3, 0);
    place_add_way(p3, p1, 0);
}

void addTrackSwitchCross(char name)
{
    char buffer[3];
    buffer[0] = name;
    buffer[1] = '3';
    buffer[2] = '\0';
    place *p3 = place_new(buffer);
    buffer[1] = '4';
    place *p4 = place_new(buffer);
    buffer[1] = '5';
    place *p5 = place_new(buffer);
    buffer[1] = '8';
    place *p8 = place_new(buffer);

    place_add_way(p3, p5, 0);
    place_add_way(p5, p3, 0);
    place_add_way(p3, p8, 0);
    place_add_way(p8, p3, 0);
    
    place_add_way(p4, p8, 0);
    place_add_way(p8, p4, 0);
    place_add_way(p4, p5, 0);
    place_add_way(p5, p4, 0);
}

void connectTracks(char *start, char *end, int distance)
{
    place *p1 = place_get(start);
    place *p2 = place_get(end);
    place_add_way(p1, p2, distance);
    place_add_way(p2, p1, distance);
}

void initPath() {
    addTrackSwitch('A');
    addTrackSwitch('B');
    addTrackSwitch('C');
    addTrackSwitchCross('D');
    addTrackSwitchCross('E');
    addTrackSwitch('F');
    addTrackSwitch('G');
    addTrackSwitch('H');
    addTrackSwitch('I');
    //standalone places
    place_new("Y1");


    connectTracks("A0", "B0", 5); //x1
    connectTracks("B1", "C1", 5); //x2
    connectTracks("B2", "E4", 1); //x3
    connectTracks("E5", "D5", 5); //x4
    connectTracks("D4", "C2", 1); //x5
    connectTracks("E8", "F2", 1); //x6
    connectTracks("F0", "D8", 5); //x7
    connectTracks("D3", "G0", 5); //x8
    connectTracks("H0", "F1", 5); //x9
    connectTracks("H2", "I0", 5); //x10
    //standalone ways
    connectTracks("Y1", "I1", 5); //x11
    connectTracks("Y1", "I2", 5); //x12

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

                Serial.print("Start: ");
                Serial.println(track1.track);
                Serial.print("Stop: ");
                Serial.println(track2.track);

                char route[100];
                int sw = millis();
                int length = place_get_route(track1.track, track2.track, route);
                int sw2 = millis() - sw;
                Serial.print("Took: ");
                Serial.print(sw2);
                Serial.println(" ms");
                Serial.print("Route (");
                Serial.print(length);
                Serial.print(") -> ");
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
                            t->isSelected = Selection::Selected;
                            t->state = State::Updated;
                        }
                        if(t->type == Type::Tunnel || t->type == Type::Tunnel90)
                        {
                            sprintf(needle, "%s", t->track2);

                            if(strlen(t->track2) > 1 && strstr(route, needle) != NULL)
                            {
                                t->isSelected = Selection::Selected2;
                                t->state = State::Updated;
                            }
                        }
                    } else {
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

                        if(counter > 0)
                        {
                            if(t->type >= 200)
                            {
                                if(counter == 11 || counter == 12)
                                    t->isSelected = Selection::Selected;
                                else
                                    t->isSelected = Selection::Selected2;

                                bool newState = counter % 2 != 0;
                                if(t->direction != newState)
                                {
                                    switchTrack(t, newState, true);
                                }
                            } else {
                                t->isSelected = Selection::Selected;
                                bool newState = counter != 1;
                                if(t->direction != newState)
                                {
                                    switchTrack(t, newState, true);
                                }
                            }
                        }
                    }
                }

                pathFound = millis();
            } else {
                if(millis() - pathFound > 5000)
                {
                    int trackCount = (sizeof(tracks) / sizeof(tracks[0]));
                    for(int i = 0; i < trackCount; i++)
                    {
                        Track *t = &tracks[i];
                        if(t->isSelected)
                        {
                            t->isSelected = Selection::NotSelected;
                            t->state = State::Updated;
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
