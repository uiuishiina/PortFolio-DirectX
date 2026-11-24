#pragma once

#include"System.h"
#include"DebugSystem.h"
#include"WindowsSystem.h"
#include"../Component/ComponentManager.h"
#include"Math/BaseStruct/Transform.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	struct CoreContext;
	struct ContainerContext;

	namespace ClassModule
	{
		namespace DescriptorGroup
		{
			template<typename T>
			class ConstantBufferGroup;
		}
	}
}

namespace App
{
	class IRendererPipeline
	{
	public:

		virtual ~IRendererPipeline() = default;

		virtual bool init_pipeline(
			DirectX::CoreContext*,
			DirectX::ContainerContext*
		) = 0;

		virtual void execute_pipeline() = 0;

	};

	class RendererComponent final : public IComponent
	{
	public:

		explicit RendererComponent(
			const ComponentUniqueID& id,
			Entity* entity,
			RemoveFunc func = {}
		) :
			entity_{ entity },
			IComponent{ id,func }
		{}

		Entity* get_target_entity() const noexcept
		{
			return entity_;
		}

	private:
		Entity* entity_{};

	};


	class TransformItem
	{
	public:
		using Transform = HandyItems::Math::Transform;
		using transform_buffer = DirectX::ClassModule::DescriptorGroup::ConstantBufferGroup<HandyItems::Math::Matrix>;

		TransformItem();
		~TransformItem();

		bool create_transform_item(
			DirectX::CoreContext*,
			DirectX::ContainerContext*
		);

		Transform& get_transform() noexcept
		{
			return transform_;
		}

		transform_buffer* get_buffer() const noexcept;

		void update_buffer();

	private:

		Transform transform_{};
		Transform previous_transform{};
		std::unique_ptr<transform_buffer> buffer_;

		uint32_t index_size{};
		uint32_t dirty_size{};
	};

	class TransformComponent final : public IComponent
	{
	public:
		
		explicit TransformComponent(
			const ComponentUniqueID& id,
			TransformItem::Transform* transform,
			RemoveFunc func = {}
		) :
			transform_{ transform },
			IComponent{ id,func }
		{};

		TransformItem::Transform* get_transform() noexcept
		{
			return transform_;
		}

		TransformItem::Transform* operator -> () noexcept
		{
			return transform_;
		}

	private:

		using IComponent::get_active;
		using IComponent::set_active;

		TransformItem::Transform* transform_;
	};

	class RendererSystem final : public ISystem
	{
	public:

		RendererSystem();
		~RendererSystem();

		template<typename pipeline>
		void add_pipeline()
		{
			pipelines_.push_back(
				std::make_unique<pipeline>()
			);
		}

		bool init_system(SystemManager& manager) override;

		void update_system() override;

		void shutdown_system() override;

		template<typename Component,typename... Args>
		std::unique_ptr<Component> create_component(
			Args&&... args
		)
		{
			if constexpr (std::is_same_v<Component, RendererComponent>)
			{
				auto component = target_components.create_component(std::forward<Args>(args)...);
				target_chasu = target_components.get_datas();
			}
			else if constexpr (std::is_same_v<Component, TransformComponent>)
			{
				auto transform = std::make_unique<TransformItem>();
				if (!transform->create_transform_item(
					core_context.get(),
					container_context.get()
				))
				{
					return nullptr;
				}

				auto component = transform_components.create_component(transform->get_transform());
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

		template<typename Component>
		void unlink_component(ComponentUniqueID id)
		{
			if constexpr (std::is_same_v<Component, RendererComponent>)
			{
				target_components.unlink_component(id);
				target_chasu = target_components.get_datas();
			}
			else if constexpr (std::is_same_v<Component, TransformComponent>)
			{
				transform_components.unlink_component(id);
				if (transforms_.contains(id))
				{
					transforms_.erase(id);
				}
			}
			
		}

	private:

		EntityManager* entity_{};
		WindowsSystem* main_window{};
		DebugSystem* debug_{};

		std::unique_ptr<DirectX::ContainerContext> container_context{};
		std::unique_ptr<DirectX::CoreContext> core_context{};

		std::vector<std::unique_ptr<IRendererPipeline>> pipelines_{};

		ComponentManager<RendererComponent, Entity> target_components{};
		std::vector<Entity*> target_chasu{};

		ComponentManager<TransformComponent, TransformItem::Transform> transform_components{};
		std::unordered_map<ComponentUniqueID, std::unique_ptr<TransformItem>> transforms_{};
	};

	template<>
	struct ComponentTraits<TransformComponent>
	{
		using System = RendererSystem;
	};
}