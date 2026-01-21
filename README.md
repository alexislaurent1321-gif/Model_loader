# Presentation
This is a demonstration of the [SCOPE](https://github.com/alexislaurent1321-gif/SCOPE) library, a self-made beginner 3D engine. It allows you to load a model, add lights to it, and navigate through the scene.
It loads three imgui user interfaces: one for the model, one for the lights, and one for the camera. The project uses SCOPE as a submodule. 

# Loading a model
The engine loads with assimp, so most formats are therefore compatible.
> [!WARNING]  
Warning: the model needs to be textured. Materials are not yet supported.

## Exemple
The model loaded here is the [survival guitar backpack](https://sketchfab.com/3d-models/survival-guitar-backpack-799f8c4511f84fab8c3f12887f7e6b36) by Berk Gedik, seen in the [learnOpenGL](https://learnopengl.com/) tutorial.
> [!WARNING]  
Warning: this model, like other gltf, is on a 1/100 scale. Do not hesitate to change the size of the model in the main file if another model is loaded.

# Dependencies and installation
After cloning the repo, add it with the command `git clone --recurse-submodules https://github.com/alexislaurent1321-gif/SCOPE.git`. 

