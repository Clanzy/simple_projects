#include "app.hpp"

#include "color-code.hpp"

#include <chrono>
#include <thread>

App::App()
{
}

int App::OnExecute()
{
	if (!running_) {
		return 1;
	}

	using namespace std::chrono;
	const time_point<system_clock> now = system_clock::now();
	const auto ms_per_frame = thousand_ms_ / fps_;
	long long start;
	long long delay_time;

	SDL_Event event;
	while (running_) {
		start = duration_cast<milliseconds>(now.time_since_epoch())
				.count();
		while (SDL_PollEvent(&event) == 1) {
			OnEvent(event);
		}
		OnLoop();
		OnRender();

		delay_time =
			ms_per_frame -
			(duration_cast<milliseconds>(now.time_since_epoch())
				 .count() -
			 start);
		if (delay_time > 0) {
			std::this_thread::sleep_for(milliseconds(delay_time));
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
				   SDL_WINDOWPOS_CENTERED, window_width_,
				   window_height_, 0);

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

	constexpr int max_alpha = 0xFF;
	SDL_SetRenderDrawColor(renderer_, r, g, b, max_alpha);

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
