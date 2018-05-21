# rob-DEV-Engine
An OpenGL Cross Platform Game Engine (WIP)
My implementation of a C++ Game Engine / OpenGL renderer, the engine is obviously not an "engine" in the sense that you won't be making games anytime soon. Instead it is my first attempt at constructing a component based core library ontop of which an editor could be placed. 

Features:
Input System - Mouse and Keyboard
OpenGL Batch Renderer - With vertex indexing
OBJ File Importer - Vertex duplicates are removed and indexes are calculated.
Virtual File System - A file of packaged files which can be read in from disk and loaded into RAM.
Entity based objects - All Objects are respresented under an "Entity" with other components i.e meshes/transforms are added under it.
Clear namespacing
Utilites such as Time, IO and other misc needs.

External Libraries used:
GLFW
GLEW
GLM

I'm gonna continue this and see where it ends up.
![1](https://github.com/rob-DEV/rob-DEV-Engine/blob/master/rob-DEV-Engine-Core/dev_img/4.PNG)
