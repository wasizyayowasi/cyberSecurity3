#pragma once

#include <deque>

class SceneBase;		
class InputState;	

// シーン監視クラス
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

