#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// Required
	// 1. Input
	// 2. ResizeHover
	// 
	// Added
	// 1. ResizeActive
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeStartSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}