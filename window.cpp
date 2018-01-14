
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

//import glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //for matirx transformations
#include "glm/gtx/string_cast.hpp"
#include "glm/ext.hpp" // for mat to string conversions, terminal output



using namespace glm;

#include "helper.hpp"

//code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

int main() {
    
    
    
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }else{
        fprintf(stderr, "GLFW initialized\n");
    }
    
    
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    
    
    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 1024, 768, "Window", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    glm::mat4 mvp = modelViewProjection(true); //get a model view projection matrix
    
//    GLuint programID = loadShaders( "triangleVertexShader.glsl", "triangleFragmentShader.glsl" );//load glsl shaders
    GLuint programID = loadShaders( "textureVertexShader.glsl", "textureFragmentShader.glsl" );//load glsl shaders
    GLuint matrixID = glGetUniformLocation(programID, "MVP"); //mvp uniform in vertex shader
    GLuint textureSampleID = glGetUniformLocation(programID, "myTextureSampler"); // texture uniform in vertex shader
    
    
    //z-buffer depth test enabling to only draw the ones that are closer to the camera
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);// Accept fragment if it closer to the camera than the former one
    
    //https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)
    GLuint vertexArrayObject = createVAO(); //create and bind VAO, needs to happen after winodw creation
    GLuint vertexbuffer = createTriangle(); //create triangle vertecies and returna buffer handle to buffer with them inside
    GLuint vertexBufferCube = createCube();
    
    //color information for shaders
    GLuint colorbuffer = genAndBindBufferID();
    static GLfloat g_color_buffer_data[12*3*3]; //buffer holding color information
    
    //texture information for shaders
    GLuint textureBuffer = createTextureUV();
    
    //texture information for shaders
    GLuint texture = loadBMPCustom("uvtemplate2.bmp");
    
    
    do{
        
        mvp = liveModelViewProjectionMatrix(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//set the uniform variable in the shader
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(textureSampleID, 0);
        
        //vertices attribute at location 0 <- indicated which buffer for shader
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCube);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,0,(void*)0);
        
        //attribute at location 1 this is random color
//        glEnableVertexAttribArray(1);
//        fillColorBuffer(g_color_buffer_data, 12*3); //reload the color buffer every frame
//        glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
//        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
        
        // texture buffer
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,textureBuffer);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0); // 2 instead of 3 (2 UV corrdinates)

        
        // Draw the triangle (s) !
        glDrawArrays(GL_TRIANGLES, 0, 3*12); // Starting from vertex 0; 3 vertices total -> 1 triangle or for the cube... we have 12 triangle
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexBufferCube);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &vertexArrayObject);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
    
}








