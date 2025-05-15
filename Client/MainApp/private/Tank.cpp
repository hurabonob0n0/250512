#include "Client_pch.h"
#include "Tank.h"
#include "Client_Defines.h"
#include "GameInstance.h"
#include "ClientPacketHandler.h"
#include "ServiceManager.h"


CTank::CTank() : CRenderObject()
{
}

CTank::CTank(CTank& rhs) : CRenderObject(rhs)
{
}

HRESULT CTank::Initialize_Prototype()
{
    __super::Initialize_Prototype();

    return S_OK;
}

HRESULT CTank::Initialize(void* pArg)
{
    m_RG = CRenderer::RG_BLEND;

    __super::Initialize(pArg);

    MaterialData mat{};
    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Fence_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Fences_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Fence_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Fences_Normal.dds"));
    int a = m_GameInstance->Add_Material("Tank_Fence", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Glacis_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Glacis_Plate_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Glacis_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Glacis_Plate_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Glacis", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Glass_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Glass_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Glass_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Glass_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Glass", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Sprocket_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Sprocket_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Sprocket_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Sprocket_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Sprocket", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Tracks_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Tracks_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Tracks_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Tracks_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Tracks", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Turret_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Turret_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Turret_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Turret_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Turret", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_W_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_W_Base_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_W_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_W_Base_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_W", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_Wheels_D", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Wheels_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_Wheels_N", CTexture::Create(L"../bin/Models/TankDDS/M1A2_Wheels_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_Wheels", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_M250_D", CTexture::Create(L"../bin/Models/TankDDS/M2-50_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_M250_N", CTexture::Create(L"../bin/Models/TankDDS/M2-50_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_M250", mat);

    mat.DiffuseMapIndex = m_GameInstance->Add_Texture("Tank_M240P_D", CTexture::Create(L"../bin/Models/TankDDS/M240P_Base_color.dds"));
    mat.NormalMapIndex = m_GameInstance->Add_Texture("Tank_M240P_N", CTexture::Create(L"../bin/Models/TankDDS/M240P_Normal.dds"));
    a = m_GameInstance->Add_Material("Tank_M240P", mat);


    m_VIBuffer= (CModel*)m_GameInstance->Get_Component("ModelCom");

    CB_Mat_Index CBMat{};

    for (int i = 0; i < 10; ++i)
    {
        CBMat.CBIndex = i+1;
        CBMatIndicies.push_back(CBMat);
    }



    return S_OK;
}

void CTank::Tick(float fTimeDelta)
{
    //if (_myPlayer) {

    //    if (m_GameInstance->Key_Pressing(VK_UP)) {
    //        m_TransformCom->Go_Straight(fTimeDelta * 30.f);
    //        //_float4 tempPosition;
    //        //XMStoreFloat4(&tempPosition, m_TransformCom->Get_State(CTransform::STATE_POSITION));
    //        //SendBufferRef sendBuffer = ClientPacketHandler::Make_C_MOVE(tempPosition.x, tempPosition.y, tempPosition.z);
    //        //ServiceManager::GetInstace().GetService()->Broadcast(sendBuffer);
    //    }

    //    if (m_GameInstance->Key_Pressing(VK_LEFT)) {
    //        m_TransformCom->Go_Left(fTimeDelta * 30.f);
    //        //_float4 tempPosition;
    //        //XMStoreFloat4(&tempPosition, m_TransformCom->Get_State(CTransform::STATE_POSITION));
    //        //SendBufferRef sendBuffer = ClientPacketHandler::Make_C_MOVE(tempPosition.x, tempPosition.y, tempPosition.z);
    //        //ServiceManager::GetInstace().GetService()->Broadcast(sendBuffer);

    //    }

    //    if (m_GameInstance->Key_Pressing(VK_DOWN)) {
    //        m_TransformCom->Go_Backward(fTimeDelta * 30.f);
    //        //_float4 tempPosition;
    //        //XMStoreFloat4(&tempPosition, m_TransformCom->Get_State(CTransform::STATE_POSITION));
    //        //SendBufferRef sendBuffer = ClientPacketHandler::Make_C_MOVE(tempPosition.x, tempPosition.y, tempPosition.z);
    //        //ServiceManager::GetInstace().GetService()->Broadcast(sendBuffer);

    //    }

    //    if (m_GameInstance->Key_Pressing(VK_RIGHT)) {
    //        m_TransformCom->Go_Right(fTimeDelta * 30.f);
    //        //_float4 tempPosition;
    //        //XMStoreFloat4(&tempPosition, m_TransformCom->Get_State(CTransform::STATE_POSITION));
    //        //SendBufferRef sendBuffer = ClientPacketHandler::Make_C_MOVE(tempPosition.x, tempPosition.y, tempPosition.z);
    //        //ServiceManager::GetInstace().GetService()->Broadcast(sendBuffer);

    //    }

    //    _float4 Position;

    //    XMStoreFloat4(&Position, m_TransformCom->Get_State(CTransform::STATE_POSITION));

    //    float TerrainY = ((CVIBuffer_Terrain*)(m_GameInstance->GetPrototype("TerrainCom")))->Get_Terrain_Heights(Position.x, Position.z);

    //    m_TransformCom->Set_State(CTransform::STATE_POSITION, _vector{ Position.x,TerrainY - 8.f,Position.z,1.f });

    //}


    if (m_GameInstance->Key_Down(VK_SPACE))
    {
        if (m_CBIndex < 9)
            ++m_CBIndex;
        else
            m_CBIndex = 0;
    }

    _uint Matindex = CBMatIndicies[m_CBIndex].MatIndex;

    if (m_GameInstance->Key_Down(VK_RIGHT))
        if (Matindex < 8)
            CBMatIndicies[m_CBIndex].MatIndex += 1;

    if (m_GameInstance->Key_Down(VK_LEFT))
        if (Matindex > 0)
            CBMatIndicies[m_CBIndex].MatIndex -= 1;

}

void CTank::LateTick(float fTimeDelta)
{
    //__super::LateTick(fTimeDelta);
    m_RendererCom->AddtoRenderObjects(m_RG, this);

    auto FrameResource = m_GameInstance->Get_Current_FrameResource();
    auto currObjectCB = FrameResource->m_ObjectCB;

    XMMATRIX world = m_TransformCom->Get_WorldMatrix();
    _matrix textransform = m_TexCoordTransformCom->Get_WorldMatrix();

    ObjectConstants objConstants{};
    XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
    XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(textransform));

    for (int i = 0; i < CBMatIndicies.size(); ++i) {
        objConstants.MaterialIndex = CBMatIndicies[i].MatIndex;
        currObjectCB->CopyData(CBMatIndicies[i].CBIndex, objConstants);
    }

}

void CTank::Render()
{
    //__super::Render();
    _uint bs = sizeof(ObjectConstants);
    UINT objCBByteSize = CRenderObject::CalcConstantBufferByteSize(bs);

    auto objectCB = m_GameInstance->Get_Current_FrameResource()->m_ObjectCB->Resource();


    for (int i = 0; i < CBMatIndicies.size(); ++i) {
        D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
        objCBAddress += CBMatIndicies[i].CBIndex * objCBByteSize;
        m_GameInstance->Get_CommandList()->SetGraphicsRootConstantBufferView(0, objCBAddress);
        m_VIBuffer->Render(i);
    }

    /*objCBAddress += CBMatIndicies[0].CBIndex * objCBByteSize;
    m_GameInstance->Get_CommandList()->SetGraphicsRootConstantBufferView(0, objCBAddress);*/

    //m_VIBuffer->Render(0);
}

void CTank::Free()
{
    __super::Free();
    Safe_Release(m_VIBuffer);
}

CTank* CTank::Create()
{
    CTank* pInstance = new CTank;
    pInstance->Initialize_Prototype();
    return pInstance;
}

CRenderObject* CTank::Clone(void* pArg)
{
    CTank* pInstance = new CTank(*this);
    pInstance->Initialize(pArg);
    return pInstance;
}
