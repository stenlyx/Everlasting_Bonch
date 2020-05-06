#include "window.h"
#include "text.h"
#include "json.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include<sstream> 
#include<string>

using json = nlohmann::json;

std::ifstream ifs("strings/ru-ru.json");
json jf = json::parse(ifs);
int p = 1;



SDL_Event event;

int main(int argc, char** argv)
{
	Window window("Endless Bonch", 1280, 720);

	while (!window.isClosed())
	{
		//window.pollEvents();
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (p != 11)
					{
						SDL_RenderClear(Window::renderer);
						std::string str = std::to_string(p);
						std::string i = jf[str];
						Text text(Window::renderer, "assets/arial.ttf", 25, i, { 255, 255, 255, 255 });
						text.display(0, 300, Window::renderer);
						p++;
						std::cout << p << std::endl;
						break;
					}
					else
						break;
				}
			case SDL_MOUSEBUTTONDOWN:
				if (p != 11)
				{
					SDL_RenderClear(Window::renderer);
					std::string str = std::to_string(p);
					std::string i = jf[str];
					Text text(Window::renderer, "assets/arial.ttf", 25, i, { 255, 255, 255, 255 });
					text.display(0, 300, Window::renderer);
					p++;
					std::cout << p << std::endl;
					break;
				}
				else
					break;
			default:
				break;
			}
		}
		window.clear();
	}

	return 0;
}