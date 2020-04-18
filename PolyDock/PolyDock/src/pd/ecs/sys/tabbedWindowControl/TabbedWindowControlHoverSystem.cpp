#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlHoverSystem.hpp>

#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

using namespace ::pd::ecs::sys::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowControlHoverSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component, WidgetComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto entity : view)
		{
			const auto& widgetCmp = view.get<WidgetComponent>(entity);

			const IWidget::eButton hovered = widgetCmp.widget->getButtonFromPos(inputComponent->getCursorPos());

			if (hovered != IWidget::eButton::NONE)
			{
				registry.get_or_assign<HoverComponent>(entity).hovered = hovered;
				registry.get_or_assign<WidgetUpdateRequestComponent>(entity);
			}
			else if (registry.has<HoverComponent>(entity))
			{
				registry.remove<HoverComponent>(entity);
				registry.get_or_assign<WidgetUpdateRequestComponent>(entity);
			}
		}
	}{}
}