#version 330 core

in vec3 fragmentColor; //coming from vertexshader

out vec3 color; // our output color for the fragment


void main(){
//    color = vec3(1,1,1); //color of triangle
    color = fragmentColor; // color using color assigned in the vertex shader, interpolated between all 3 surrounding vertices
}
