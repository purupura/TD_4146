#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class TitleScene {

public:
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	bool isFinished_ = false; // ゲーム終了フラグ

	uint32_t textureHandle_ = 0;
	Sprite* titleSprite_ = nullptr; // タイトル画面の画像
};