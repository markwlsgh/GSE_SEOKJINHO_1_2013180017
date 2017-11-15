#version 330

layout(location=0) out vec4 FragColor;

uniform vec4 u_Color;
//uniform float u_Time
void main()
{
	//float term = sin(u_Time);
	FragColor = vec4(u_Color.r, u_Color.g, u_Color.b, u_Color.a);
}
