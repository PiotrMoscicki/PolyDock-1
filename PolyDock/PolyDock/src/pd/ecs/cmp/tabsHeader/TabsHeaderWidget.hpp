#pragma once

#include <vector>
#include <optional>
#include <entt/entt.hpp>
#include <qwidget.h>
#include <qpointer.h>
#include <Eigen/Dense>

namespace pd::ecs::cmp::root { class WidgetsOwnerComponent; }

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class ITabsHeaderWidget
	{
	public:
		enum class eAddButtonState { IDLE, HOVERED, PRESSED };

		virtual ~ITabsHeaderWidget() = default;

		virtual void update(std::vector<std::string> names, std::vector<std::optional<QIcon>> icons,
			std::vector<int> selected, int hovered, int active, eAddButtonState addButtonState) = 0;

		virtual int getTabIdxFromPosition(const Eigen::Vector2i& pos) const = 0;
		virtual bool isPositionOnTheRightOfLastTab(const Eigen::Vector2i& pos) const = 0;
		virtual bool hoversAddButton(const Eigen::Vector2i& pos) const = 0;
		virtual Eigen::AlignedBox2i getWidgetRect() const = 0;
		virtual Eigen::Vector2i getCursorPosInTabSpace(const Eigen::Vector2i& pos) const = 0;

		virtual QWidget* getWidget() = 0;
	};

	// ---------------------------------------------------------------------------------------------------------
	class DefaultTabsHeaderWidget : public ITabsHeaderWidget, private QWidget
	{
	public:
		void update(std::vector<std::string> names, std::vector<std::optional<QIcon>> icons,
			std::vector<int> selected, int hovered, int active, eAddButtonState addButtonState) override;

		int getTabIdxFromPosition(const Eigen::Vector2i& pos) const override;
		bool isPositionOnTheRightOfLastTab(const Eigen::Vector2i& pos) const override;
		bool hoversAddButton(const Eigen::Vector2i& pos) const override;
		Eigen::AlignedBox2i getWidgetRect() const override;
		Eigen::Vector2i getCursorPosInTabSpace(const Eigen::Vector2i& pos) const override;

		QWidget* getWidget() override { return this; }

	private:
		// QWidget
		void paintEvent(QPaintEvent* event) override;

		Eigen::AlignedBox2i getTabRectAtIdx(int idx) const;
		Eigen::AlignedBox2i getTextRectAtIdx(int idx) const;
		Eigen::AlignedBox2i getSeparatorRectAtIdx(int idx) const;
		Eigen::AlignedBox2i getAddButtonRect() const;
		int getTabWidth() const;
		int getAlternativeTabWidth() const;

		std::vector<std::string> m_names;
		std::vector<std::optional<QIcon>> m_icons;
		std::vector<int> m_selected;
		int m_hovered = -1;
		int m_active = -1;
		eAddButtonState m_addButtonState = eAddButtonState::IDLE;

		int m_maxTabWidth = 150;
		int m_separatorWidth = 4;
		Eigen::Vector2i m_interactiveBoxSize = { 20, 20 };
		QLinearGradient m_activeTabGradient;
		QLinearGradient m_hoveredTabGradient;
		QLinearGradient m_inactiveTabGradient;
		QLinearGradient m_separatorGradient;
		QLinearGradient m_tempGradient; //temp toremove
		QColor m_filColor;
	};

	// ---------------------------------------------------------------------------------------------------------
	class Widget
	{
	public:
		Widget(ITabsHeaderWidget* header) : m_header(header) {}

		void update(std::vector<std::string> names, std::vector<std::optional<QIcon>> icons, 
			std::vector<int> selected, int hovered, int active, ITabsHeaderWidget::eAddButtonState addButtonState)
			{ m_header->update(std::move(names), std::move(icons), std::move(selected), hovered, active, addButtonState); }

		int getTabIdxFromPosition(const Eigen::Vector2i& pos) const { return m_header->getTabIdxFromPosition(pos); }
		int isPositionOnTheRightOfLastTab(const Eigen::Vector2i& pos) const { return m_header->isPositionOnTheRightOfLastTab(pos); }
		bool hoversAddButton(const Eigen::Vector2i& pos) const { return m_header->hoversAddButton(pos); }
		Eigen::AlignedBox2i getWidgetRect() const { return m_header->getWidgetRect(); }
		Eigen::Vector2i getCursorPosInTabSpace(const Eigen::Vector2i& pos) const { return m_header->getCursorPosInTabSpace(pos); }

		QWidget* getTabsHeaderWidget() { return m_header->getWidget(); }

	private:
		ITabsHeaderWidget* m_header = nullptr;
	};
}