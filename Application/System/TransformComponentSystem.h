#pragma once

#include"System.h"
#include"Entity.h"
#include"../Component/ComponentManager.h"

namespace App
{

	struct Transform
	{
		float  posiztion_[3] = {};
	};

	class TransformComponent final : public IComponent
	{
	public:

		explicit TransformComponent(
			const ComponentUniqueID& id,
			Transform* transform,
			RemoveFunc func = {}
		) :
			transform_{ transform },
			IComponent{ id,func }
		{
		};

		Transform* get_transform() const noexcept
		{
			return transform_;
		}

		Transform* operator -> () const noexcept
		{
			return transform_;
		}

	private:

		Transform* transform_{};

	};


	class TransfromSystem final : public ISystem
	{
	public:

		bool init_system(SystemManager& manager) override
		{
			manager_ = manager.get_system<EntityManager>();
			return manager_;
		}

		void update_system() override
		{

		}

		template<typename Component>
		std::unique_ptr<Component> create_component()
		{
			if constexpr (std::is_same_v<Component, TransformComponent>)
			{
				auto transform = std::make_unique<Transform>();

				auto component = components_.create_component(transform.get());
				if (component)
				{
					transforms_.emplace(
						component->get_unique_id(),
						std::move(transform)
					);
				}

				return component;
			}
			else
			{
				return nullptr;
			}
		}

		void unlink_component(ComponentUniqueID id)
		{
			components_.unlink_component(id);
			if (transforms_.contains(id))
			{
				transforms_.erase(id);
			}
		}

		void shutdown_system() override
		{
			if (manager_)
			{
				if (manager_->has_entitys())
				{
					manager_->remove_component_to_all<TransformComponent>();
				}
			}
		}

	private:

		EntityManager* manager_{};

		ComponentManager<TransformComponent, Transform> components_{};
		std::unordered_map<ComponentUniqueID, std::unique_ptr<Transform>> transforms_{};

	};


	template<>
	struct ComponentTraits<TransformComponent>
	{
		using System = TransfromSystem;
	};
}