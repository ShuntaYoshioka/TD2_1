#include "Fade.h"
#include <algorithm>

using namespace KamataEngine;

void Fade::Initialize() {
	// テクスチャ読み込み
	textureHandle_ = KamataEngine::TextureManager::Load("white1x1.png");
	// スプライト
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	sprite_->SetSize(Vector2(1280, 720));
	sprite_->SetColor(Vector4(0, 0, 0, 1));
}

void Fade::Update() {

	switch (status_) {
	case Status::None:
		// 何もしない
		break;
	case Status::FadeIn:
		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		sprite_->SetColor(Vector4(0, 0, 0, 1.0f - std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	case Status::FadeOut:
		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	}
}

void Fade::Draw() {

	if (status_ == Status::None) {
		return;
	}

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}

void Fade::Start(Status status, float duration) {

	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop() { status_ = Status::None; }

bool Fade::isFinished() const {

	switch (status_) {
	case Status::FadeIn:
	case Status::FadeOut:
		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}
