#include "SCOPE/SCOPE.h"

// Frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(){
    // Context creation
    Context context;
    context.init();

    // Loading of openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Camera& camera = context.cameraController.camera;


    // Depth test
    glEnable(GL_DEPTH_TEST); 

    // Initialization of IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Shaders loading
    Shader model_shader("libs/SCOPE/resources/shaders/default_lights.vert", "libs/SCOPE/resources/shaders/default_lights.frag");

    // Models loading
    Model model1("models/backpack2/scene.gltf");


    // -----------------------------
    //  Render loop
    // -----------------------------
    
    UICameraController uiCam(&context.cameraController);
    UIModel uiModel(&model1);
    UILight uiLight;

    while (!glfwWindowShouldClose(context.window))
    {
        // Updating frames
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call to the input manager
        context.processInput(context.window, deltaTime);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model_shader.use();
        model_shader.setUniform("viewPos", camera.Position);
        float shininess = 1.;
        model_shader.setUniform("material.shininess", shininess);


        int pointIndex = 0, dirIndex = 0, spotIndex = 0;

        for (auto &entry : uiLight.lights) {
            if (entry.type == UILight::LightType::Point){
                static_cast<PointLight*>(entry.light.get())->apply(model_shader, pointIndex++);
                const int nbPointLights = pointIndex;
                model_shader.setUniform("nbPointLights", nbPointLights);
            }
            else if (entry.type == UILight::LightType::Directional){
                static_cast<DirLight*>(entry.light.get())->apply(model_shader, dirIndex++);
                const int nbDirLights = dirIndex;
                model_shader.setUniform("nbDirLights", nbDirLights);
            }
        }

        // Space transformations for the vertex shader
        glm::mat4 projection = camera.getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 model = model1.getModelMatrix();

        model_shader.setUniform("projection", projection);
        model_shader.setUniform("view", view);
        model_shader.setUniform("model", model);
        model1.draw(model_shader);

        // UI update
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        uiCam.draw();
        uiLight.draw();
        uiModel.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    // End of IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
