#include "button.h"
#include "SDL.h"
#include <string>

Button::Button(int x, int y, int w, int h, int r, int g, int b, int a) :
	MouseX(0), MouseY(0), _w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{
}
void Button::draw() const
{
	SDL_Rect rect = {_x, _y, _w, _h};

	SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(Window::renderer, &rect);
}

bool Button::CheckEvents(bool leftMousePressed) {
	if (leftMousePressed)
	{
		if ((MouseX > _x) && (MouseY > _y) && (MouseX < (_x + _w)) && (MouseY < (_y + _h))) {
			return true;
		}
	}
}