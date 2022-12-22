#pragma once

#include <deque>

class SceneBase;		
class InputState;	

// �V�[���Ď��N���X
class SceneManager
{
private:
	std::deque<SceneBase*> scenes_;
public:
	
	void changeScene(SceneBase* scene);

	void pushScene(SceneBase* scene);		
	
	void popScene();

	void update(const InputState& input);
	
	void draw();
};

