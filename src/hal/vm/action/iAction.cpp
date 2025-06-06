﻿#include "iAction.h"
#include "./manu/manuAction.h"
#include "./mark/markAction.h"
#include "./spread/spreadAction.h"

namespace TIGER_VMSLM
{
    IAction::IAction(CVM *p_vm) : QObject(nullptr), m_pVM(p_vm), m_bStop(false), runCount(0)
    {
        assert(m_pVM != nullptr);
    }

    IAction::~IAction()
    {
    }

    void IAction::start()
    {
        m_bStop = false;
    }

    void IAction::stop()
    {
        m_bStop = true;
    }


    CActionCreater::CActionCreater(CVM *p_vm) : m_pVM(p_vm)
    {
        assert(m_pVM != nullptr);
    }

    IAction *CActionCreater::autoWorkAction()
    {
        return new CManuAction(m_pVM);
    }

    IAction *CActionCreater::markOnceAction()
    {
        return new CMarkAction(m_pVM);
    }

    IAction *CActionCreater::spreadAction()
    {
        return new CSpreadAction(m_pVM);
    }
}