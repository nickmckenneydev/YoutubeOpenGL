#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <iostream>
//GLOBALS
SDL_Window *mWindow=nullptr;
SDL_Renderer *mRenderer=nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false;
void InitalizeProgram(const char* title,int width,int height) {
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL3 could not be loaded" << std::endl;
		exit(1);
	}
		//OpenGL Version 3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 1);

		mWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		mRenderer = SDL_CreateRenderer(mWindow, "opengl");
		SDL_SetWindowTitle(mWindow, title);
		gOpenGLContext = SDL_GL_CreateContext(mWindow);
		if (gOpenGLContext == nullptr)
		{
			std::cout << "OpenGL could not be loaded" << std::endl;
		}
}		

void MainLoop() {
	while (!gQuit) 
	{

	}
}
void CleanUp(){
	
	SDL_Quit();
}
int main(){
	InitalizeProgram();
}
