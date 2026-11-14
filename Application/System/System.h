#pragma once

#include"../Component/Component.h"
#include"Entity.h"

namespace App
{

	using SystemID = std::uint64_t;

	template<typename T>
	SystemID get_system_id()
	{
		return static_cast<SystemID>(
			typeid(T).hash_code()
			);
	}

	class SystemManager;

	class ISystem : HandyItems::others::NonCopyableBase
	{
	public:

		virtual ~ISystem() = default;

		virtual bool init_system(SystemManager& manager) = 0;

		virtual void update_system() = 0;

		virtual void shutdown_system() = 0;

	};

	class EntityManager final : public ISystem
	{
	public:

		bool init_system(SystemManager& manager) override { return true; }

		Entity* create_entity(
			const std::string& name
		)
		{
			const auto id = ++next_id;
			auto entity = std::make_unique<Entity>(
				id,
				name
			);

			if (entitys_.try_emplace(
				id,
				std::move(entity)
			).second)
			{
				entity_names.emplace(
					name,
					id
				);
				return entitys_[id].get();
			}

			return nullptr;
		}

		Entity* get_entity(
			const EntityID& id
		)
		{
			const auto it = entitys_.find(id);
			return it != entitys_.end() ? it->second.get() : nullptr;
		}

		Entity* get_entity(
			const EntityName& name
		)
		{
			return get_entity(
				get_id_to_name(name)
			);
		}

		void delete_entity(
			const EntityID& id
		)
		{
			if (entitys_.contains(id))
			{
				entitys_.erase(id);
			}
		}

		void delete_entity(
			const EntityName& name
		)
		{
			delete_entity(
				get_id_to_name(name)
			);
		}

		template<typename Component>
		void remove_component_to_all()
		{
			for (auto& [id, entity] : entitys_)
			{
				entity->remove_component<Component>();
			}
		}

		void update_system() override
		{
			for (auto& [id, entity] : entitys_)
			{
				entity->update();
			}
		}

		void clear_entitys()
		{
			entitys_.clear();
		}

		void shutdown_system() override
		{
			clear_entitys();
		}

		bool has_entitys() const noexcept
		{
			return !entitys_.empty();
		}

	private:

		EntityID get_id_to_name(
			const EntityName& name
		)
		{
			return entity_names.contains(name) ?
				entity_names[name] : 0;
		}

		EntityID next_id{};

		std::unordered_map<EntityName, EntityID> entity_names{};
		std::unordered_map<EntityID, std::unique_ptr<Entity>> entitys_{};

	};

	class SystemManager final
	{
	public:

		~SystemManager()
		{
			auto* entity_manager = get_system<EntityManager>();
			if (entity_manager)
			{
				entity_manager->shutdown_system();
			}

			for (auto& [id, system] : systems_)
			{
				system->shutdown_system();
			}
		}

		template<typename... Systems>
		void register_systems()
		{
			(register_system<Systems>(), ...);
		}

		template<typename System,typename... Args>
		void register_system(
			Args&&... args
		)
		{
			auto system = std::make_unique<System>(std::forward<Args>(args)...);

			const auto id = get_system_id<System>();

			systems_.try_emplace(
				id,
				std::move(system)
			);
		}

		bool init_systems()
		{
			for (auto& [id, system] : systems_)
			{
				if (!system->init_system(*this))
				{
					return false;
				}
			}
			return true;
		}

		template<typename System>
		System* get_system() const noexcept
		{
			const auto it = systems_.find(
				get_system_id<System>()
			);
			if (it == systems_.end())
			{
				return nullptr;
			}
			return static_cast<System*>(
				it->second.get()
				);
		}

		void update_system()
		{
			for (auto& [id, system] : systems_)
			{
				system->update_system();
			}
		}

		template<typename Component, typename... Args>
		std::unique_ptr<Component> create_component(
			Args&&... args
		)
		{
			using System = ComponentTraits<Component>::System;

			auto* system = get_system<System>();

			if (!system)
			{
				return nullptr;
			}

			return system->create_component<Component>(std::forward<Args>(args)...);
		}

		std::unordered_map<SystemID, std::unique_ptr<ISystem>> systems_{};

	};


}
