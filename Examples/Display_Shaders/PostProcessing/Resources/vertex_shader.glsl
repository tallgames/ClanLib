#version 150
attribute vec4 Position;
attribute vec2 TexCoord0;

out vec2 TexCoord;

layout (std140) uniform ProgramUniforms
{
	mat4 cl_ModelViewProjectionMatrix;
	float Amount;
	float Timer;
};

void main(void) 
{ 
	gl_Position = cl_ModelViewProjectionMatrix*Position; 

	TexCoord = TexCoord0; 
}
