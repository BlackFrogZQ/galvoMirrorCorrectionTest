﻿#include "vm.h"
#include "ncDef.h"
#include "./action/iAction.h"

namespace TIGER_VMSLM
{
    CVM::CVM(HWND p_hWnd) : IVM(p_hWnd), m_megatron(nullptr)
    {
        m_plcServer = new CModbusServer(this);
        m_plcControl = new IPlcController(m_plcServer);
        assert(m_plcServer != nullptr);
        assert(m_plcControl != nullptr);

        m_megatron = new CDZSTeGMCMegatron(m_hWnd);
        m_megatronController = new IMegatronController(m_megatron);
        assert(m_megatron != nullptr);
        assert(m_megatronController != nullptr);
        connect(m_megatron, &CDZSTeGMCMegatron::sigMarkEnd, this, [this]()
        {
            emit sigMarkEnd();
        });
        connect(m_megatron, &CDZSTeGMCMegatron::sigDownloadEnd, this, [this]()
        {
            emit sigDownloadEnd();
        });
        connect(m_megatron, &CDZSTeGMCMegatron::sigExecProcess, this, [this](unsigned int p_value)
        {
            emit sigExecProcess(p_value);
        });
        connect(m_megatron, &CDZSTeGMCMegatron::sigError, this, [this](const QString &p_msg)
        {
            myInfo << p_msg;
        });

        auto pActionCreator = new CActionCreater(this);
        assert(pActionCreator != nullptr);
        m_pManuAction = pActionCreator->autoWorkAction();
        m_pMarkAction = pActionCreator->markOnceAction();
        m_pSpreadAction = pActionCreator->spreadAction();
        delete pActionCreator;
        pActionCreator = nullptr;
        connect(m_pSpreadAction, &IAction::sigEnd, this, [this]()
        {
            emit sigSpreadEnd();
            if (m_vmStatus == vmsSpread)
            {
                changeVMStatus(vmsIdle);
            }
        });
        connect(m_pMarkAction, &IAction::sigEnd, this, [this]()
        {
            emit sigMarkEnd();
            if (m_vmStatus == vmsMark)
            {
                changeVMStatus(vmsIdle);
            }
        });
    }

    CVM::~CVM()
    {
        delPtr(m_megatron);
    }

    void CVM::init()
    {
        m_plcServer->setPlcIP(CModbusServer::CPlcIP(cnStr("PLC"), plcParas()->ip, plcParas()->ipPort, plcParas()->ipMAC));
        m_plcServer->connectPlc();

        m_megatron->setMegatronIP(CMegatronIP(cnStr("振镜控制卡"), DZSTMarkConnectPara()->ip));
        m_megatron->connectMegatron();
    }

    void CVM::autoWork()
    {
        m_pManuAction->start();
    }

    void CVM::stopWork()
    {
        m_pManuAction->stop();
    }

    void CVM::startSpread()
    {
        m_pSpreadAction->start();
        changeVMStatus(vmsSpread);
    }

    void CVM::stopSpread()
    {
        assert(m_vmStatus == vmsSpread);
        m_pSpreadAction->stop();
        changeVMStatus(vmsIdle);
    }

    void CVM::startMark()
    {
        m_megatron->starMark();
    }
    void CVM::pauseMark()
    {
        m_megatron->PauseMark();
    }
    void CVM::continueMark()
    {
        m_megatron->ContinueMark();
    }
    void CVM::stopMark()
    {
        m_megatron->StopMark();
    }

    void CVM::nativeEvent(MSG* p_message)
    {
        assert(p_message != nullptr);
        if(m_megatron)
        {
            m_megatron->nativeEvent(p_message);
        }
    }

    void CVM::creatUdmBin(std::vector<std::vector<TIGER_PrintDatas::Segment>> p_segments)
    {
        m_megatron->creatUdmBin(p_segments);
    }

    bool CVM::sendDisColis(int p_addr, bool p_value)
    {
        return m_plcServer->sendDisColis(p_addr, p_value);
    }

    bool CVM::sendHold(int p_addr, bool p_value)
    {
        return m_plcServer->sendHold(p_addr, p_value);
    }

    void CVM::changeVMStatus(CVMStatus p_status)
    {
        if (m_vmStatus == p_status)
        {
            return;
        }
        m_vmStatus = p_status;
        myInfo << cnStr("虚拟机状态改变为: %1").arg(cvmStatusCn[p_status]);
        emit sigVMStatusUpdate();
    }
}