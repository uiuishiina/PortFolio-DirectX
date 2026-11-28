#pragma once
#include"System/Entity.h"
#include"System/InputSystem.h"
#include"System/RendererSystem.h"

namespace App
{
	class Player final : public Entity
	{
		using Vector3 = HandyItems::Math::Float3;
	public:
		using Entity::Entity;

		void start() override
		{
			if (
				auto* p = get_component<InputComponent>();
				p
				)
			{
				input_ = p;
			}
			if (
				auto* p = get_component<TransformComponent>();
				p
				)
			{
				transform_ = p;
			}
		}

		void update() override
		{
			if (!transform_)
			{
				return;
			}
			if (input_)
			{
				Vector3 move{};

				if (input_->get_action_state(
					InputAction::MoveRight
				) == ActionState::Hold)
				{
					move.x_ = speed_;
				}
				else if (input_->get_action_state(
					InputAction::MoveLeft
				) == ActionState::Hold)
				{
					move.x_ = -speed_;
				}

				if (input_->get_action_state(
					InputAction::MoveUp
				) == ActionState::Hold)
				{
					move.y_ = speed_;
				}
				else if (input_->get_action_state(
					InputAction::MoveDown
				) == ActionState::Hold)
				{
					move.y_ = -speed_;
				}

				if (input_->get_action_state(
					InputAction::keyO
				) == ActionState::Hold)
				{
					move.z_ = speed_;
				}
				else if (input_->get_action_state(
					InputAction::keyP
				) == ActionState::Hold)
				{
					move.z_ = -speed_;
				}

				transform_->get_transform().translate_world(
					move
				);
			}
		}

		void ondestroy() override
		{

		}

	private:

		float speed_ = 0.05f;

		InputComponent* input_{};
		TransformComponent* transform_{};

	};
}