# OpenGL

me getting back into OpenGL/ C++ 

1. on OSX 


**GLFW**
to deal with window creation/destroying, user input/output we will use GLFW. Recommended by https://solarianprogrammer.com/2013/05/10/opengl-101-windows-osx-linux-getting-started/ and http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/. Reason enough I suppose...

*downloaded* GLFW from http://www.glfw.org

*installed* using these instructions(but instead of cloning I downloaded from the website): https://codeyarns.com/2015/08/25/how-to-build-and-use-glfw/

is now installed in my /usr/local/include/GLFW/ dir

**GLEW**
What is glew? https://gamedev.stackexchange.com/questions/112182/what-is-glew-and-how-does-it-work

GL/glew.h 

Downloaded the zip file from : http://glew.sourceforge.net 

cd glew-2.1.0/ 
cd build/
cmake ./cmake
make -j4 (this indicates how many jobs should be running simultaniously) 

it got installed into Downloads folder, so I moved it to /usr/local/include:

mv -v /Users/<username>/Downloads/glew-2.1.0/include/ /usr/local/include/GL
  
i believe 'install' would have done the move for me. 



