#include "Scene.h"

Scene::Scene(const std::string& sceneName, const std::string& imagePath)
{
    this->sceneName = sceneName;
    this->sceneImage = LoadTexture(imagePath.c_str());
}

Scene::~Scene()
{
    UnloadTexture(sceneImage);
}

void Scene::AddClickableBox(const Rectangle& box, const std::string& targetSceneName)
{
    clickableBoxes.push_back(box);
    targetSceneNames.push_back(targetSceneName);
    actions.push_back(nullptr);
}

void Scene::AddActionBox(const Rectangle& box, void (*action)())
{
    clickableBoxes.push_back(box);
    targetSceneNames.emplace_back("");
    actions.push_back(action);
}

void Scene::Update()
{
    Vector2 mousePosition = GetMousePosition();

    for (size_t i = 0; i < clickableBoxes.size(); ++i)
    {
        if (CheckCollisionPointRec(mousePosition, clickableBoxes[i]))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (!targetSceneNames[i].empty())
                {
                    // Transition to the target scene if it's specified
                    // For simplicity, we assume that all scenes are preloaded.
                    // You can add more sophisticated scene loading mechanisms.
                    // For example, using a map to store preloaded scenes and loading them on demand.
                    // Here, we'll assume all scenes are loaded before the game starts.
                    // LoadScene(targetSceneNames[i]);
                }
                else if (actions[i] != nullptr)
                {
                    // Execute the associated action
                    actions[i]();
                }
            }
        }
    }
}

void Scene::Draw()
{
    DrawTexture(sceneImage, 0, 0, WHITE);
}