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

//returns a model view projection matrix
glm::mat4 modelViewProjection();

// creates a Vertex Array Object and binds it to an ID
GLuint createVAO();


GLuint createTriangle();

glm::mat4 modelViewProjection(bool proj);


#endif /* helper_hpp */


