#pragma once

#include"Component.h"

namespace App
{

	template<typename Component, typename Data>
	class ComponentManager final
	{
	public:

		std::unique_ptr<Component> create_component(
			Data* data
		)
		{
			const auto id = ++next_id;

			auto component = std::make_unique<Component>(
				id,
				data,
				[this, id]()
				{
					if (this)
					{
						this->unlink_component(id);
					}
				}
			);

			return datas_.try_emplace(id, data).second ?
				std::move(component) : nullptr;
		}

		void unlink_component(ComponentUniqueID id)
		{
			if (datas_.contains(id))
			{
				datas_.erase(id);
			}
		}

	private:

		ComponentID next_id{};

		std::unordered_map<ComponentUniqueID, Data*> datas_{};

	};
}