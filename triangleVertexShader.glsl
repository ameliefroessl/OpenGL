#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace; //0 is index from glEnableVertexAttribArray(0)
layout(location = 1) in vec3 vertexColor; // 1 is index from glEnableVertexAttribArray(1)

uniform mat4 MVP;// model view projection matrix uniform accessible through c++ program 

out vec3 fragmentColor; // this will be passed on to the fragment shader

void main(){
    
    //without MVP matrix
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    
    //with Model view projection matrix
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0f);
    
    fragmentColor = vertexColor;// will be passed as is. Will be an interpolation to produce fragment colors.
    
    
    
    
    
}
