#include "SceneManager.h"
#include "SceneBase.h"

void SceneManager::changeScene(SceneBase* scene)
{
	//�V�[���X�^�b�N����ł͂Ȃ�������...
	if (!scenes_.empty())
	{
		//��ԏ�̒��g�������āA���g�̓����Ă����������
		delete scenes_.front();		//top�͂Ă��؂�̗v�f��Ԃ��Ă�
		scenes_.pop_front();				//����遨�ӂ���0�ɂȂ�
	}
	scenes_.push_front(scene);			//�������
}

void SceneManager::pushScene(SceneBase* scene)
{
	scenes_.push_front(scene);//�������
}

void SceneManager::popScene()
{
	if (scenes_.size() > 1) {
		//�|�b�v�̌��ʁA�V�[�����O�ɂȂ�Ȃ��悤�ɂ���
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