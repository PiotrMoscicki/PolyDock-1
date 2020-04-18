#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlPressSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlPressSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			if (registry.has<HoverComponent>(entity)
				&& inputComponent->isPressed(InputComponent::eMouseButton::LEFT))
			{
				registry.get_or_assign<PressComponent>(entity);
				registry.get_or_assign<WidgetUpdateRequestComponent>(entity);
			}
			else if (registry.has<PressComponent>(entity))
			{
				registry.remove<PressComponent>(entity);
				registry.get_or_assign<WidgetUpdateRequestComponent>(entity);
			}
		}
	}
}