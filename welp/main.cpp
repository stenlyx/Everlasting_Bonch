#include "window.h"
#include "text.h"
#include <iostream>
#include <fstream>
#include<sstream> 
#include<string>
#include "rapidjson/document.h"
#include <windows.h>
#include <unordered_map>
#include "SDL_mixer.h"

using namespace rapidjson;

SDL_Event event;

std::unordered_map<std::string, std::string> mText;

void rjson(const std::string fileName)
{
	// Clear the existing map, if already loaded
	mText.clear();
	// Try to open the file
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	// Read the entire file to a string stream
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	// Open this file in rapidJSON
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	// Parse the text map
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
}

const std::string GetText(const std::string key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = mText.find(key);
	if (iter != mText.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

void display_text(int p)
{
	SDL_RenderClear(Window::renderer);
	std::string str = std::to_string(p);
	Text text(Window::renderer, u8"assets/times.ttf", 25, GetText(str), { 255, 255, 255, 255 });
	text.display(40, 450, Window::renderer);
}

void display_buttons(int amount, std::string b1, std::string b2, std::string b3 = "")
{
	if (amount == 2)
	{
		SDL_RenderClear(Window::renderer);
		Text text1(Window::renderer, u8"assets/times.ttf", 30, b1, { 255, 0, 0, 0 });
		Text text2(Window::renderer, u8"assets/times.ttf", 30, b2, { 0, 255, 0, 0 });
		text1.display(40, 450, Window::renderer);
		text2.display(40, 480, Window::renderer);
	}
	if (amount == 3)
	{
		SDL_RenderClear(Window::renderer);
		Text text1(Window::renderer, u8"assets/times.ttf", 30, b1, { 255, 0, 0, 0 });
		Text text2(Window::renderer, u8"assets/times.ttf", 30, b2, { 0, 255, 0, 0 });
		Text text3(Window::renderer, u8"assets/times.ttf", 30, b3, { 0, 0, 255, 0 });
		text1.display(40, 450, Window::renderer);
		text2.display(40, 480, Window::renderer);
		text3.display(40, 510, Window::renderer);
	}
}

int main(int argc, char** argv)
{
	std::ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();

	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music* background = Mix_LoadMUS("assets/hornet_theme.mp3");

	int a = 1;
	bool leftClick = false;
	bool goNext = false;
	bool run = false;
	bool grave = false;

	Window window("Endless Bonch", 1280, 720);
	rjson("strings/intro.gptext");
/*
	mText.clear();
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
*/
	Mix_PlayMusic(background, -1);
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
					if (a < 7)
					{
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					if (a == 7) { rjson("strings/beginning1.gptext"), a++; }
					if (a < 13)
					{
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					if (a == 13) 
					{
						display_buttons(3, u8"1.Без моих идей, невежа, ты б и шагу не шагнул!",
							u8"2.Сейчас вцеплюсь тебе я в горло и на части разорву!",
							u8"3.Отдадим чертову монету покойнику!");

					}
					if (a < 20 && goNext)
					{
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					if (a == 20)
					{
						goNext = false;
						display_buttons(2, u8"1.Бежать куда глаза глядят", u8"2.Спрятаться на кладбище");
					}
					if (a < 32 && goNext && run)
					{

						if (a == 23)
						{
							display_buttons(2, u8"1.Бежать левее", u8"2.Бежать правее");
							break;
						}
						if (a == 28)
						{
							display_buttons(2, u8"1.Продолжить разбегаться", u8"2.Может быть продолжить разбегаться?");
							break;
						}
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					else
						break;
				case SDLK_1:
					if (a == 13) { rjson("strings/beginning2.gptext"), display_text(a), a++, goNext = true; }
					if (a == 20) { rjson("strings/run.gptext"), display_text(a), a++, goNext = true, run = true; }
					if (a == 23) { display_text(a), a++; }
					if (a == 28) { display_text(a), a++; }
					break;
				case SDLK_2:
					if (a == 13) { rjson("strings/beginning2.gptext"), display_text(a), a++, goNext = true; }
					if (a == 20) { rjson("strings/grave.gptext"),  display_text(a), a++, goNext = true; }
					if (a == 23) { display_text(a), a++; }
					break;
				case SDLK_3:
					if (a == 13) { rjson("strings/beginning2.gptext"), display_text(a), a++, goNext = true; }
					break;

				default:
					break;
				}
			/*
			case SDL_MOUSEBUTTONDOWN:
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					leftClick = true;
				}
				if (CheckButton1.CheckEvents(leftClick) && p == 13)
				{
					goNext = true;
					std::cout << "LOL" << std::endl;
					p++;
				}

				if (CheckButton2.CheckEvents(leftClick) && p == 13)
				{
					goNext = true;
					std::cout << "LMAO" << std::endl;
					p++;
				}

				if (CheckButton3.CheckEvents(leftClick) && p == 13)
				{
					goNext = true;
					std::cout << "Poggers" << std::endl;
					p++;
				}

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						leftClick = false;
					}
				}
				break;
				}
			*/
			default:
				break;
			}
		}
		//window.pollEvents();
		
		window.clear();

	}
	Mix_FreeMusic(background);
	Mix_CloseAudio();
	return 0;
}