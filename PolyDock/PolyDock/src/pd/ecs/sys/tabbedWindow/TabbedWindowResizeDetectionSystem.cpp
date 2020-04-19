#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeDetectionSystem.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		Component, 
		ResizeActive>();

	if (const auto* inputComponent = registry.try_get<Input>(root))
	{
		const Vector2i diff = inputComponent->getCursorDiff();
		if (diff != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				using eVertical = ResizeHover::eVertical;
				using eHorizontal = ResizeHover::eHorizontal;

				const auto& windowCmp = registry.get_or_assign<Component>(entity);
				const auto& activeCmp = registry.get_or_assign<ResizeActive>(entity);
				auto& resizeRequestCmp = registry.get_or_assign<ResizeRequest>(entity);
				auto& movementRequestCmp = registry.get_or_assign<MovementRequest>(entity);

				resizeRequestCmp.newWindowSize = windowCmp.size;
				movementRequestCmp.newWindowPos = windowCmp.position;

				if (activeCmp.vertical == eVertical::BOTTOM)
					resizeRequestCmp.newWindowSize.y() = windowCmp.size.y() + diff.y();
				else if (activeCmp.vertical == eVertical::TOP)
				{
					movementRequestCmp.newWindowPos.y() = windowCmp.position.y() + diff.y();
					resizeRequestCmp.newWindowSize.y() = windowCmp.size.y() - diff.y();
				}

				if (activeCmp.horizontal == eHorizontal::RIGHT)
					resizeRequestCmp.newWindowSize.x() = windowCmp.size.x() + diff.x();
				else if (activeCmp.horizontal == eHorizontal::LEFT)
				{
					movementRequestCmp.newWindowPos.x() = windowCmp.position.x() + diff.x();
					resizeRequestCmp.newWindowSize.x() = windowCmp.size.x() - diff.x();
				}
			}
		}
	}
}