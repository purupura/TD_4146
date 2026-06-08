#include "GameScene.h"


GameScene::~GameScene() {
    // ★解放処理（忘れるとメモリリークします）
    delete ball_;
    delete ballModel_;
    delete camera_;
}

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
    // ★ボール用の3Dモデル（仮に球体のモデル obj ファイルなど）を読み込みます
    // ※エンジンの仕様に合わせてファイルパスや読み込み関数名を調整してください
    ballModel_ = Model::CreateFromOBJ("sphere", true); 

	//==============================================================
	// オブジェクト生成
	//==============================================================
    // ★ボールのインスタンスを生成して初期化
    ball_ = new Ball();
    
    // 【重要】Ballクラス側に model_ や Ballcamera_ をセットする関数がない場合は、
    // Ballクラスに「SetModel(ballModel_)」や「SetCamera(camera_)」のような
    // 橋渡し用の関数を作って、ここでポインタを渡してあげる必要があります。
    // 例：
    ball_->SetModel(ballModel_);
    ball_->SetCamera(camera_);

    ball_->Initialize();
	//==============================================================
}

void GameScene::Update() {
    // ★ボールの移動や物理演算を毎フレーム実行する
    if (ball_) {
        ball_->Update();
    }

    // スペースキーが押されたら「再発射」させたい場合
    if (input_->TriggerKey(DIK_SPACE)) {
        // 現在、スペースを押すと isFinished_ = true になっていますが、
        // テストとしてボールをリセットして再発射させるなら以下のように書けます
        ball_->Initialize(); 
    }
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
//==============================================================
#pragma region 背景スプライト描画
	KamataEngine::Sprite::PreDraw(commandList);
	KamataEngine::Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();
	//==============================================================

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw();

	/// <summary>
	/// ここにモデルの描画処理を追加できる
	/// </summary>
    // ★ここでボールの描画を呼び出す！
    if (ball_) {
        ball_->Draw();
    }

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

//==============================================================
#pragma region 前景スプライト描画
	KamataEngine::Sprite::PreDraw(commandList);
	KamataEngine::Sprite::PostDraw();
#pragma endregion
	//==============================================================
}
