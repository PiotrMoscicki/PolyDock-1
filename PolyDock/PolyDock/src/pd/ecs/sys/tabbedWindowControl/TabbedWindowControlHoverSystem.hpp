#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Required
	// 1. root/Input
	// 2. tabbedWindowControl/Component
	// 3. tabbedWindowControl/Widget
	//
	// Removed/Added/Modified
	// 1. tabbedWindowControl/Hover
	// Added
	// 1. tabbedWindowControl/WidgetUpdateRequest
	class TabbedWindowControlHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}