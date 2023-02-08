#pragma once

#include <string_view>
#include <ctime>

#include <SDL.h>

class App {
private:
	static constexpr std::string_view name_ = "Trippy Screen";

	static constexpr int cps_ = CLOCKS_PER_SEC;
	static constexpr int fps_ = 90;

	bool running_;

	SDL_Renderer *renderer_;
	SDL_Window *window_;

public:
	App();
	int OnExecute();

	bool OnInit();

	void OnEvent(const SDL_Event &event);

	void OnLoop();

	void OnRender();

	void OnCleanup();
};
