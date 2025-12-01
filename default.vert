#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Controls the scale of the vertices


// Inputs the matrices needed for 3D viewing with perspective


uniform mat4 cameraMatrix;
uniform mat4 model; 

void main()
{
	// --- UPDATE THIS LINE ---
	// Apply the Model matrix first, then the Camera matrix
	gl_Position = cameraMatrix * model * vec4(aPos, 1.0);
	
	color = aColor;
	texCoord = aTex;
}