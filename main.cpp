#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
//GLOBALS
GLuint gScreenWidth = 640;
GLuint gScreenHeight = 480;
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

//SHADERS
std::string gVertexShaderSource =
"#version 410 core\n"
"in vec4 position;\n"
"void main(void)\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
"}\n";

std::string gFragmentShaderSource =
"#version 410 core\n"
"out vec4 color;\n"
"void main(void)\n"
"{\n"
"color = vec4(1.0f,0.5f,0.0f,1.0f);\n"
"}\n";

GLuint CompileShader(GLuint type,std::string& source) {
	GLuint shaderObject;
	if (type == GL_FRAGMENT_SHADER) {
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (type == GL_VERTEX_SHADER)
	{
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}

		const char* src = source.c_str();
		glShaderSource(shaderObject, 1, &src, nullptr);
		glCompileShader(shaderObject);

		return shaderObject;
	
}
GLuint CreateShaderProgram(std::string& vertexShaderSource, std::string& fragmentShaderSource) {
	GLuint programObject = glCreateProgram();

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	glLinkProgram(programObject);
	return programObject;
}

void CreateGraphicsPipeline() {
	gGraphicsPipelineShaderProgram = CreateShaderProgram(gVertexShaderSource, gFragmentShaderSource);
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

	//COPIES DATA
	glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(gVertexArrayObject, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);//Unselect Vertex ARRAY
	glDisableVertexAttribArray(0);
}
int InitalizeProgram(const char* title,int width,int height) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}
		//OpenGL Version 3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		mWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (mWindow == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
			return 1;
		}

		SDL_SetWindowTitle(mWindow, title);
		gOpenGLContext = SDL_GL_CreateContext(mWindow);//OpenGL object
		

		if (gOpenGLContext == nullptr)
		{
			std::cout << "OpenGL could not be loaded" << std::endl;
		}
		
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){// INIT GLAD LIBRARY. BRINGS OPENGL functions
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
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, gScreenWidth, gScreenHeight);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(gGraphicsPipelineShaderProgram);

}
void Draw(){
	glBindVertexArray(gVertexArrayObject);//Collection of data
	glBindBuffer(GL_ARRAY_BUFFER, gVertexArrayObject);//take collection of data
	glDrawArrays(GL_TRIANGLES, 0, 3);//Kick of Graphics Pipeline. Draw from data
	glUseProgram(0);//CLEANUP

}
void MainLoop() {
	while (!gQuit) 
	{
		Input();
		PreDraw();
		Draw();
		SDL_GL_SwapWindow(mWindow);//updates screen. Takes what is drawn in back buffer and presents to front buffer

	}
}
void CleanUp(){
	SDL_GL_DestroyContext(gOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
int main(){
	InitalizeProgram("Nick",640,480);
	VertexSpecifiction();
	CreateGraphicsPipeline();//Creates vertex and frag shaders
	MainLoop();//Draws Triangle

	CleanUp();
	return 0;
}

//notes
// glGen -> Allocation
//VAO -> How to Access VBO glGenVertexArrays,glBindVertexArray
//VBO -> Actual Data  glGenBuffer,glBindBuffer,glBufferData

//Vertex Specificiation -> VAO and VBO -> veritices
//Vertex shader