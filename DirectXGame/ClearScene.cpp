#include "ClearScene.h"
ClearScene::~ClearScene() { delete clearSprite_; }

void ClearScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("debugfont.png");
	clearSprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void ClearScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		isGameFinished_ = true;
	}
}

void ClearScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());
	clearSprite_->Draw();

	Sprite::PostDraw();
}