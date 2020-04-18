#include <pd/pch/PCH.h>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

using namespace ::pd::ecs::cmp::tabbedWindowControl;

// ---------------------------------------------------------------------------------------------------------
DefaultWidget::DefaultWidget()
	: m_layout(new QGridLayout()), m_minimize(new QLabel()),
	m_maximize(new QLabel()), m_close(new QLabel())
{
	setLayout(m_layout);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->addWidget(m_minimize, 0, 0);
	m_layout->addWidget(m_maximize, 0, 1);
	m_layout->addWidget(m_close, 0, 2);
	m_layout->setRowStretch(0, 0);

	m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimize.png"));
	m_minimize->setAutoFillBackground(true);
	m_maximize->setPixmap(QPixmap(":/icons/tabbedWindow/maximize.png"));
	m_maximize->setAutoFillBackground(true);
	m_close->setPixmap(QPixmap(":/icons/tabbedWindow/close.png"));
	m_close->setAutoFillBackground(true);

	QWidget::setFixedSize(145, 20);

	QPalette pal = QWidget::palette();
	pal.setColor(QPalette::Window, QColor(30, 30, 30));
	QWidget::setAutoFillBackground(true);
	QWidget::setPalette(pal);
}

// ---------------------------------------------------------------------------------------------------------
void DefaultWidget::update(eButton hovered, bool pressed, bool maximized)
{
	QPalette normal = QWidget::palette();
	normal.setColor(QPalette::Window, QColor(30, 30, 30));
	QPalette hover = QWidget::palette();
	hover.setColor(QPalette::Window, QColor(60, 60, 60));
	QPalette press = QWidget::palette();
	press.setColor(QPalette::Window, QColor(90, 90, 90));
	QPalette closeHover = QWidget::palette();
	closeHover.setColor(QPalette::Window, QColor(232, 17, 35));
	QPalette closePress = QWidget::palette();
	closePress.setColor(QPalette::Window, QColor(140, 12, 22));


	{ // eButton::MINIMIZE
		if (hovered == eButton::MINIMIZE)
		{
			if (pressed)
				m_minimize->setPalette(press);
			else
				m_minimize->setPalette(hover);
		}
		else
			m_minimize->setPalette(normal);
	}
	{ // eButton::MAXIMIZE
		QString part = maximized ? "restore" : "maximize";

		if (hovered == eButton::MAXIMIZE)
		{
			if (pressed)
				m_maximize->setPalette(press);
			else
				m_maximize->setPalette(hover);
		}
		else
			m_maximize->setPalette(normal);
	}
	{ // eButton::CLOSE
		if (hovered == eButton::CLOSE)
		{
			if (pressed)
				m_close->setPalette(closePress);
			else
				m_close->setPalette(closeHover);
		}
		else
			m_close->setPalette(normal);
	}
}

// ---------------------------------------------------------------------------------------------------------
Eigen::AlignedBox2i DefaultWidget::getWidgetRect() const
{
	const QRect rect = QWidget::rect();
	const QPoint globalPos = QWidget::mapToGlobal(rect.topLeft());

	return Eigen::AlignedBox2i(
		Eigen::Vector2i{ globalPos.x(), globalPos.y() },
		Eigen::Vector2i{ rect.width() + globalPos.x(), rect.height() + globalPos.y() });
}

// ---------------------------------------------------------------------------------------------------------
DefaultWidget::eButton DefaultWidget::getButtonFromPos(const Eigen::Vector2i& pos) const
{
	eButton result = eButton::NONE;

	if (m_minimize->rect().contains(m_minimize->mapFromGlobal({ pos.x(), pos.y() })))
		return eButton::MINIMIZE;
	else if (m_maximize->rect().contains(m_maximize->mapFromGlobal({ pos.x(), pos.y() })))
		return eButton::MAXIMIZE;
	else if (m_close->rect().contains(m_close->mapFromGlobal({ pos.x(), pos.y() })))
		return eButton::CLOSE;
	else
		return eButton::NONE;
}