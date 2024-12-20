﻿#include "mainWindow.h"
#include "basic.h"
#include "system/basic.h"
#include "hal/DZSTMark/DZSTMark.h"
#include "controlWindow/controlWindow.h"
#include "multipointCorrectWindow/multipointCorrectWindow.h"
#include <QTextBrowser>
#include <QVBoxLayout>

CMainWindow* g_pMainWindow = nullptr;
CMainWindow* mainWindow()
{
    return g_pMainWindow;
};

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent)
{
    g_pMainWindow = this;

    m_hWnd = (HWND)this->winId();
    m_pCDZSTMark = new CDZSTMark(m_hWnd);

    init();
}

CMainWindow::~CMainWindow()
{
    delPtr(m_pCDZSTMark);
}

void CMainWindow::printMsg(QString p_msg)
{
    m_pOutMsg->append(p_msg);
    m_pOutMsg->moveCursor(m_pOutMsg->textCursor().End);
}

bool CMainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(eventType);

	MSG* msg = static_cast<MSG*>(message);
    m_pCDZSTMark->nativeEvent(msg);

	return QWidget::nativeEvent(eventType, message, result);
}

void CMainWindow::init()
{
    m_pMultipointCorrect = new CMultipointCorrect(this, m_pCDZSTMark);
    m_pControl = new CControl(this, m_pCDZSTMark);

    // 输入输出窗口
    m_pOutMsg = new QTextBrowser;
    m_pOutMsg->setOpenLinks(false);
    m_pOutMsg->setOpenExternalLinks(false);
    m_pOutMsg->setStyleSheet(cStyleSheet);
    m_pOutMsg->document()->setMaximumBlockCount(300);
    m_pOutMsg->setFixedHeight(100);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_pMultipointCorrect);
    pLayout->addWidget(m_pControl);
    pLayout->addWidget(m_pOutMsg);
    this->setLayout(pLayout);
}