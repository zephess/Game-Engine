#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 vDirection;

uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
	mat4 rotView = mat4(mat3(uView)); 
	
	vDirection = aPos;
	gl_Position = uProjection * rotView * vec4(aPos, 1.0);

}