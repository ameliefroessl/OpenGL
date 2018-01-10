#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;// model view projection matrix uniform accessible through c++ program 

void main(){
    
    //with Model view projection matrix
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0f);

    //without MVP matrix
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    
}
