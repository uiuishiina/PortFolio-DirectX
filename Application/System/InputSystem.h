#pragma once

#include"System.h"
#include"Entity.h"
#include"Enum/EnumToIndex.h"
#include"../Component/ComponentManager.h"
#include"Tuple/TupleBase.h"
#include"Bit/BitFlag.h"

#include<variant>

namespace App
{
	enum class InputKeyBoard {

		/* -- 数値 -- */

		Zero,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Ate,
		Nine,

		/* -- アルファベット -- */
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		N,
		M,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		/* -- Funcキー -- */

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		/* -- その他 -- */

		Space,
		Enter,
		Esc,
		Shift,
		Contrl,
		Tab,

		/* -- 矢印キー -- */

		UpArrow,
		DownArrow,
		LeftArrow,
		RightArrow,

		/* -- 配列用意用Enum -- */

		Count
	};

	/// <summary>
	/// マウス入力フラグ列挙体
	/// </summary>
	enum class InputMouse {

		Left,
		Right,

		Count
	};
	
	class InputDevice
	{
	public:
		bool is_pressed(InputKeyBoard key) const
		{
			return get_async_key(convert_key(key));
		}

		bool is_pressed(InputMouse key) const
		{
			return get_async_key(convert_key(key));
		}

	private:

		bool get_async_key(int key) const;

		static int convert_key(InputKeyBoard key);

		static int convert_key(InputMouse key);
	};

	template<HandyItems::Enum::concepts::EnumHasCount... InputEnums>
	struct BindingKey
	{
		using BindKeyType = std::variant<
			InputEnums...
		>;

		BindKeyType key_;

		template<HandyItems::Enum::concepts::EnumHasCount T>
			requires (std::is_same_v<T, InputEnums> || ...)
		BindingKey(T key)
			: key_{ key }
		{
		}
	};

	template<typename Action, HandyItems::Enum::concepts::EnumHasCount... InputEnums>
	class BindActionManager
	{
		using BindingKeyType = BindingKey<InputEnums...>;
	public:

		explicit BindActionManager(
			InputDevice* device
		):
			device_{device} 
		{
		}

		template<typename T>
		void add_bind(
			Action action,
			T&& key
		)
		{
			binds_[action].emplace_back(
				std::forward<T>(key)
			);
		}

		bool pressed_bind_keys(
			Action action
		) const
		{

			const auto it = binds_.find(action);
			if (it == binds_.end())
			{
				return false;
			}

			for (const auto& key : it->second)
			{
				const auto pressed = std::visit(
					[&](const auto& input_key) -> bool
					{
						return device_->is_pressed(input_key);
					},
					key.key_
				);
				if (pressed)
				{
					return true;
				}
			}
			return false;
		}

		void clear_bind()
		{
			binds_.clear();
		}

	private:

		InputDevice* device_{};

		std::unordered_map<Action, std::vector<BindingKeyType>> binds_{};

	};


	enum class InputAction {

		MoveUp,
		MoveLeft,
		MoveDown,
		MoveRight,
		Jump,
		Esc
	};

	enum class ActionState
	{
		None,
		Down,
		Hold,
		Up
	};


	class ActionManager
	{
	public:

		explicit ActionManager(
			InputDevice* device
		)
			:
			device_{device},
			actions_{ device_ }
		{
		}

		void update()
		{
			previous_action = current_action;
			for (auto& [action, flag] : current_action)
			{
				flag = actions_.pressed_bind_keys(action);
			}
		}

		template<typename... Args>
		void add_action_bind(
			InputAction action,
			Args&&... args
		)
		{
			current_action.try_emplace(action, false);
			previous_action.try_emplace(action, false);

			actions_.add_bind(
				action,
				std::forward<Args>(args)...
			);
		}

		ActionState get_action_state(
			InputAction action
		) const 
		{
			const auto current_it = current_action.find(action);
			const auto previous_it = previous_action.find(action);

			if (
				current_it == current_action.end() ||
				previous_it == previous_action.end()
				)
			{
				return ActionState::None;
			}

			const auto currnet = current_it->second;
			const auto previous = previous_it->second;

			if (currnet && !previous)
			{
				return ActionState::Down;
			}
			else if (currnet && previous)
			{
				return ActionState::Hold;
			}
			else if (!currnet && previous)
			{
				return ActionState::Up;
			}

			return ActionState::None;
		}

	private:

		InputDevice* device_{};

		BindActionManager<InputAction, InputKeyBoard,InputMouse> actions_;

		std::unordered_map<InputAction, bool> current_action{};

		std::unordered_map<InputAction, bool> previous_action{};

	};


	class InputComponent final : public IComponent
	{
	public:

		explicit InputComponent(
			const ComponentUniqueID& id,
			ActionManager* manager,
			RemoveFunc func = {}
		) :
			manager_{ manager },
			IComponent{ id,func }
		{
		};

		ActionState get_action_state(
			InputAction action
		) const
		{
			return manager_->get_action_state(action);
		}


	private:

		ActionManager* manager_{};

	};


	class IInputSystem : public ISystem
	{

	};

	class InputSystem : public ISystem
	{
	public:

		bool init_system(SystemManager& manager) override
		{
			manager_ = manager.get_system<EntityManager>();
			return manager_;
		}

		void update_system() override
		{
			action_Manager.update();
		}

		template<typename Component>
		std::unique_ptr<Component> create_component()
		{
			if constexpr (std::is_same_v<Component, InputComponent>)
			{
				return components_.create_component(&action_Manager);
			}
			else
			{
				return nullptr;
			}
		}


		void unlink_component(ComponentUniqueID id)
		{
			components_.unlink_component(id);
		}


		void shutdown_system() override
		{
			if (manager_)
			{
				if (manager_->has_entitys())
				{
					manager_->remove_component_to_all<InputComponent>();
				}
			}
		}

		ActionManager& get_action_manager()
		{
			return action_Manager;
		}

	private:

		EntityManager* manager_{};

		InputDevice device_{};

		ActionManager action_Manager{ &device_ };

		ComponentManager<InputComponent, ActionManager> components_{};
	};


	template<>
	struct ComponentTraits<InputComponent>
	{
		using System = InputSystem;
	};

}