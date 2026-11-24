#include "System.h"

#include"DebugSystem.h"

namespace App
{

	void SystemManager::send_log(const char* text, ISystem* system) const noexcept
	{
		auto* debug = this->get_system<DebugSystem>();
		if (!debug)
		{
			return;
		}
		debug->debug_log(text, system->get_name());
	}

	void SystemManager::send_error_log(const char* text, ISystem* system) const noexcept
	{
		auto* debug = this->get_system<DebugSystem>();
		if (!debug)
		{
			return;
		}
		debug->debug_error_log(text, system->get_name());
	}

}
