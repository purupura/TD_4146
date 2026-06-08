#pragma once
#include <KamataEngine.h>
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "3d/Camera.h"
#include "3d/ObjectColor.h"
#include <3d/Object3d.h>

using namespace KamataEngine;

class Ball
{
public:
    Ball();
    ~Ball();

    void Initialize();
    void Update();
    void Draw();

public:
    // 外部からモデルとカメラを受け取るための関数
    void SetModel(Model* model) { model_ = model; }
    void SetCamera(Camera* camera) { Ballcamera_ = camera; }

private:
    // 1. 【エンジンの機能】位置や回転を管理するクラス
    KamataEngine::WorldTransform worldTransform_;

    // 2. 【あなたのボール専用】見た目とカメラのポインタをここに宣言する！
    // (※クラス名「Model」「Camera」はお使いのエンジンの実際の名称に合わせてください)
    Model* model_ = nullptr;
    Camera* Ballcamera_ = nullptr;

    // 3. 【物理演算用】ボールを飛ばすための変数
    KamataEngine::Vector3 velocity_; // 速度 (vx, vy, vz)
    float gravity_;                 // 重力
};