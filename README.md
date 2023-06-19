# AENG
Acorn engine, a 3D engine powered by OpenGL

This project started as a way to learn C++, now I'm working on the implementation of new feautres and some stuff.

All contributions to the project are wellcome!

### [----------( **Implementations** )-----------]

### ✔ Implemented Feautres:
* ~~Import .obj files.~~ Compile obj files to bin.
* Camera.
* Direction based movement.
* Multiple objects render.
* Textures(partially).
* Custom shaders(partially).

### ✘ Future Feautres:

* Multi lightning
* Shadows
* Scenes.
* Phisics.

### [----------( **Running** )-----------]

### 🗂 Dependencies:

* OpenGL
* Eglew
* Glfw

**You must install the dependencies before compiling**

The script `run.sh` handles the compilation and execution of the needed program, for example:
```bash
./run.sh main # will run the main script
```

### The models

The engine now uses binary files to load the models, to compile a file
must be `.obj` and you will use:
```bash
./run.sh fs # the program will ask you to compile a file
```
The raw `.obj` files will must be in the path `scene/models/` the program will ask you the file, you must write it without the extension (`file.obj -> file`) and will compile it to `scene/compiled/file.dat`
 