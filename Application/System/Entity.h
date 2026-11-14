#pragma once

#include<string>
#include<cstdint>
#include<unordered_map>
#include<memory>

#include"../Component/Component.h"

namespace App
{

	using EntityID = std::uint64_t;
	using EntityName = std::string;

	class Entity : HandyItems::others::NonCopyableBase
	{
	public:

		explicit Entity(
			const EntityID& id,
			const EntityName& name
		) :
			id_{ id },
			name_{ name }
		{

		};

		template<typename Component>
		bool add_component(
			std::unique_ptr<Component> component
		)
		{
			if (!component)
			{
				return false;
			}

			const auto id = get_component_id<Component>();

			if (components_.contains(id))
			{
				return false;
			}

			components_.emplace(
				id,
				std::move(component)
			);

			return true;
		}

		template<typename Component>
		Component* get_component()
		{
			const auto it = components_.find(get_component_id<Component>());

			if (it == components_.end())
			{
				return nullptr;
			}

			return static_cast<Component*>(
				it->second.get()
				);
		}

		template<typename Component>
		void remove_component()
		{
			const auto id = get_component_id<Component>();
			const auto it = components_.find(id);

			if (it != components_.end())
			{
				components_.erase(id);
			}
		}

		virtual void update() {}

		EntityID get_id() const noexcept
		{
			return id_;
		}

		EntityName get_name() const noexcept
		{
			return name_;
		}

	private:

		EntityID id_{};

		EntityName name_{};

		std::unordered_map<ComponentID, std::unique_ptr<IComponent>> components_{};

	};
}