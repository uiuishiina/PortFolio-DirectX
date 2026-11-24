#pragma once

#include"System.h"
#include"Debug/DebugLogSystem.h"

/*
	既存のクラスをシステムで扱えるように中継するが、マクロは削除し関数呼び出しでの方針でいく
*/

namespace App
{
	class DebugSystem final : public ISystem
	{
		using HRESULT = long;
	public:

		explicit DebugSystem()
		{
			ISystem::name_ = "DebugSystem";
		}

		bool init_system(SystemManager& manager) override
		{
			//	Rendererの移行が完了したらマクロ削除とインスタンスをここで初期化する

			is_init = true;
			return is_init;
		}

		void update_system() override
		{
		}

		void shutdown_system() override
		{
		}

		template<typename... Args>
		void debug_log(Args&&... args)
		{
			HandyItems::Debug::DebugLogSystem::Instance().send_to_thread(
				HandyItems::Debug::DebugLogBuilder::create_LogObject(
					HandyItems::Debug::create_string(std::forward<Args>(args)...)
				)
			);
		}

		template<typename... Args>
		void debug_error_log(Args&&... args)
		{
			HandyItems::Debug::DebugLogSystem::Instance().send_to_thread(
				HandyItems::Debug::DebugLogBuilder::create_LogObject(
					HandyItems::Debug::create_string(std::forward<Args>(args)...),
					HandyItems::Debug::LogLevel::Error
				)
			);
		}

		std::string to_HRESULT(HRESULT hr);
	};
}