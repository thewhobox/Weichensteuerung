#include <Arduino.h>


enum Type {
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
    WeicheR90,
    WeicheR180,
    WeicheR270,
    Kreuz = 200,
    Kreuz90
};

enum State {
    Initial,
    Untouched,
    Updated
};

struct Gleis {
	const int posX;
	const int posY;
	const byte i2c_addr;
	const byte nummer;
    const Type type;
    State state;
    bool direction;
};

struct Gleis gleise[] = {
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
        .state = State::Initial
	},
	{
        .posX = 0,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 0,
        .posY = 5,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 0,
        .posY = 6,
        .type = Type::Kurve,
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
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 1,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 2,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 3,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 5,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 6,
        .type = Type::WeicheL,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 7,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 8,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 1,
        .posY = 9,
        .type = Type::Kurve,
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
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 2,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 3,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 5,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 6,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 7,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 8,
        .type = Type::Kurve,
        .state = State::Initial
	},
	{
        .posX = 2,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 3,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 5,
        .type = Type::WeicheR,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 6,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 7,
        .type = Type::Kurve,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 8,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 3,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 4,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 4,
        .posY = 5,
        .type = Type::WeicheL90,
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
        .state = State::Initial
	},
	{
        .posX = 4,
        .posY = 8,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 4,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 5,
        .posY = 6,
        .type = Type::Kurve,
        .state = State::Initial
	},
	{
        .posX = 5,
        .posY = 7,
        .type = Type::WeicheL270,
        .state = State::Initial
	},
	{
        .posX = 5,
        .posY = 8,
        .i2c_addr = 0x30,
        .nummer = 1 << 1,
        .type = Type::Kreuz,
        .state = State::Initial
	},
	{
        .posX = 5,
        .posY = 9,
        .i2c_addr = 0x30,
        .nummer = 0 << 1,
        .type = Type::WeicheL90,
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
        .state = State::Initial
	},
	{
        .posX = 6,
        .posY = 6,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 6,
        .posY = 7,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 6,
        .posY = 8,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 6,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 7,
        .posY = 6,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 7,
        .posY = 7,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 7,
        .posY = 8,
        .type = Type::Gerade90,
        .state = State::Initial
	},
	{
        .posX = 7,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 8,
        .posY = 7,
        .type = Type::Kurve180,
        .state = State::Initial
	},
	{
        .posX = 8,
        .posY = 8,
        .type = Type::Kreuz90,
        .state = State::Initial
	},
	{
        .posX = 8,
        .posY = 9,
        .type = Type::WeicheR270,
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
        .state = State::Initial
	},
	{
        .posX = 9,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 4,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 5,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 6,
        .type = Type::WeicheL,
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 7,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 8,
        .type = Type::Kurve270,
        .state = State::Initial
	},
	{
        .posX = 10,
        .posY = 9,
        .type = Type::Gerade90,
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
        .state = State::Initial
	},
	{
        .posX = 11,
        .posY = 7,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 11,
        .posY = 8,
        .type = Type::Gerade,
        .state = State::Initial
	},
	{
        .posX = 11,
        .posY = 9,
        .type = Type::Kurve270,
        .state = State::Initial
	},
};