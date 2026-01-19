#include "SCOPE/SCOPE.h"

int main(){

    SCOPE::Scene scene;

    // Context creation
    SCOPE::Context context;
    context.init();

    SCOPE::openGL_init();
    SCOPE::UI_init(context);    // initialization of IMGUI

    // Shaders loading
    SCOPE::Shader model_shader("libs/SCOPE/resources/shaders/default_lights.vert", "libs/SCOPE/resources/shaders/default_lights.frag");

    // Model loading
    SCOPE::Model model("models/backpack2/scene.gltf");
    scene.setModel(model);

    // Camera
    scene.setCamera(SCOPE::Camera());

    // User interfaces
    SCOPE::UICameraController uiCam;
    SCOPE::UIModel uiModel;
    SCOPE::UILight uiLight;

    // Render loop
    while (!glfwWindowShouldClose(context.window)){

        scene.update(context);
        scene.render(context, model_shader);

        // UI update
        SCOPE::UI_update();

        uiCam.draw(context);
        uiLight.draw(scene);
        uiModel.draw(scene);

        SCOPE::UI_render();   
    }

    SCOPE::UI_shutDown();
    
    SCOPE::shutDown();

    return 0;
}
