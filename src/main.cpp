#include "SCOPE/SCOPE.h"
#include "SCOPE/UIs/UIManager.h"

int main(){

    SCOPE::Scene scene;
    SCOPE::Context context;
    SCOPE::UIManager UI;
    
    context.init();     // initialization of the context
    UI.init(context);    // initialization of IMGUI
   
    // OpenGL initialization (always after creating the OpenGL context)
    SCOPE::init();

    SCOPE::Shader shader("libs/SCOPE/resources/shaders/default.vert", "libs/SCOPE/resources/shaders/default.frag");   // default shader for the model
    SCOPE::Model model("models/survival_guitar_backpack/scene.gltf");   // loading a model
    
    // Setting up the scene
    scene.setModel(model);
    scene.setCamera(SCOPE::Camera());

    // Render loop
    while (!glfwWindowShouldClose(context.window)){

        scene.update(context);
        scene.render(context, shader);
        UI.draw(scene, context);  // Draw the UIs
    }

    UI.shutDown();  // Shutdown IMGUI
    SCOPE::shutDown();  // Shutdown GLFW

    return 0;
}
