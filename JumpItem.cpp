#include "JumpItem.h"

void JumpItem::Initialize(const KamataEngine::Vector3& position, const KamataEngine::Vector3& size, KamataEngine::Model* model) {
	assert(model);
	model_ = model;
	position_ = position;
	size_ = size;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position_;
}

void JumpItem::Update() {
	worldTransform_.translation_ = position_;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void JumpItem::Draw(KamataEngine::Camera* camera) { model_->Draw(worldTransform_, *camera); }

AABB JumpItem::GetAABB() const {
	return AABB{
	    {position_.x - size_.x * 0.5f, position_.y - size_.y * 0.5f, position_.z - size_.z * 0.5f},

	    {position_.x + size_.x * 0.5f, position_.y + size_.y * 0.5f, position_.z + size_.z * 0.5f}
    };
}