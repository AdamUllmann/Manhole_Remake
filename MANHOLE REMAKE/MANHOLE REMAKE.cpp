// MANHOLE REMAKE.cpp
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "raylib.h"

// defining all scenes
enum class Scene {
    MAIN_MENU,
    SCENE_1,
    SCENE_2,
    // add more scenes as needed
    // MINIGAME_1,
    // MINIGAME_2,
    // ...
};

// a struct to hold all scene data (assets, click boxes, etc.)
struct ClickBox {
    Rectangle bounds;
    Scene targetScene;
    Sound soundEffect;
    bool isMiniGameStart;
};

// a struct to represent a sprite
struct Sprite {
    Texture2D texture;
    Vector2 position;       // vector containing x and y coordinates
    // other things like animations can go here
};

struct SceneData {
    Texture2D image;
    std::vector<ClickBox> clickBoxes;
    std::vector<Sprite> sprites;
    // Add more scene-specific data as needed (e.g., sounds, animations)
};

// Function to handle scene transitions
void ChangeScene(Scene& currentScene, Scene nextScene) {
    currentScene = nextScene;
}


void StartMiniGame() {

}

int main(void)
{
    // initialization
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "MANHOLE");
    ToggleFullscreen();
    InitAudioDevice();
    SetMouseCursor(3);

    Scene currentScene = Scene::MAIN_MENU;

    // Load scene data into a map
    std::map<Scene, SceneData> sceneData;

    sceneData[Scene::SCENE_1] = {
        LoadTexture("assets/unknofdwn.png"),
        {
            {Rectangle{0, 0, 500, 500}, Scene::SCENE_2, LoadSound("path/to/sound_effect.wav"), false } // Clicking here leads to Scene 2
        }
        // Add other assets and data for scene 1, such as sound effects, animations, etc.
    };

    // Scene 2
    sceneData[Scene::SCENE_2] = {
        LoadTexture("assets/shopping.png"),
        {
            {Rectangle{0, 0, 500, 500}, Scene::MAIN_MENU}, // Clicking here leads back to Main Menu
            // Add other click boxes for scene 2 and their respective target scenes
        }
        // Add other assets and data for scene 2, such as sound effects, animations, etc.
    };

    // Load data for other scenes here

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Input handling
        if (currentScene == Scene::MAIN_MENU) {
            // Handle clicks in the main menu
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Implement logic to check if the user clicked on a button to start the game
                // Example:
                ChangeScene(currentScene, Scene::SCENE_1);
            }
        }
        else {

            // Handle clicks and interactions for other scenes
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                SceneData& currentSceneData = sceneData[currentScene];
                for (const ClickBox& clickBox : currentSceneData.clickBoxes) {
                    if (CheckCollisionPointRec(mousePos, clickBox.bounds)) {

                        
                        // Perform actions related to the clicked box in the current scene
                        // Example:
                        // PlaySound(currentSceneData.sound);
                        // ChangeScene(currentScene, nextScene);
                        // Trigger animations or open minigames here


                    // Play sound effect, if defined for this click box
                            PlaySound(clickBox.soundEffect);

                        // Start the mini-game, if defined for this click box
                        if (clickBox.isMiniGameStart) {
                            StartMiniGame(); 
                        }

                        // Change scene to the target scene defined for this click box
                        ChangeScene(currentScene, clickBox.targetScene);

                        break; // Stop checking if the mouse is clicked in multiple click boxes


                    }
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the appropriate scene based on the currentScene value
        if (currentScene != Scene::MAIN_MENU) {
            SceneData& currentSceneData = sceneData[currentScene];
            DrawTexture(currentSceneData.image, 0, 0, WHITE);
            // Draw sprites in the current scene
            for (const Sprite& sprite : currentSceneData.sprites) {
                DrawTexture(sprite.texture, sprite.position.x, sprite.position.y, WHITE);
            }
        }

        // Draw other UI elements here

        for (const ClickBox& clickBox : sceneData[currentScene].clickBoxes) { // debugging use. to highlight bounds of click boxes
            DrawRectangleRec(clickBox.bounds, Color{ 0, 0, 200, 100 });       // debugging use. to highlight bounds of click boxes
        }

        EndDrawing();
    }

    // Unload any loaded resources here
    for (auto& scene : sceneData) {
        UnloadTexture(scene.second.image);
        // Unload other scene-specific assets
    }

    // De-Initialization
    CloseWindow();

    return 0;
}