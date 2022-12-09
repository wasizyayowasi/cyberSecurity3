#pragma once
#include "SceneBase.h"
class ScenePause : public SceneBase
{
public:
    ScenePause(SceneManager& manager);
    virtual ~ScenePause();

    virtual void update(const InputState& input)override;
    void draw();

private:

};

