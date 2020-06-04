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
		Text text1(Window::renderer, u8"assets/times.ttf", 25, b1, { 226, 106, 106, 0 });
		Text text2(Window::renderer, u8"assets/times.ttf", 25, b2, { 255, 255, 126, 0 });
		text1.display(40, 450, Window::renderer);
		text2.display(40, 480, Window::renderer);
	}
	if (amount == 3)
	{
		SDL_RenderClear(Window::renderer);
		Text text1(Window::renderer, u8"assets/times.ttf", 25, b1, { 226, 106, 106, 0 });
		Text text2(Window::renderer, u8"assets/times.ttf", 25, b2, { 123, 239, 178, 0 });
		Text text3(Window::renderer, u8"assets/times.ttf", 25, b3, { 255, 255, 126, 0 });
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

	Mix_Music* background = Mix_LoadMUS("assets/2thieves.mp3");
	Mix_Music* runmin = Mix_LoadMUS("assets/runmin.mp3");
	Mix_Music* run1 = Mix_LoadMUS("assets/run.mp3");
	Mix_Music* deadmin = Mix_LoadMUS("assets/deadmin.mp3");
	Mix_Music* fool = Mix_LoadMUS("assets/fool.mp3");
	Mix_Chunk* ded = Mix_LoadWAV("assets/ded.wav");
	Mix_Chunk* dead = Mix_LoadWAV("assets/dead.wav");

	int a = 1;
	bool leftClick = false;
	bool goNext = false;
	bool run = false;
	bool grave = false;
	bool dawg = false;
	bool sigma = false;
	bool sigma2 = false;
	bool sigma3 = false;
	bool longr = false;
	bool play_run = false;
	bool play_run1 = true;

	Window window("Endless Bonch", 1280, 720);
	rjson("strings/intro.gptext");
	Mix_PlayMusic(background, 0);
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

					if (a == 16)
						Mix_PlayChannel(-1, ded, 0);

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
					if (play_run)
					{
						Mix_PlayMusic(runmin, 0);
						play_run = false;
						break;
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
						if (a == 31 && play_run1)
						{
							Mix_PlayMusic(run1, 0);
							play_run1 = false;
							display_text(a);
							a++;
							break;
						}
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;

					}

					if (a < 26 && goNext && grave)
					{
						if (a == 24)
						{
							display_buttons(2, u8"1.Да", u8"2.Попытаться закрыть уши");
							break;
						}
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					if (a == 26&&grave)
					{
						display_buttons(3, u8"1.Вы решаете, что хуже уже не будет, и идете на звуки музыки", 
							u8"2.Даже самая виртуозная игра на скрипке не дает вам забыть,что вы все еще на кладбище с мертвецами.", 
							u8"   Разворачиваетесь и бежите прочь от музыки.");
						break;
					}
					if (a < 65&&sigma)
					{
						if (a == 39)
						{
							display_buttons(2, u8"1.Остаться", u8"2.Попытаться уйти");
							break;
						}
						if (a == 48)
						{
							display_buttons(2, u8"1.Отправиться короткой горной дорогой", u8"2.Пойти длинной, но безопасной дорогой");
							break;
						}
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}

					if (a < 72 && longr)
					{
						if (a == 69)
						{
							display_buttons(2, u8"1.Отвлечь толпу шутками", u8"2.Начать передразнивать аббата");
							break;
						}
						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					
					if (a < 68 && sigma2)
					{
						if (a == 33)
						{
							display_buttons(2, u8"1.Попытаться попросить помощи", u8"2.Промолчать");
							break;
						}
						if (a == 35)
							Mix_PlayChannel(-1, dead, 0);

						if (a == 36)
							Mix_PlayMusic(deadmin, 0);

						if (a == 42)
						{
							display_buttons(2, u8"1.Толкаться", u8"2.Бежать");
							break;
						}
						if (a == 46)
						{
							display_buttons(2, u8"1.Пинаться", u8"2.Пытаться бежать");
							break;
						}
						if (a == 55)
						{
							display_buttons(2, u8"1.Убежать влево", u8"2.Убежать вправо");
							break;
						}
						if (a == 56)
							Mix_PlayMusic(fool, 0);

						display_text(a);
						a++;
						std::cout << a << std::endl;
						break;
					}
					
					if (a < 78 && sigma3)
					{
						if (a == 44)
						{
							display_buttons(2, u8"1.Попытаться попросить помощи", u8"2.Промолчать");
							break;
						}
						if (a == 53)
						{
							display_buttons(2, u8"1.Толкаться", u8"2.Бежать");
							break;
						}
						if (a == 57)
						{
							display_buttons(2, u8"1.Пинаться", u8"2.Пытаться бежать");
							break;
						}
						if (a == 66)
						{
							display_buttons(2, u8"1.Убежать влево", u8"2.Убежать вправо");
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
					if (a == 20) { rjson("strings/run.gptext"), display_text(a), a++, goNext = true, run = true, play_run = true; }
					if (a == 23&&run) { display_text(a), a++; }
					if (a == 24 && grave) { display_text(a), a++; }
					if (a == 26 && grave) { rjson("strings/sigma.gptext"), display_text(a), a++, sigma = true; }
					if (a == 39&&sigma)  { display_text(a), a++; } 
					if (a == 48 && sigma) { display_text(a), a++; }
					if (a == 69&&longr) { display_text(a), a++; }
					if (a == 28&&run) { display_text(a), a++; }
					if (a == 33&&sigma2) { display_text(a), a++; }
					if (a == 42&&sigma2) { display_text(a), a++; }
					if (a == 46 && sigma2) { display_text(a), a++; }
					if (a == 55 && sigma2) { display_text(a), a++; }
					if (a == 44&&sigma3) { display_text(a), a++; }
					if (a == 53 && sigma3) { display_text(a), a++; }
					if (a == 57 && sigma3) { display_text(a), a++; }
					if (a == 66 && sigma3) { display_text(a), a++; }
					break;
				case SDLK_2:
					if (a == 13) { rjson("strings/beginning2.gptext"), display_text(a), a++, goNext = true; }
					if (a == 20) { rjson("strings/grave.gptext"),  display_text(a), a++, goNext = true, grave = true; }
					if (a == 24 && grave) {
						SDL_RenderClear(Window::renderer);
						Text ss(Window::renderer, u8"assets/times.ttf", 30, u8"Вы не можете противиться искусству", { 255, 255, 255, 255 });
						ss.display(40, 450, Window::renderer);
					}
					if (a == 26 && grave) { rjson("strings/sigma2.gptext"), display_text(a), a++, sigma2 = true; }
					if (a == 39 && sigma) { rjson("strings/sigma3.gptext"), display_text(a), a++, sigma2 = true, sigma = false; }
					if (a == 48 && sigma) { rjson("strings/longr.gptext"), display_text(a), a++, longr = true; }
					if (a == 69 && longr) { display_text(a), a++; }
					if (a == 23&&run) { display_text(a), a++; }
					if (a == 33 && sigma2) { display_text(a), a++; }
					if (a == 42 && sigma2) { display_text(a), a++; }
					if (a == 46 && sigma2) { display_text(a), a++; }
					if (a == 55 && sigma2) { display_text(a), a++; }
					if (a == 44 && sigma3) { display_text(a), a++; }
					if (a == 53 && sigma3) { display_text(a), a++; }
					if (a == 57 && sigma3) { display_text(a), a++; }
					if (a == 66 && sigma3) { display_text(a), a++; }
					break;
				case SDLK_3:
					if (a == 13) { rjson("strings/beginning2.gptext"), display_text(a), a++, goNext = true; }
					break;

				default:
					break;
				}
			default:
				break;
			}
		}
		//window.pollEvents();
		
		window.clear();

	}
	Mix_FreeMusic(background);
	Mix_FreeChunk(ded);
	Mix_CloseAudio();
	return 0;
}