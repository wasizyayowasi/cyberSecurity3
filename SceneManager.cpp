#include "SceneManager.h"
#include "SceneBase.h"

void SceneManager::changeScene(SceneBase* scene)
{
	//シーンスタックが空ではなかったら...
	if (!scenes_.empty())
	{
		//一番上の中身を消して、中身の入っていた器を消す
		delete scenes_.front();		//topはてっぺんの要素を返してる
		scenes_.pop_front();				//一個減る→ふつうは0になる
	}
	scenes_.push_front(scene);			//一個増える
}

void SceneManager::pushScene(SceneBase* scene)
{
	scenes_.push_front(scene);//一個増える
}

void SceneManager::popScene()
{
	if (scenes_.size() > 1) {
		//ポップの結果、シーンが０にならないようにする
		delete scenes_.front();
		scenes_.pop_front();
	}
}

void SceneManager::update(const InputState& input)
{
	scenes_.front()->update(input);
}

void SceneManager::draw()
{
	for (int i = scenes_.size() - 1; i >= 0; --i) {
		scenes_[i]->draw();
	}
}