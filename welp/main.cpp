#include "window.h"
#include "text.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include<sstream> 
#include<string>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include "rapidjson/stringbuffer.h"
#include <cstdio>
#include <windows.h>
#include <unordered_map>

using namespace rapidjson;

SDL_Event event;

int main(int argc, char** argv)
{
	int p = 1;

	std::unordered_map<std::string, std::string> mText;

	auto fileName = "strings/ru-ru.gptext";

	std::ifstream file(fileName);
	// Read the entire file to a string stream
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	// Open this file in rapidJSON
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	const rapidjson::Value& actions = doc;
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			mText.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}

	Window window("Endless Bonch", 1280, 720);
	while (!window.isClosed())
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (p != 5)
					{
						SDL_RenderClear(Window::renderer);
						std::string str = std::to_string(p);
						Text text(Window::renderer, u8"assets/times.ttf", 30, mText[str], { 255, 255, 255, 255 });
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
					Text text(Window::renderer, u8"assets/times.ttf", 30, mText[str], { 255, 255, 255, 255 });
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
		window.pollEvents();
		window.clear();
	}
	return 0;
}