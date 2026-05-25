#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene {
public:
	/// <summary>
	/// デストクラタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Camera* camera_ = nullptr;

	// モデル
	Model* model = nullptr;

	bool isFinished_ = false;
};
