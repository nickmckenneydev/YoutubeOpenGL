#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
//GLOBALS
SDL_Window* mWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

SDL_Surface* mSurface;

bool gQuit = false;
//VAO globals
GLuint gVertexArrayObject = 0;
//VBO globals
GLuint gVertexBufferObject = 0;
//Functions
GLuint gGraphicsPipelineShaderProgram = 0;
//char* vs std::string&
//std.cString
GLuint CompileShader(GLuint type,std::string& source) {

}
GLuint CreateShaderProgram(std::string& vertexShaderSource, std::string& fragmentShaderSource) {
	GLuint programObject = glCreateProgram();
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
}
void CreateGraphicsPipeline() {
	
	std::string vs="w";
	std::string fs="a";
	gGraphicsPipelineShaderProgram = CreateShaderProgram(vs, fs);
}
void GetOpenGLVersionInfo() {
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}
void VertexSpecifiction() {
	//create verticies on CPU side
	const std::vector<GLfloat> vertexPosition{
		-0.8f,-0.8f,0,
		0.8f,-0.8f,0,
		-0.0f,0.8f,0,
	};
	glGenVertexArrays(1, &gVertexArrayObject);
	glBindVertexArray(gVertexArrayObject);//Select the vertex array I created
	
		glGenBuffers(1, &gVertexBufferObject);//generate VBO
	glBindBuffer(GL_ARRAY_BUFFER, gVertexArrayObject);
	glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(gVertexArrayObject, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
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
	std::string goatName = "gruff";

	char* goatNameAsCStr = goatName.data();
	std::cout << "&goatName:" << &goatName << std::endl;
	std::cout << "&goatNameAsCStr:" << &goatNameAsCStr << std::endl;
	goatNameAsCStr[0] -= 32;
	std::cout << "&goatName.c_str()" << &goatName.c_str() << std::endl;



	InitalizeProgram("Nick",640,480);
	VertexSpecifiction();
	//CreateGraphicsPipeline();
	MainLoop();
	CleanUp();
	return 0;
}

//notes
// glGen -> Allocation
//VAO -> How to Access VBO glGenVertexArrays,glBindVertexArray
//VBO -> Actual Data  glGenBuffer,glBindBuffer,glBufferData

//Vertex Specificiation -> VAO and VBO -> veritices
//Vertex shader