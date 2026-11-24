#pragma once

#include"../Component/Component.h"
#include"Entity.h"

#include<queue>
#include<algorithm>

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

		bool is_initialize() const noexcept
		{
			return is_init;
		}

		const char* get_name() const noexcept
		{
			return name_;
		}

	protected:

		bool is_init = false;
		const char* name_{};

	};

	template<typename... Types>
	struct TypeList
	{};

	template<typename Init,typename Update,typename Shutdown>
	struct SystemDependency
	{
		using InitAfter = Init;

		using UpdateAfter = Update;

		using ShutdownAfter = Shutdown;
	};

	template<typename T>
	struct SystemTraits : SystemDependency<
		TypeList<>,
		TypeList<>,
		TypeList<>
		>
	{};

	struct SystemDependencies
	{
		std::vector<SystemID> init_after{};
		std::vector<SystemID> update_after{};
		std::vector<SystemID> shutdown_after{};
	};


	class EntityManager final : public ISystem
	{
	public:

		explicit EntityManager()
		{
			ISystem::name_ = "EntityManager";
		}

		bool init_system(SystemManager& manager) override 
		{ 
			is_init = true;
			return is_init;
		}

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
			if (is_init) { clear_entitys(); }
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
			for (auto& id : shutdown_order)
			{
				auto* system = systems_.at(id).get();

				system->shutdown_system();
				send_log("Shutdown = ", system);
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

			const auto result = systems_.try_emplace(
				id,
				std::move(system)
			).second;
			if (result)
			{
				register_order.push_back(id);
				using Traits = SystemTraits<System>;

				system_dependenies.emplace(
					id,
					SystemDependencies{
						make_system_ids(typename Traits::InitAfter{}),
						make_system_ids(typename Traits::UpdateAfter{}),
						make_system_ids(typename Traits::ShutdownAfter{})
					}
				);
			}
		}

		bool init_systems()
		{
			if (!build_system_order()) {
				return false;
			}

			for (auto& id : init_order)
			{
				auto* system = systems_.at(id).get();

				send_log("Init = ", system);
				if (!system->init_system(*this))
				{
					send_error_log("Init Failed = ", system);
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
			for (auto& id : update_order)
			{
				auto* system = systems_.at(id).get();

				system->update_system();
			}
		}

		void send_update_order() const noexcept
		{
			for (auto& id : update_order)
			{
				auto* system = systems_.at(id).get();
				send_log("Update = ", system);
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

	private:
		template<typename... Systems>
		std::vector<SystemID> make_system_ids(
			TypeList<Systems...>
		)
		{
			return {
				get_system_id<Systems>()...
			};
		}

		template<typename Member>
		bool build_order(
			Member member,
			std::vector<SystemID>& result
		) const
		{
			result.clear();

			std::unordered_map<SystemID, size_t> indegree{};

			std::unordered_map<
				SystemID,
				std::vector<SystemID>
			> graph{};

			// ノードを登録
			for (const auto& id : register_order)
			{
				indegree.emplace(id, 0);
			}

			// 依存関係を構築
			for (const auto& id : register_order)
			{
				const auto it = system_dependenies.find(id);

				if (it == system_dependenies.end())
				{
					return false;
				}

				const auto& dependencies = it->second.*member;

				for (const auto& dependency : dependencies)
				{
					// 自分自身への依存
					if (dependency == id)
					{
						return false;
					}

					// 依存先が未登録
					if (!systems_.contains(dependency))
					{
						return false;
					}

					// dependency -> id
					graph[dependency].push_back(id);

					++indegree[id];
				}
			}

			// 依存先を持たないSystemを登録順に追加
			std::queue<SystemID> ready{};

			for (const auto& id : register_order)
			{
				if (indegree[id] == 0)
				{
					ready.push(id);
				}
			}

			// トポロジカルソート
			while (!ready.empty())
			{
				const auto id = ready.front();
				ready.pop();

				result.push_back(id);

				for (const auto& next : graph[id])
				{
					if (--indegree[next] == 0)
					{
						ready.push(next);
					}
				}
			}

			// 全ノードを処理できなければ循環依存
			return result.size() == register_order.size();
		}

		bool build_system_order()
		{
			std::vector<SystemID> init{};
			std::vector<SystemID> update{};
			std::vector<SystemID> shutdown{};

			if (!build_order(
				&SystemDependencies::init_after,
				init
			))
			{
				return false;
			}

			if (!build_order(
				&SystemDependencies::update_after,
				update
			))
			{
				return false;
			}

			if (!build_order(
				&SystemDependencies::shutdown_after,
				shutdown
			))
			{
				return false;
			}

			//　依存順の反転
			std::ranges::reverse(shutdown);

			// すべて成功した場合のみ反映
			init_order = std::move(init);
			update_order = std::move(update);
			shutdown_order = std::move(shutdown);

			return true;
		}

		void send_log(const char* text, ISystem* system) const noexcept;
		void send_error_log(const char* text, ISystem* system) const noexcept;

		std::unordered_map<SystemID, std::unique_ptr<ISystem>> systems_{};
		std::unordered_map<SystemID, SystemDependencies> system_dependenies{};

		std::vector<SystemID> register_order{};

		std::vector<SystemID> init_order{};
		std::vector<SystemID> update_order{};
		std::vector<SystemID> shutdown_order{};

	};
}
