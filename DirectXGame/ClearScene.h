#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class ClearScene {

public:
	~ClearScene();

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

	bool IsGameFinished() const { return isGameFinished_; }

private:
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	bool isGameFinished_ = false; // ゲーム終了フラグ

	uint32_t textureHandle_ = 0;
	Sprite* clearSprite_ = nullptr; // タイトル画面の画像
};