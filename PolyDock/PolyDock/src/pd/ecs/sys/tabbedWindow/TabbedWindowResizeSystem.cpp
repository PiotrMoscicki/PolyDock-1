#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeSystem.hpp>

#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		ResizeRequest,
		Component>();

	for (auto entity : view)
	{
		const auto& request = view.get<ResizeRequest>(entity);
		auto& window = view.get<Component>(entity);

		window.size = request.newWindowSize;

		registry.remove<ResizeRequest>(entity);
		registry.get_or_assign<RequestWidgetUpdate>(entity);
	}
}