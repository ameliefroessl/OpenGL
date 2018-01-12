
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
    
    
    GLuint vao = createVAO(); //create and bind VAO, needs to happen after winodw creation
    GLuint vb = createTriangle(); //create triangle vertecies and returna buffer handle to buffer with them inside
    GLuint vbCube = createCube();
    
    glm::mat4 mvp = modelViewProjection(true); //get a model view projection matrix
    GLuint programID = loadShaders( "triangleVertexShader.glsl", "triangleFragmentShader.glsl" );//load glsl shaders
    GLuint matrixID = glGetUniformLocation(programID, "MVP"); //get handle to uniform varibale in vertex shader
    
    //z-buffer depth test enabling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);// Accept fragment if it closer to the camera than the former one
    
    GLuint colorbuffer = genAndBindBufferID();
    static GLfloat g_color_buffer_data[12*3*3]; //buffer holding color information
    
    
    do{
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbCube);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        

        fillColorBuffer(g_color_buffer_data, 12*3); //reload the color buffer every frame

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0); 
        
        // Draw the triangle (s) !
        glDrawArrays(GL_TRIANGLES, 0, 3*12); // Starting from vertex 0; 3 vertices total -> 1 triangle or for the cube... we have 12 triangle
        glDisableVertexAttribArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    glDeleteBuffers(1, &vbCube);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &vao);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
    
}








