#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
//GLOBALS
SDL_Window* mWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

SDL_Surface* mSurface;

bool gQuit = false;
void GetOpenGLVersionInfo() {
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}
int InitalizeProgram(const char* title,int width,int height) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}
		//OpenGL Version 3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 1);

		mWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (mWindow == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
			return 1;
		}

		SDL_SetWindowTitle(mWindow, title);
		gOpenGLContext = SDL_GL_CreateContext(mWindow);
		

		if (gOpenGLContext == nullptr)
		{
			std::cout << "OpenGL could not be loaded" << std::endl;
		}
		
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
			std::cout << "Failed to load GLAD" << std::endl;
			exit(1);
		}
		
}		
int Input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			gQuit = true;
			SDL_DestroyWindow(mWindow);
			SDL_Quit();
		}
	}

return 0;
}

void PreDraw(){
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
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
	SDL_GL_DestroyContext(gOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
int main(){
	InitalizeProgram("Nick NIck",640,480);
	MainLoop();
}

//notes
// glGen -> Allocation
//VAO -> How to Access VBO glGenVertexArrays,glBindVertexArray
//VBO -> Actual Data  glGenBuffer,glBindBuffer,glBufferData