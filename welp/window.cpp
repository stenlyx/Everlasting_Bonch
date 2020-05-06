#include "window.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "json.h"
#include <iostream>
#include <fstream>
#include "text.h"
/*
using json = nlohmann::json;

std::ifstream ifs("strings/ru-ru.json");
json jf = json::parse(ifs);

int p = 1;

std::string str = std::to_string(p);

std::string i = jf[str];

text.display(300, 300, Window::renderer);


using json = nlohmann::json;

std::ifstream ifs("strings/ru-ru.json");
json jf = json::parse(ifs);


int p = 1;
std::string str = std::to_string(p);
std::string i = jf[str];
*/



SDL_Renderer* Window::renderer = nullptr;

Window::Window(const std::string& title, int width, int height) :
_title(title), _width(width), _height(height)
{
	_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to initalize SDL." << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initalize STD_emage." << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to initalize STD_ttf ." << std::endl;
		return false;
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);

	if (_window == nullptr)
	{
		std::cerr << "Failed to create window." << std::endl;
		return 0;
	}

	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		std::cerr << "Failed to create renderer." << std::endl;
		return 0;
	}

	return true;
}
/*
void Window::pollEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_closed = true;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_closed = true;
				break;
			}

		default:
			break;
		}
	}
}
*/
void Window::clear() const
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//SDL_RenderClear(renderer);
}