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
        Kreuz90,
        Kreuz180,
        Kreuz270
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
    bool isUpdated;
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
    bool isUpdated;
    bool direction;
    bool isTrack1Selected;
    bool isTrack2Selected;
};

struct Track tracks[] = {
    //---------Spalte 0
    {
        .posX = 0,
        .posY = 0,
        .type = Type::Kurve90,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 1,
        .type = Type::Gerade,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 2,
        .type = Type::Gerade,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 3,
        .type = Type::Gerade,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 4,
        .i2c_addr = 0x31,
        .nummer = 3,
        .type = Type::WeicheR,
        .track = "CX",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 5,
        .type = Type::Gerade,
        .track = "D4",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 6,
        .i2c_addr = 0x30,
        .nummer = 2,
        .type = Type::WeicheL180,
        .track = "DX",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 7,
        .type = Type::Gerade,
        .track = "D6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 8,
        .type = Type::Gerade,
        .track = "D6",
        .isUpdated = true
    },
    {
        .posX = 0,
        .posY = 9,
        .type = Type::Kurve,
        .track = "D6",
        .isUpdated = true
    },
    //---------Spalte 1
    {
        .posX = 1,
        .posY = 0,
        .type = Type::Gerade90,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 1,
        .type = Type::Kurve90,
        .track = "L6",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 2,
        .i2c_addr = 0x31,
        .nummer = 1,
        .type = Type::WeicheR,
        .track = "LX",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 3,
        .type = Type::Gerade,
        .track = "B5",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 4,
        .i2c_addr = 0x31,
        .nummer = 0,
        .type = Type::Kreuz270,
        .track = "BX",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 5,
        .type = Type::Gerade,
        .track = "E7",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 6,
        .i2c_addr = 0x30,
        .nummer = 3,
        .type = Type::Kreuz90,
        .track = "EX",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 7,
        .type = Type::Gerade,
        .track = "E5",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 8,
        .type = Type::Kurve,
        .track = "E5",
        .isUpdated = true
    },
    {
        .posX = 1,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 2
    {
        .posX = 2,
        .posY = 0,
        .type = Type::Gerade90,
        .track = "C6",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 1,
        .type = Type::Gerade90,
        .track = "L6",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 2,
        .type = Type::Gerade90,
        .track = "L7",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 3,
        .type = Type::Kurve90,
        .track = "A4",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 4,
        .type = Type::WeicheR180,
        .track = "AX",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 5,
        .type = Type::Gerade,
        .track = "F6",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 6,
        .i2c_addr = 0x30,
        .nummer = 0,
        .type = Type::WeicheL,
        .track = "FX",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 7,
        .type = Type::Kurve,
        .track = "F4",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H5",
        .isUpdated = true
    },
    {
        .posX = 2,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 3
    {
        .posX = 3,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 1,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {  
        .posX = 3,
        .posY = 2,
        .type = Type::WeicheR90,
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 3,
        .type = Type::Tunnel90,
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 4,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 5,
        .type = Type::Kurve,
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 6,
        .type = Type::Leer,
    },
    {
        .posX = 3,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "G4",
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H5",
        .isUpdated = true
    },
    {
        .posX = 3,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 4
    {
        .posX = 4,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 1,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 2,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 3,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 4,
        .type = Type::Leer
    },
    {
        .posX = 4,
        .posY = 5,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 6,
        .type = Type::Leer,
    },
    {
        .posX = 4,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "G4",
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H5",
        .isUpdated = true
    },
    {
        .posX = 4,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 5
    {
        .posX = 5,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 1,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 2,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 3,
        .type = Type::Tunnel90,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 4,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 5,
        .type = Type::Kurve270,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 6,
        .type = Type::Leer,
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "G4",
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H5",
        .isUpdated = true
    },
    {
        .posX = 5,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 6
    {
        .posX = 6,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 1,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 2,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 3,
        .type = Type::Tunnel90,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 4,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 5,
        .type = Type::Kurve,
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 6,
        .type = Type::Leer
    },
    {
        .posX = 6,
        .posY = 7,
        .type = Type::Gerade90,
        .track = "G4",
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H5",
        .isUpdated = true
    },
    {
        .posX = 6,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I6",
        .isUpdated = true
    },
    //---------Spalte 7
    {
        .posX = 7,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 1,
        .type = Type::Kurve90,
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 2,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 3,
        .type = Type::Kurve270,
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 4,
        .type = Type::Leer
    },
    {
        .posX = 7,
        .posY = 5,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 6,
        .type = Type::Leer
    },
    {
        .posX = 7,
        .posY = 7,
        .i2c_addr = 0x32,
        .nummer = 3,
        .type = Type::WeicheR90,
        .track = "GX",
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 8,
        .i2c_addr = 0x32,
        .nummer = 2,
        .type = Type::Kreuz90,
        .track = "HX",
        .isUpdated = true
    },
    {
        .posX = 7,
        .posY = 9,
        .i2c_addr = 0x32,
        .nummer = 0,
        .type = Type::WeicheR270,
        .track = "IX",
        .isUpdated = true
    },
    //---------Spalte 8
    {
        .posX = 8,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 1,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 2,
        .type = Type::Kurve90,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 3,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 4,
        .type = Type::Kurve,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 5,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 6,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 7,
        .type = Type::WeicheL90,
        .track = "JX",
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H7",
        .isUpdated = true
    },
    {
        .posX = 8,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I4",
        .isUpdated = true
    },
    //---------Spalte 9
    {
        .posX = 9,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 1,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 2,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 3,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 4,
        .type = Type::WeicheL,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 5,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 6,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 7,
        .type = Type::Kurve270,
        .track = "J6",
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 8,
        .type = Type::Gerade90,
        .track = "H7",
        .isUpdated = true
    },
    {
        .posX = 9,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I4",
        .isUpdated = true
    },
    //---------Spalte 10
    {
        .posX = 10,
        .posY = 0,
        .type = Type::Gerade90,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 1,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 2,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 3,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 4,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 5,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 6,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 7,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 8,
        .type = Type::Kurve270,
        .track = "H7",
        .isUpdated = true
    },
    {
        .posX = 10,
        .posY = 9,
        .type = Type::Gerade90,
        .track = "I4",
        .isUpdated = true
    },
    //---------Spalte 11
    {
        .posX = 11,
        .posY = 0,
        .type = Type::Kurve180,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 1,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 2,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 3,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 4,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 5,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 6,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 7,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 8,
        .type = Type::Gerade,
        .isUpdated = true
    },
    {
        .posX = 11,
        .posY = 9,
        .type = Type::Kurve270,
        .track = "I4",
        .isUpdated = true
    },
};