//Quelle: https://antongerdelan.net/opengl/shaders.html

#version 410

layout(location=0) in vec3 Position;

void main(){
    gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
}