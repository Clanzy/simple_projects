#pragma once

#include <string_view>

#include <SDL.h>

class App {
private:
	static constexpr std::string_view name_ = "Trippy screen";

	static constexpr int window_width_ = 800;
	static constexpr int window_height_ = 600;

	static constexpr long long thousand_ms_ = 1000;
	static constexpr int fps_ = 90;

	bool running_ = true;

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
