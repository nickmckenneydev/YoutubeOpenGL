//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int width = 800;
const unsigned int height = 800;


// Vertices coordinates
GLfloat vertices1[] =
{
	//     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f, // Front Left
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f, // Back Left
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f, // Back Right
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f, // Front Right
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    2.5f, 5.0f  // Top
};


GLfloat vertices2[] =
{
	//     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "NickNick", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
	gladLoadGL();
	glViewport(0, 0, width, height);
	Shader shaderProgram("default.vert", "default.frag");
	
	//VAO VAO1;
	GLuint myVAO_ID; // Just a simple integer
	glGenVertexArrays(1, &myVAO_ID); // Create it
	glBindVertexArray(myVAO_ID); // Bind it
	VBO VBO1(vertices1, sizeof(vertices1));
	EBO EBO1(indices, sizeof(indices));
	

		VBO1.Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		VBO1.Unbind();
	

	glBindVertexArray(0);
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(vertices2, sizeof(vertices2));
	EBO EBO2(indices, sizeof(indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); //glVertexAttribPointer && glEnableVertexAttribArray;
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);
	VBO2.Unbind();
	EBO2.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//TEXTURES
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/YoutubeOpenGL/";
	shaderProgram.Activate();
	Texture texture1((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	
	
	Texture texture2((parentDir + texPath + "pop_cat2.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	texture1.texUnit(shaderProgram, "tex0", 0);
	glEnable(GL_DEPTH_TEST);
	float rotation = 0.1f;
	double prevTime = glfwGetTime();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.1f;
			prevTime = crntTime;
		}
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		texture1.Bind(GL_TEXTURE0);
		glGenVertexArrays(1, &myVAO_ID); // Create it VAO1.Bind();
		glm::mat4 model1 = glm::mat4(1.0f);
		model1 = glm::translate(model1, glm::vec3(-0.5f, 0.0f, 0.0f));
		model1 = glm::rotate(model1, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		texture2.Bind(GL_TEXTURE0);
		VAO2.Bind(); 
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(0.5f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, glm::radians(-rotation*50), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete all the objects
	glDeleteVertexArrays(1, &myVAO_ID);
	VBO1.Delete();
	EBO1.Delete();

	glDeleteVertexArrays(1, &VAO2.ID);//VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}