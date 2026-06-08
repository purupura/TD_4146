#include "Ball.h"

Ball::Ball() {
    // コンストラクタ
}

Ball::~Ball() {
    // デストラクタ
}

void Ball::Initialize()
{
    // 1. ワールド変換の初期化と定数バッファの生成
    worldTransform_.Initialize();
    worldTransform_.CreateConstBuffer();
    worldTransform_.Map();

    // 2. ボールの初期位置を設定 (画面手前の地面付近)
    worldTransform_.translation_ = { 0.0f, 0.0f, 10.0f };

    // 3. 発射速度（パワー）を設定
    // X: 0 (まっすぐ) / Y: 15.0 (上方向) / Z: -20.0 (奥方向)
    // ※エンジンの座標系（右高左低、奥がプラスかマイナスか）に合わせて数値を調整してください
    velocity_ = { 0.0f, 15.0f, -20.0f };

    // 4. 重力の設定 (毎フレームY速度を少しずつ下げる)
    gravity_ = -0.5f;

    // 初回の行列転送
    worldTransform_.TransferMatrix();
}

void Ball::Update()
{
    // ① 速度の分だけ、位置（translation_）を移動させる
    worldTransform_.translation_.x += velocity_.x;
    worldTransform_.translation_.y += velocity_.y;
    worldTransform_.translation_.z += velocity_.z;

    // ② Y方向の速度に重力を加算する（放物線を描かせる）
    velocity_.y += gravity_;

    // ③ 地面（Y=0）に着地したときのバウンド処理
    if (worldTransform_.translation_.y < 0.0f)
    {
        worldTransform_.translation_.y = 0.0f; // 地面にめり込まないように固定
        velocity_.y = -velocity_.y * 0.6f;     // 60%の力で跳ね返る

        // 完全に勢いがなくなったら摩擦で止める
        if (velocity_.y < 0.1f) {
            velocity_ = { 0.0f, 0.0f, 0.0f };
        }
    }

    // ④ 【最重要】位置が変わったので、行列を再計算してGPUへ転送する
    // ※エンジン内に「matWorld_」を計算する UpdateMatrix() のような関数があれば、
    // 先にそれを呼んでから TransferMatrix() を呼び出します。
    // もし Initialize() 内の処理で自動的に計算される仕様であれば、以下のように転送を呼びます。
    
    // worldTransform_.UpdateMatrix(); // もしあれば呼び出す
    worldTransform_.TransferMatrix();   // 定数バッファ（matWorld）を更新
}

void Ball::Draw()
{
    // 前述のDraw処理
    if (model_ && Ballcamera_) {
        model_->Draw(worldTransform_, *Ballcamera_);
    }
}