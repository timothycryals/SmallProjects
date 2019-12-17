#version 150

in vec4 vPosition;
uniform vec4 uColor;
out vec4 color;


void
main()
{
    color = uColor;
	gl_Position = vPosition;
}
