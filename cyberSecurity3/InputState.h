#pragma once

#include <map>
#include <vector>
#include <string>

enum class InputType
{
	next,			/// 次へ行くボタン
	prev,			/// 前に戻るボタン
	pause,			/// ポーズボタン
	keyconf,		/// キーコンフィグ
	change,			///変更
	up,				///上
	down,			///下
	max				///最大入力インデックス
};

/// <summary>
/// 入力装置カテゴリ
/// </summary>
enum class InputCategory {
	keybd,		//キーボード
	pad,		//ゲームパッド
	mouse,		//マウス
};

/// <summary>
/// 入力情報
/// </summary>
struct InputInfo {
	InputCategory cat;	//入力装置カテゴリ
	int id;				//入力ID(KEY_INPUT_～,PAD_INPUT_～,MOUSE_INPUT_～)
};

class KeyConfigScene;

/// <summary>
/// 入力状態を管理する
/// </summary>
class InputState
{
	friend KeyConfigScene;//KeyConfigSceneにだけ、すべてを見せる。
public:

	InputState();

	/// <summary>
	/// 押した瞬間にtrueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押した瞬間ならtrue,それ以外ならfalse</returns>
	bool isTriggered(InputType type) const;

	/// <summary>
	/// 押されてたらtrueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押されてたらtrue, 押されてないならfalse</returns>
	bool isPressed(InputType type) const;

	/// <summary>
	/// 入力情報を更新する
	/// (注意)毎フレームUpdateを呼ばないと入力状態は
	/// 更新されません。
	/// </summary>
	void update();

	/// <summary>
	/// 入力情報を更新する
	/// </summary>
	/// <param name="type">ゲームのおける入力種別</param>
	/// <param name="cat">入力カテゴリ(kyebd等)</param>
	/// <param name="id">実際の入力</param>
	void rewriteInputInfo(InputType type, InputCategory cat, int id);

private:

	std::map<InputType, std::vector<InputInfo> > inputMapTable_;//実際の入力とゲームボタンの対応テーブル

	//入力タイプとその名前の対ぴテーブル
	std::map<InputType, std::string> inputNameTable_;

	std::vector<bool> currentInput_;	//現在の入力情報(押しているか押していないか)
	std::vector<bool> lastInput_;		//直前の入力情報(直前押しているか押していないか)

	//int keypadState;			// キーパッド状態
	//int lastKeypadState;		// 直前のキーパッド状態
	//char keystate[256];			// キーボード状態
	//char lastKeystate[256];		// 直前のキーボード状態

};
