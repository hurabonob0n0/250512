#include "Client_pch.h"
#include "Terrain.h"
#include "Client_Defines.h"
#include "GameInstance.h"

CTerrain::CTerrain() : CRenderObject()
{
}

HRESULT CTerrain::Initialize_Prototype()
{
    __super::Initialize_Prototype();
    return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
    m_RG = CRenderer::RG_BLEND;

    __super::Initialize(pArg);
    m_VIBufferCom = (CVIBuffer_Terrain*)m_GameInstance->Get_Component("TerrainCom");

    return S_OK;
}

void CTerrain::Tick(float fTimeDelta)
{
    

    __super::Tick(fTimeDelta);
}

void CTerrain::LateTick(float fTimeDelta)
{
    __super::LateTick(fTimeDelta);
}

void CTerrain::Render()
{
    __super::Render();

    m_VIBufferCom->Render();
}

CTerrain* CTerrain::Create()
{
    CTerrain* pInstance = new CTerrain;
    pInstance->Initialize_Prototype();
    return pInstance;
}

CRenderObject* CTerrain::Clone(void* pArg)
{
    CTerrain* pInstance = new CTerrain;
    pInstance->Initialize(pArg);
    return pInstance;
}

void CTerrain::Free()
{
    Safe_Release(m_VIBufferCom);
    __super::Free();
}
