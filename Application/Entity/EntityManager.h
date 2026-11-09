#pragma once

/* ========== Includeファイル ========== */

#include"Entity.h"
#include"Container/UniqueptrKeyMap.h"

#include<string>

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	struct EntityKey : public HandyItems::container::handle::LogicalKey {

		EntityKey() = default;

		explicit EntityKey(EntityID id) :
			HandyItems::container::handle::LogicalKey{
			static_cast<std::uint32_t>(id)
		} {}
	};

	struct EntityEncodedKey : public HandyItems::container::handle::EncodedKey {};


	class EntityManager final : HandyItems::others::NonCopyableBase
	{
	public:

		[[nodiscard]] EntityID create_entity(
			const std::string& name
		) {

			auto id = ++next_id;
			if (!entity_container.add_value(
				EntityKey{ id },
				std::make_unique<Entity>(id)
			)) {
				return 0;
			}
			return id;
		}

		[[nodiscard]] Entity* get_entity(
			const EntityID& id
		) {
			return entity_container.get_unique(EntityKey{ id });
		}

	private:

		HandyItems::container::UniqueptrKeyMap<EntityKey, EntityEncodedKey, Entity> entity_container{};

		EntityID next_id{};

	};
}