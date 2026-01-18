#include "SCOPE/SCOPE.h"

int main(){
    Scene scene;
    // Context creation
    Context context;
    context.init();
    Camera& camera = context.cameraController.camera;


    SCOPE::openGL_init();
    SCOPE::UI_init(context);    // initialization of IMGUI

    // Shaders loading
    Shader model_shader("libs/SCOPE/resources/shaders/default_lights.vert", "libs/SCOPE/resources/shaders/default_lights.frag");

    // Models loading
    Model model1("models/backpack2/scene.gltf");

    scene.setModel(model1);
    scene.setCamera(camera);


    UICameraController uiCam(&context.cameraController);
    UIModel uiModel;
    UILight uiLight;

    // Frame
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Render loop
    while (!glfwWindowShouldClose(context.window))
    {
        // Updating frames
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call to the input manager
        context.processInput(context.window, deltaTime);

        scene.render(model_shader);

        // UI update
        SCOPE::UI_update();

        uiCam.draw();
        uiLight.draw(&scene);
        uiModel.draw(&scene);

        SCOPE::UI_render();

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    // End of IMGUI
    SCOPE::UI_shutDown();

    glfwTerminate();

    return 0;
}
