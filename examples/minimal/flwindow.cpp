#include "flwindow.h"
#include "../../framelesshelper.h"

#include <QScreen>
#include <QVBoxLayout>
#include <QPushButton>

FRAMELESSHELPER_USE_NAMESPACE

FLWindow::FLWindow(QWidget *parent) : QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setupUi();

	move(screen()->geometry().center() - frameGeometry().center());
}

FLWindow::~FLWindow()
{

}

void FLWindow::initFramelessWindow()
{
	FramelessHelper* helper = new FramelessHelper(windowHandle());
	helper->setResizeBorderThickness(4);
	helper->setTitleBarHeight(m_titleBarWidget->height());
	helper->setResizable(true);
	helper->setHitTestVisible(m_minimizeButton);
	helper->setHitTestVisible(m_maximizeButton);
	helper->setHitTestVisible(m_closeButton);
	helper->install();
}

void FLWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    static bool inited = false;
    if (!inited) {
        inited = true;
		initFramelessWindow();
    }
}

void FLWindow::setupUi()
{
	resize(800, 600);

	m_titleBarWidget = new QWidget(this);
	m_titleBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_titleBarWidget->setFixedHeight(40);
	m_titleBarWidget->setStyleSheet(QString::fromLatin1("background:grey"));

    m_minimizeButton = new QPushButton(m_titleBarWidget);
	m_minimizeButton->setText(QStringLiteral("Min"));
    m_minimizeButton->setObjectName(QStringLiteral("MinimizeButton"));
    connect(m_minimizeButton, &QPushButton::clicked, this, &QWidget::showMinimized);

    m_maximizeButton = new QPushButton(m_titleBarWidget);
	m_maximizeButton->setText(QStringLiteral("Max"));
    m_maximizeButton->setObjectName(QStringLiteral("MaximizeButton"));
    connect(m_maximizeButton, &QPushButton::clicked, this, [this](){
        if (isMaximized() || isFullScreen()) {
            showNormal();
        } else {
            showMaximized();
        }
    });

    m_closeButton = new QPushButton(m_titleBarWidget);
	m_closeButton->setText(QStringLiteral("Close"));
    m_closeButton->setObjectName(QStringLiteral("CloseButton"));
    connect(m_closeButton, &QPushButton::clicked, this, &QWidget::close);

    const auto titleBarLayout = new QHBoxLayout(m_titleBarWidget);
    titleBarLayout->setContentsMargins(0, 0, 0, 0);
    titleBarLayout->setSpacing(10);
    titleBarLayout->addStretch();
    titleBarLayout->addWidget(m_minimizeButton);
    titleBarLayout->addWidget(m_maximizeButton);
    titleBarLayout->addWidget(m_closeButton);
	titleBarLayout->addStretch();
    m_titleBarWidget->setLayout(titleBarLayout);

    const auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_titleBarWidget);
    mainLayout->addStretch();
    setLayout(mainLayout);
}