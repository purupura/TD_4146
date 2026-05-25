#include "GameScene.h"
GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();
	//==============================================================
	// カメラ生成
	//==============================================================
	camera_ = new Camera();
	camera_->Initialize();

	//==============================================================
	// スプライト生成
	//==============================================================

	//==============================================================
	// モデル読み込み
	//==============================================================

	//==============================================================

	// オブジェクト生成
	//==============================================================

	//==============================================================
}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isFinished_ = true;
	}

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
//==============================================================
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	///

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
	//==============================================================

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw();

	/// <summary>
	/// ここにモデルの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

//==============================================================
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	// TestSprite_->Draw();

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
	//==============================================================
}
