#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <iostream>
void InitalizeProgram() {

}
void MainLoop() {

}
void CleanUp(){}
int main(){}
//struct SDLApplication {
//	SDL_Window* mWindow;
//	SDL_Renderer* mRenderer;
//	bool gameIsRunning;
//	SDLApplication(const char* title, int width, int height) {
//		SDL_Init(SDL_INIT_VIDEO);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//		mWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//		mRenderer = SDL_CreateRenderer(mWindow, "opengl");
//		SDL_SetWindowTitle(mWindow, title);
//	}
//	~SDLApplication() {
//		SDL_Quit();
//	}
//
//};
//
//
//int main(int argc, char* argv[])
//{
//	SDLApplication app("NICK NICK", 800, 600);
//	return 0;
//}