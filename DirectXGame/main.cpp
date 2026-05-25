#include "ClearScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <KamataEngine.h>
#include <Windows.h>

using namespace KamataEngine;

enum class Scene {

	kUnknown = 0,

	kTitle, // タイトルシーン
	kGame,  // ゲームシーン
	kClear
};

void ChangeScene();
void UpdateScene();
void DrawScene();

// ゲームシーン
GameScene* gameScene = nullptr;

TitleScene* titleScene = nullptr; // タイトルシーンのポインタ

// クリアシーン
ClearScene* clearScene = nullptr; // クリアシーンのポインタ

Scene scene = Scene::kUnknown; // 現在のシーンを表す変数

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"TD_4146");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize();

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize();

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize();
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();

	gameScene = new GameScene();
	gameScene->Initialize();

#pragma endregion

	// タイトルシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	// クリアシーンの初期化
	clearScene = new ClearScene();
	clearScene->Initialize();

	// シーンをタイトルシーンに設定
	scene = Scene::kTitle;
	// scene = Scene::kGameScene;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		// シーンの更新と切り替え
		UpdateScene();
		ChangeScene();

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// シーンの描画
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	delete gameScene;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;

	case Scene::kGame:
		gameScene->Update();
		break;

	case Scene::kClear:
		clearScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;

	case Scene::kGame:
		gameScene->Draw();
		break;

	case Scene::kClear:
		clearScene->Draw();
		break;
	}
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene && titleScene->IsFinished()) {
			delete titleScene;
			titleScene = nullptr;
			scene = Scene::kGame;
			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;

	case Scene::kGame:
		if (gameScene && gameScene->IsFinished()) {
			delete gameScene;
			gameScene = nullptr;
			scene = Scene::kClear;
			clearScene = new ClearScene();
			clearScene->Initialize();
		}
		break;
	case Scene::kClear:
		if (clearScene && clearScene->IsGameFinished()) {
			delete clearScene;
			clearScene = nullptr;
			scene = Scene::kTitle;
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	}
}