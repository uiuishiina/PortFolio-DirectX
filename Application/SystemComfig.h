#pragma once

#include"System/ClockSystem.h"
#include"System/InputSystem.h"
#include"System/WindowsSystem.h"
#include"System/DebugSystem.h"
#include"System/RendererSystem.h"

namespace App
{


	template<>
	struct SystemTraits<InputSystem> :
		SystemDependency<
		TypeList<EntityManager>,
		TypeList<>,
		TypeList<EntityManager>
		>
	{};

	template<>
	struct SystemTraits<RendererSystem> :
		SystemDependency<
		TypeList<EntityManager,WindowsSystem,DebugSystem>,
		TypeList<WindowsSystem>,
		TypeList<EntityManager>
		>
	{};

	template<>
	struct SystemTraits<WindowsSystem> :
		SystemDependency<
		TypeList<>,
		TypeList<>,
		TypeList<>
		>
	{};

	template<>
	struct SystemTraits<ClockSystem> :
		SystemDependency<
		TypeList<>,
		TypeList<>,
		TypeList<>
		>
	{};

	template<>
	struct SystemTraits<DebugSystem> :
		SystemDependency<
		TypeList<>,
		TypeList<>,
		TypeList<>
		>
	{};

	template<>
	struct SystemTraits<EntityManager> :
		SystemDependency<
		TypeList<DebugSystem>,
		TypeList<>,
		TypeList<DebugSystem>
		>
	{};

}