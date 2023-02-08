#include "app.hpp"

#include "color-code.hpp"

#include <chrono>

App::App()
{
	running_ = true;
}

int App::OnExecute()
{
	if (running_ == false) {
		return 1;
	}

	const int clocks_per_frame = cps_ / fps_;
	int start = 0;
	int delay_time;

	SDL_Event event;
	while (running_) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event) == 1) {
			OnEvent(event);
		}
		OnLoop();
		OnRender();

		delay_time = clocks_per_frame - (SDL_GetTicks() - start);
		if (delay_time > 0) {
			SDL_Delay(delay_time);
		}
	}
	OnCleanup();

	return 0;
}

bool App::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	window_ = SDL_CreateWindow(name_.data(), SDL_WINDOWPOS_CENTERED,
				   SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	if (window_ == nullptr) {
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, 0);

	return true;
}

void App::OnEvent(const SDL_Event &event)
{
	if (event.type == SDL_QUIT) {
		running_ = false;
	}
}

void App::OnLoop()
{
}

void App::OnRender()
{
	static SmoothColorCode r;
	static SmoothColorCode g;
	static SmoothColorCode b;
	static int counter = 0;

	r++;

	if (counter % 2 == 0) {
		g++;
	}
	if (counter % 3 == 0) {
		b++;
	}

	SDL_SetRenderDrawColor(renderer_, r, g, b, 255);

	SDL_RenderFillRect(renderer_, NULL);

	SDL_RenderPresent(renderer_);

	counter++;
}

void App::OnCleanup()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}
