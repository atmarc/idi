#version 330 core

in vec3 vertex;
in vec4 color;

out vec4 fcolor;

uniform float val;
uniform mat4 TG;

void main()  {
    gl_Position = TG * vec4 (vertex * val, 1.0);
    fcolor = color;
}
