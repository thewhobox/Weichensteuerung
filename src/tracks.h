#include <Arduino.h>

enum Type
{
        Leer,
        Gerade,
        Gerade90,
        Tunnel,
        Tunnel90,
        Kurve,
        Kurve90,
        Kurve180,
        Kurve270,
        WeicheL = 100,
        WeicheL90,
        WeicheL180,
        WeicheL270,
        WeicheR,
        WeicheR45,
        WeicheR90,
        WeicheR180,
        WeicheR270,
        Kreuz = 200,
        Kreuz90
};

enum State
{
        Initial,
        Untouched,
        Updated
};

enum Selection
{
    NotSelected,
    Selected,
    Selected2
};

enum Position
{
    NO,
    OS,
    SW,
    WN
};

struct Signal
{
    const int posX;
    const int posY;
    const byte i2c_addr;
    const byte nummer;
    bool lightState;
    State state;
    Position position;
};

struct Signal signals[] = {
    {
        .posX = 6,
        .posY = 7,
        .i2c_addr = 0x32,
        .nummer = 0 << 1,
        .position = Position::WN
    },
    {
        .posX = 6,
        .posY = 8,
        .i2c_addr = 0x32,
        .nummer = 1 << 1,
        .position = Position::WN
    }, {
        .posX = 6,
        .posY = 9,
        .i2c_addr = 0x32,
        .nummer = 2 << 1,
        .position = Position::WN
    }
};

struct Track
{
    const int posX;
    const int posY;
    const byte i2c_addr;
    const byte nummer;
    const Type type;
    const char track[3];
    const char track2[3];
    State state;
    bool direction;
    Selection isSelected;
};

struct Track tracks[] = {
    //---------Spalte 0
    {
        .posX = 0,
        .posY = 0,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 1,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 2,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 3,
        .type = Type::Gerade,
        .track = "A2",
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 4,
        .type = Type::Gerade,
        .track = "A2",
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 5,
        .type = Type::Gerade,
        .track = "A2",
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 6,
        .type = Type::Kurve,
        .track = "A2",
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 7,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 8,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 0,
        .posY = 9,
        .type = Type::Leer,
        .state = State::Initial
    },
    //---------Spalte 1
    {
        .posX = 1,
        .posY = 0,
        .type = Type::Kurve90,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 1,
        .type = Type::Gerade,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 2,
        .type = Type::Gerade,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 3,
        .type = Type::Gerade,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 4,
        .type = Type::Gerade,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 5,
        .type = Type::Gerade,
        .track = "A1",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 6,
        .type = Type::WeicheL,
        .track = "AX",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 7,
        .type = Type::Gerade,
        .track = "A0",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 8,
        .type = Type::Gerade,
        .track = "A0",
        .state = State::Initial
    },
    {
        .posX = 1,
        .posY = 9,
        .type = Type::Kurve,
        .track = "A0",
        .state = State::Initial
    },
    //---------Spalte 2
    {
        .posX = 2,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 1,
        .type = Type::Kurve90,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 2,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 3,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 4,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 5,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 6,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 7,
        .type = Type::Gerade,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 8,
        .type = Type::Kurve,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 2,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "B0",
        .state = State::Initial
    },
    //---------Spalte 3
    {
        .posX = 3,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {  
        .posX = 3,
        .posY = 2,
        .type = Type::Kurve90,
        .track = "H1",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 3,
        .type = Type::Gerade,
        .track = "H1",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 4,
        .type = Type::Gerade,
        .track = "H1",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 5,
        .type = Type::WeicheR,
        .track = "HX",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 6,
        .type = Type::Gerade,
        .track = "H0",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 7,
        .type = Type::Kurve,
        .track = "H0",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 3,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "B0",
        .state = State::Initial
    },
    //---------Spalte 4
    {
        .posX = 4,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 2,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 3,
        .type = Type::Kurve90,
        .track = "I1",
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 4,
        .type = Type::Gerade,
        .track = "I1",
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 5,
        .type = Type::WeicheR45,
        .track = "IX",
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 6,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "F1",
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "E3",
        .state = State::Initial
    },
    {
        .posX = 4,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "B0",
        .state = State::Initial
    },
    //---------Spalte 5
    {
        .posX = 5,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 2,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 3,
        .type = Type::Gerade90,
        .track = "I1",
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 4,
        .type = Type::Kurve90,
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 5,
        .type = Type::Tunnel,
        .track = "G2",
        .track2 = "I2",
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 6,
        .type = Type::Kurve,
        .track = "G2",
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 7,
        .type = Type::WeicheL270,
        .track = "FX",
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 8,
        .i2c_addr = 0x31,
        .nummer = 1 << 1,
        .type = Type::Kreuz,
        .track = "EX",
        .state = State::Initial
    },
    {
        .posX = 5,
        .posY = 9,
        .i2c_addr = 0x31,
        .nummer = 0 << 1,
        .type = Type::WeicheL90,
        .track = "BX",
        .state = State::Initial
    },
    //---------Spalte 6
    {
        .posX = 6,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 2,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 3,
        .type = Type::Gerade90,
        .track = "Y1",
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 4,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 5,
        .type = Type::Gerade90,
        .track = "I2",
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 6,
        .type = Type::Gerade90,
        .track = "G2",
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "F0",
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "E5",
        .state = State::Initial
    },
    {
        .posX = 6,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "B1",
        .state = State::Initial
    },
    //---------Spalte 7
    {
        .posX = 7,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 2,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 3,
        .type = Type::Kurve180,
        .track = "Y1",
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 4,
        .type = Type::Tunnel90,
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 5,
        .type = Type::Kurve270,
        .track = "I2",
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 6,
        .type = Type::Gerade90,
        .track = "G2",
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "D8",
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "D5",
        .state = State::Initial
    },
    {
        .posX = 7,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "C1",
        .state = State::Initial
    },
    //---------Spalte 8
    {
        .posX = 8,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 1,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 2,
        .type = Type::Kurve180,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 3,
        .type = Type::Kurve,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 4,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 5,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 6,
        .type = Type::Gerade90,
        .track = "G2",
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 7,
        .type = Type::Kurve180,
        .track = "D8",
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 8,
        .i2c_addr = 0x30,
        .nummer = 1 << 1,
        .type = Type::Kreuz90,
        .track = "DX",
        .state = State::Initial
    },
    {
        .posX = 8,
        .posY = 9,
        .i2c_addr = 0x30,
        .nummer = 0 << 1,
        .type = Type::WeicheR270,
        .track = "CX",
        .state = State::Initial
    },
    //---------Spalte 9
    {
        .posX = 9,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 1,
        .type = Type::Kurve180,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 2,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 3,
        .type = Type::Tunnel,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 4,
        .type = Type::Kurve270,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 5,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 6,
        .type = Type::Gerade90,
        .track = "G2",
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 7,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "D3",
        .state = State::Initial
    },
    {
        .posX = 9,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "C0",
        .state = State::Initial
    },
    //---------Spalte 10
    {
        .posX = 10,
        .posY = 0,
        .type = Type::Gerade90,
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 1,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 2,
        .type = Type::Leer,
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 3,
        .type = Type::Kurve180,
        .track = "G1",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 4,
        .type = Type::Gerade,
        .track = "G1",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 5,
        .type = Type::Gerade,
        .track = "G1",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 6,
        .type = Type::WeicheL,
        .track = "GX",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 7,
        .type = Type::Gerade,
        .track = "G0",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 8,
        .type = Type::Kurve270,
        .track = "D3",
        .state = State::Initial
    },
    {
        .posX = 10,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "C0",
        .state = State::Initial
    },
    //---------Spalte 11
    {
        .posX = 11,
        .posY = 0,
        .type = Type::Kurve180,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 1,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 2,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 3,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 5,
        .type = Type::Gerade,
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 6,
        .type = Type::Gerade,
        .track = "C0",
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 7,
        .type = Type::Gerade,
        .track = "C0",
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 8,
        .type = Type::Gerade,
        .track = "C0",
        .state = State::Initial
    },
    {
        .posX = 11,
        .posY = 9,
        .type = Type::Kurve270,
        .track = "C0",
        .state = State::Initial
    },
};