#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
//GLOBALS
SDL_Window* mWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false;

void InitalizeProgram(const char* title,int width,int height) {
	if (SDL_Init(SDL_INIT_VIDEO)<0)
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
		
		SDL_SetWindowTitle(mWindow, title);
		gOpenGLContext = SDL_GL_CreateContext(mWindow);

		if (gOpenGLContext == nullptr)
		{
			std::cout << "OpenGL could not be loaded" << std::endl;
		}
		
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
			std::cout << "Failed to load GLAD" << std::endl;
		}
		
}		
void Input() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		//switch (e.type)
		//{
		//	case SDL_EVENT_QUIT:
		//		std::cout << "QUITTING" << std :: endl;
		//		gQuit = true;
		//		//SDL_Quit();
		//}
	}
}
void PreDraw(){}
void Draw(){}
void MainLoop() {
	while (!gQuit) 
	{
		Input();
		PreDraw();
		Draw();
		SDL_GL_SwapWindow(mWindow);//updates screen
	}
}
void CleanUp(){
	
	SDL_Quit();
}
int main(){
	InitalizeProgram("Nick NIck",640,480);
	MainLoop();
}
