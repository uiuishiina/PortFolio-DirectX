#pragma once

/* ========== Includeファイル ========== */
#include"../Component/ComponentBase.h"
#include"Container/UniqueptrKeyMap.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	using EntityID = std::uint64_t;

	struct ComponentKey : public HandyItems::container::handle::LogicalKey {

		ComponentKey() = default;

		explicit ComponentKey(ComponentID id) :
			HandyItems::container::handle::LogicalKey{
			static_cast<std::uint32_t>(id)
		} {}
	};

	struct ComponentEncodeKey : public HandyItems::container::handle::EncodedKey {};

	class Entity : HandyItems::others::NonCopyableBase
	{
	public:

		Entity(
			EntityID id
		) :
			id_{ id } {};

		template<typename T,typename... Args> 
		requires std::derived_from<T, ComponentBase>
		bool add_component(Args... args) {

			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			return components_.add_value(
				ComponentKey{ component->get_type_id() },
				std::move(component)
			);
		}

		template<typename T>
		T* get_component() const noexcept {
			
			auto* component = components_.get_unique(
				ComponentKey{ HandyItems::id::get_id::get_type_id<T>() }
			);
			
			return component ? static_cast<T*>(component) : nullptr;
		}

		[[nodiscard]] EntityID get_id() const noexcept {
			return id_;
		}

		void set_active(bool flag) {
			is_active = flag;
		}

		[[nodiscard]] bool get_active() const noexcept {
			return is_active;
		}

	private:
		EntityID id_{};

		bool is_active = true;

		HandyItems::container::UniqueptrKeyMap<ComponentKey,ComponentEncodeKey,ComponentBase> components_{};

	};
}