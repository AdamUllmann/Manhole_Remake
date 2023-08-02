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
    Rectangle originalBounds;
    Scene targetScene;
    Sound soundEffect;
    bool isMiniGameStart;
    Rectangle bounds;
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
    Music song;
    std::vector<Sprite> sprites;
    // more scene-specific data as needed
};

// a function to handle scene transitions
void ChangeScene(Scene& currentScene, Scene nextScene) {
    currentScene = nextScene;
}


void StartMiniGame() {

}

void ResizeTextures(std::map<const Scene, SceneData>& datamap, int newWidth, int newHeight) {
    for (std::pair<const Scene, SceneData>& sceneDataPair : datamap) {      // for each scene in the map 
        SceneData& data = sceneDataPair.second; // get the scene data from the pair

        Image img = LoadImageFromTexture(data.image);   // background texture resize
        ImageResize(&img, newWidth, newHeight);
        UnloadTexture(data.image);
        data.image = LoadTextureFromImage(img);
        UnloadImage(img);

                    // updates click box positions and scales based on the new window size
        for (ClickBox& clickBox : data.clickBoxes) {
            clickBox.bounds.x = clickBox.originalBounds.x * static_cast<float>(newWidth);
            clickBox.bounds.y = clickBox.originalBounds.y * static_cast<float>(newHeight);
            clickBox.bounds.width = clickBox.originalBounds.width * static_cast<float>(newWidth);
            clickBox.bounds.height = clickBox.originalBounds.height * static_cast<float>(newHeight);
        }

                     // updates sprite positions and scales based on the new window size
        for (auto& sprite : data.sprites) {
            sprite.position.x *= static_cast<float>(newWidth);
            sprite.position.y *= static_cast<float>(newHeight);
            // add scaling code
        }
    }
}


int main(void)
{
    // initialization
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "MANHOLE");
    ToggleFullscreen();
    InitAudioDevice();
    SetTargetFPS(60);
    SetMouseCursor(3);
    Image img = LoadImage("assets/ICON.png");
    SetWindowIcon(img);
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    Scene currentScene = Scene::MAIN_MENU;

    std::map<const Scene, SceneData> sceneData;     // all scene data is loaded into a map

    // Scene 1
    sceneData[Scene::SCENE_1] = {
        LoadTexture("assets/testRenders/first.png"),
        {
            { 
                Rectangle{ 0.1, 0.1, 0.2, 0.2 }, // defines click boxes
                Scene::SCENE_2,                         //  clicking here leads to a target scene
                LoadSound("path/to/sound_effect.wav"),  //  clicking here plays a sound
                false                                   //  is it a minigame scene?
            }
        }
        // add other assets and data for scene 1, such as sound effects, animations, etc.
    };

    // Scene 2
    sceneData[Scene::SCENE_2] = {
        LoadTexture("assets/testRenders/03.png"),
        {
            {
                Rectangle{ 0.1, 0.1, 0.2, 0.2 }, // defines click boxes
                Scene::MAIN_MENU,                         //  clicking here leads to a target scene
                LoadSound("path/to/sound_effect.wav"),  //  clicking here plays a sound
                false                                   //  is it a minigame scene?
            }
        }
        // Add other assets and data for scene 2, such as sound effects, animations, etc.
    };

    // Load data for other scenes here



    ResizeTextures(sceneData, screenWidth, screenHeight);           // initial scaling

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Input handling
        if (currentScene == Scene::MAIN_MENU) {
            // handle clicks in the main menu
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // implement logic to check if the user clicked on a button to start the game
                ChangeScene(currentScene, Scene::SCENE_1);
            }
        }
        else {

            // handle clicks and interactions for other scenes
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                SceneData& currentSceneData = sceneData[currentScene];
                for (const ClickBox& clickBox : currentSceneData.clickBoxes) {
                    if (CheckCollisionPointRec(mousePos, clickBox.bounds)) {

                        
                        // perform actions related to the clicked box in the current scene
                        // playSound(currentSceneData.sound);
                        // changeScene(currentScene, nextScene);
                        // trigger animations or open minigames here


                    // play sound effect, if defined for this click box
                            PlaySound(clickBox.soundEffect);

                        // start the mini-game, if defined for this click box
                        if (clickBox.isMiniGameStart) {
                            StartMiniGame(); 
                        }

                        // change scene to the target scene defined for this click box
                        ChangeScene(currentScene, clickBox.targetScene);

                        break; // stop checking if the mouse is clicked in multiple click boxes


                    }
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            screenWidth = 900;
            screenHeight = 600;
            ToggleFullscreen();
            SetWindowSize(screenWidth, screenHeight);
            SetWindowPosition(25, 45);
            ResizeTextures(sceneData, screenWidth, screenHeight);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draws appropriate scene based on the currentScene value
        if (currentScene != Scene::MAIN_MENU) {
            SceneData& currentSceneData = sceneData[currentScene];
            DrawTexture(currentSceneData.image, 0, 0, WHITE);
            // Draw sprites in the current scene
            for (const Sprite& sprite : currentSceneData.sprites) {
                DrawTexture(sprite.texture, sprite.position.x, sprite.position.y, WHITE);
            }
        }

        // misc ui elements go here

        for (const ClickBox& clickBox : sceneData[currentScene].clickBoxes) { // debugging use. to highlight bounds of click boxes
            DrawRectangleRec(clickBox.bounds, Color{ 250, 0, 0, 80 });       // debugging use. to highlight bounds of click boxes
        }

        EndDrawing();
    }
    for (auto& scene : sceneData) {             // unload & deallocate
        UnloadTexture(scene.second.image);
        // unload other scene-specific assets here
    }

    // de-initialization & end
    CloseWindow();

    return 0;
}