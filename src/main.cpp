#include <Arduino.h>
#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)
#include <Wire.h>
#include "gleise.h"
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
uint32_t colorSelected = TFT_ORANGE;
uint32_t colorMenu = TFT_BLACK;
uint32_t colorMenuSelected = TFT_ORANGE;
uint32_t colorMenuLine = TFT_DARKGREEN;



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
                tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);

                int x1 = g->posX * 24;
                int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int x2 = (g->posX * 24) + 7;
                tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
                
                x1 = g->posX * 24 + 16;
                y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                x2 = (g->posX * 24) + 23;
                tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
                
                int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                int y1 = g->posY * 24;
                int y2 = (g->posY * 24) + 7;
                tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);
                
                x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                y1 = g->posY * 24 + 16;
                y2 = (g->posY * 24) + 23;
                tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
                    int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
        	        int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);

                    x1 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y1 = (g->posY * 24) + 23;
                    x2 = (g->posX * 24) + 23;
                    y2 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);

                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
                    
                    x1 = g->posX * 24 + 16;
                    y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
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
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);

                    x1 = g->posX * 24;
                    y1 = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    y2 = (g->posY * 24) + 23;
                    tft.drawLine(x1, y1, x2, y2, g->isSelected ? colorSelected : colorTrack);
                } else {
        	        int x = (g->posX * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int y1 = g->posY * 24;
                    int y2 = (g->posY * 24) + 23;
                    tft.drawLine(x, y1, x, y2, g->isSelected ? colorSelected : colorTrack);

                    int x1 = g->posX * 24;
                    int y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    int x2 = (g->posX * 24) + 7;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
                    
                    x1 = g->posX * 24 + 16;
                    y = (g->posY * 24) + 11 - ((lineThickness - 2) / 2) + i;
                    x2 = (g->posX * 24) + 23;
                    tft.drawLine(x1, y, x2, y, g->isSelected ? colorSelected : colorTrack);
                }
            }
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

void normalLoop()
{
    int gleisCount = (sizeof(gleise) / sizeof(gleise[0]));
    for(int i = 0; i < gleisCount; i++)
    {
        handleGleis(&gleise[i]);
    }

    
    int menuCount = (sizeof(MenuItems) / sizeof(MenuItems[0]));
    for(int i = 0; i < menuCount; i++)
    {
        handleMenu(&MenuItems[i], i);
    }

    uint16_t touchX;
    uint16_t touchY;
    if(millis() - lastTouch > 200 && getTouch(&touchX, &touchY))
    {
        lastTouch = millis();
        Serial.print("TouchX ");
        Serial.println(touchX);

        if(touchX > 287) //its Menu
        {
            int rest = touchY % 32;
            int index = (touchY - rest) / 32;
            Serial.print("Index: ");
            Serial.println(index);
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

            Gleis *gleis = &gleise[counter];
            int type = gleis->type;

            if(type > 99) //Nur wenn Type eine Weiche ist (struct > 99)
            {
                Serial.println("Weiche umgestellt");
                gleis->direction = !gleis->direction;
                gleis->state = State::Updated;                
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
            } else if(gleis->type != Type::Leer && MenuItems[0].isSelected) {
                if(gleis->isSelected)
                {
                    gleis->isSelected = false;
                    gleis->state = State::Updated;
                    firstTrack = -1;
                } else {
                    gleis->isSelected = true;
                    gleis->state = State::Updated;
                    if(firstTrack == -1)
                    {
                        firstTrack = counter;
                        Serial.println("First Track Selected");
                    } else {
                        lastTrack = counter;
                        drawGleis(gleis);
                        progState = ProgState::PathFinding;
                        Serial.println("Mache jetzt PathFinding");
                    }
                }
            }
        }
    }
}

void addTrackSwitch(char name){
    Serial.print("Creating TrackSwitch ");
    Serial.println(name);
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
    Serial.print("Creating TrackSwitch Cross ");
    Serial.println(name);
    char buffer[3];
    buffer[0] = name;
    buffer[1] = '3';
    buffer[2] = '\0';
    place *p3 = place_new(buffer);
    buffer[1] = '4';
    place *p4 = place_new(buffer);
    buffer[1] = '5';
    place *p5 = place_new(buffer);
    buffer[1] = '6';
    place *p6 = place_new(buffer);

    place_add_way(p3, p5, 0);
    place_add_way(p5, p3, 0);
    place_add_way(p3, p6, 0);
    place_add_way(p6, p3, 0);
    
    place_add_way(p4, p6, 0);
    place_add_way(p6, p4, 0);
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
    Serial.println("initPath");
    addTrackSwitch('A');
    addTrackSwitch('B');
    addTrackSwitch('C');
    addTrackSwitchCross('D');
    addTrackSwitchCross('E');
    addTrackSwitch('F');
    addTrackSwitch('G');
    Serial.println("created all");


    connectTracks("A0", "B0", 5); //x1
    connectTracks("B1", "C1", 5); //x2
    connectTracks("B2", "E4", 1); //x3
    connectTracks("E5", "D5", 5); //x4
    connectTracks("D4", "C2", 1); //x5
    connectTracks("E6", "F2", 1); //x6
    connectTracks("F0", "D6", 5); //x7
    connectTracks("D3", "G0", 5); //x8

    place_dump(place_get("B1"));
    place_dump(place_get("C1"));
}

int pathFound = -1;

void loop()
{
    // put your main code here, to run repeatedly:
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
            if(pathFound == -1)
            {
                Gleis gleis1 = gleise[firstTrack];
                Gleis gleis2 = gleise[lastTrack];

                Serial.print("Start: ");
                Serial.println(gleis1.track);
                Serial.print("Stop: ");
                Serial.println(gleis2.track);

                char route[100];
                int length = place_get_route(gleis1.track, gleis2.track, route);
                Serial.print("Route (");
                Serial.print(length);
                Serial.print(") -> ");
                Serial.println(route);

                char needle[5];
                int gleisCount = (sizeof(gleise) / sizeof(gleise[0]));
                for(int i = 0; i < gleisCount; i++)
                {
                    Gleis *gleis = &gleise[i];


                    if(gleis->type < 100)
                    {
                        sprintf(needle, "%s", gleis->track);

                        if(strlen(gleis->track) > 1 && strstr(route, needle) != NULL)
                        {
                            gleis->isSelected = true;
                            gleis->state = State::Updated;
                            drawGleis(gleis);
                        }
                    } else {
                        needle[0] = gleis->track[0];
                        needle[1] = '\0';
                        char *heuhaufen = route;
                        int counter = 0;
                        
                        while(true)
                        {
                            char *fund = strstr(heuhaufen, needle);
                            if(fund == NULL) break;

                            Serial.print("Found TrackSwitch ");
                            Serial.print(gleis->track[0]);
                            Serial.print(" at: ");
                            Serial.println(fund[1]);
                            heuhaufen = fund + 2;
                            counter += fund[1] - 48;
                        }

                        if(counter > 0)
                        {
                            if(gleis->type >= 200)
                            {

                            } else {
                                gleis->isSelected = true;
                                gleis->direction = counter != 1;
                                gleis->state = State::Updated;
                                drawGleis(gleis);
                            }
                        }
                        
                        Serial.print("Found ");
                        Serial.print(counter);
                        Serial.println(" times");
                    }

                }

                pathFound = millis();
            } else {
                if(millis() - pathFound > 15000)
                {
                    int gleisCount = (sizeof(gleise) / sizeof(gleise[0]));
                    for(int i = 0; i < gleisCount; i++)
                    {
                        Gleis *gleis = &gleise[i];
                        if(gleis->isSelected)
                        {
                            gleis->isSelected = false;
                            gleis->state = State::Updated;
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
