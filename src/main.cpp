/// \file	main.cpp

/// === INCLUDES	================================================================================
#include <sdl.h>
#include <window.h>
#include <texture.h>
#include <renderer.h>
#include <surface.h>

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "SDL2_gfx/SDL2_framerate.h"

#include "param.h"
#include "engine.h"

/// === NAMESPACE	================================================================================
using namespace std;
using namespace sdl;

/// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	static const string title = "AI Fish";
	bool b_done = false;
	SDL_Event event;
	bool b_fast_mode = false;

	std::srand(std::time(0));

	try
	{
		SDL sdl(EInit::VIDEO | EInit::TIMER);

		/// Cr�ation de la fen�tre
		Window window(title, Window::CENTERED, Window::CENTERED, Param::window_width,
				Param::window_height, Window::SHOWN);

		Renderer renderer(window, -1, Renderer::ACCELERATED);

		/// Init Framerate manager
		FPSmanager manager;
		SDL_initFramerate(&manager);
		SDL_setFramerate(&manager, Param::framerate);

		uint32_t start_time = SDL_GetTicks();
		uint32_t frame_count = 0;

		Engine engine(renderer);

		while (b_done == false)
		{
			/// Handle events
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					b_done = true;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_f) b_fast_mode = !b_fast_mode;
					//else if (event.key.keysym.sym == SDLK_ESCAPE) moteur.echangeFonctions();
					break;
				case SDL_MOUSEBUTTONUP:
					//moteur.clic(event.button.x, event.button.y);
					break;
				default:
					break;
				}
			}

			engine.update();

			if (b_fast_mode == false)
			{
				/// Set background: White
				renderer.setDrawColor(255, 255, 255, 255);
				renderer.clear();

				engine.display(renderer);

				renderer.present();

				/// Update and Display current FrameRate
				SDL_framerateDelay(&manager);

				frame_count++;

				if (SDL_GetTicks() - start_time >= 1000)
				{
					float fps = (frame_count / (float) (SDL_GetTicks() - start_time)) * 1000;

					window.setTitle(
							title + string(" FPS: ")
									+ to_str<uint32_t>(static_cast<uint32_t>(fps)));

					frame_count = 0;
					start_time = SDL_GetTicks();
				}
			}
			else
			{
				window.setTitle(title + string(" Fast Mode "));
			}
		}

		cout << "SDL2: Quit" << endl;
		return 0;

	} catch (const SDL_Exception& err)
	{
		cerr << "Error SDL: " << err.what() << endl;
	} catch (...)
	{
		cerr << "Unhandle exception" << endl;
	}

	return 1;
}
/// === END OF FILE	================================================================================
