#include <Arduino.h>
#include <PCF8574.h>
#include <Wire.h>

struct weiche
{
	const int index;
	const byte i2c_addr;
	const byte nummer;
	const int button;
	const bool isExtern;
	bool state;
};

struct weiche addresses[] = {
	{
		.index = 1,
		.i2c_addr = 0x30,
		.nummer = 0 << 1,
		.button = D0,
		.isExtern = false,
	},
	{
		.index = 2,
		.i2c_addr = 0x30,
		.nummer = 1 << 1,
		.button = D3,
		.isExtern = false,
	}};

const int buttonCount = 2;
PCF8574 pcf(0x20);

void setup()
{
	Wire.begin(); //D2, D1);
	Serial.begin(9600);
	delay(3000);
	Serial.print("Bereit");

	pcf.write(0, LOW);
	pcf.write(1, LOW);
	pcf.write(2, LOW);
	pcf.write(3, HIGH);
	//bool x = pcf.read(2);

	for (int i = 0; i < buttonCount; i++)
	{
		if (!addresses[i].isExtern)
			pinMode(addresses[i].button, INPUT);
	}
}

bool state_changed(struct weiche *w)
{
	bool state;
	if (w->isExtern)
		state = pcf.read(w->button);
	else
		state = digitalRead(w->button);

	if (state != w->state)
	{
		w->state = state;
		return true;
	}
	return false;
}

void send_state_update(struct weiche *w)
{
	Serial.print("Button ");
	Serial.print(w->index);
	Serial.print(" state is ");
	Serial.println(w->state ? "on" : "off");

	Serial.printf("Write to %2X\n", w->i2c_addr);
	Wire.beginTransmission(w->i2c_addr);
	byte data = w->nummer; //(addresses[i] & 0b1111) << 1;
	data = data | w->state;
	Serial.print("Data ");
	Serial.print(data, HEX);
	Serial.println();
	Wire.write(data);
	Wire.endTransmission();
	delay(200);
}

void loop()
{
	for (int i = 0; i < buttonCount; i++)
	{
		if (state_changed(&addresses[i]))
		{
			send_state_update(&addresses[i]);
		}
	}
}
