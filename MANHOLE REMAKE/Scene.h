#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <vector>

#include "raylib.h"

class Scene
{
public:
    Scene(const std::string& sceneName, const std::string& imagePath);
    virtual ~Scene();

    void AddClickableBox(const Rectangle& box, const std::string& targetSceneName);
    void AddActionBox(const Rectangle& box, void (*action)());

    void Update();
    void Draw();

private:
    std::string sceneName;
    Texture2D sceneImage;
    std::vector<Rectangle> clickableBoxes;
    std::vector<std::string> targetSceneNames;
    std::vector<void (*)()> actions;
};

#endif