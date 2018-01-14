//
//  helper.hpp
//  
//
//  Created by Amelie Froessl on 1/10/18.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>
#include <GL/glew.h>

// loads the glsl shaders from the paths
GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);

// load a BMP file
GLuint loadBMPCustom(const char * imagepath);

//returns a model view projection matrix
glm::mat4 modelViewProjection();

// creates a Vertex Array Object and binds it to an ID
GLuint createVAO();

//generate and bind a buffer id
GLuint genAndBindBufferID();

//creates the vertices of a triangle and the buffer and fill it
GLuint createTriangle();

// same for cube
GLuint createCube();

//fills a buffer with set random cube colors
GLuint createCubeColors();

//fils a buffer with 2 uv coordinates for each vertex of the cube
GLuint createTextureUV();

// fills a buffer with random cube colors, not set
void fillColorBuffer(GLfloat * buffer, int bufferSize);

//return a model view projection matrix
glm::mat4 modelViewProjection(bool proj);



#endif /* helper_hpp */


