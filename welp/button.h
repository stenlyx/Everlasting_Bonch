#pragma once
#include <SDL.h>
#include <string>
#include "window.h"

class Button
{
public:
	Button(int x, int y, int w, int h, int r, int g, int b, int a);

	void draw() const;
	bool CheckEvents(bool leftMousePressed);

private:
	int _x, _y;
	int _w, _h;
	int _r, _g, _b, _a;
	int MouseX, MouseY;
};