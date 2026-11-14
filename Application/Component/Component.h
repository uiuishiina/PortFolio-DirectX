#pragma once

#include<cstdint>
#include<typeindex>
#include<typeinfo>
#include<functional>

#include"Others/NonCopyableBase.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App
{

	using ComponentID = std::uint64_t;
	using ComponentUniqueID = std::uint64_t;

	using RemoveFunc = std::function<void()>;

	template<typename T>
	ComponentID get_component_id()
	{
		return static_cast<ComponentID>(
			typeid(T).hash_code()
			);
	}

	class IComponent : HandyItems::others::NonCopyableBase
	{
	public:

		explicit IComponent(
			const ComponentUniqueID& id,
			RemoveFunc func = {}
		) :
			id_{ id },
			func_{ std::move(func) }
		{
		};

		virtual ~IComponent()
		{
			if (func_)
			{
				func_();
			}
		}

		bool get_active() const noexcept
		{
			return is_active;
		}

		void set_active(
			bool active
		) noexcept
		{
			is_active = active;
		}

		const ComponentUniqueID& get_unique_id() const noexcept
		{
			return id_;
		}

	private:

		bool is_active = true;

		ComponentUniqueID id_{};

		RemoveFunc func_{};

	};

	template<typename T>
	struct ComponentTraits;

}