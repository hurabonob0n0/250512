#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

BEGIN(Engine)

class CVIBuffer;

class ENGINE_DLL CRenderObject : public CGameObject
{
public:
	CRenderObject();
	CRenderObject(CRenderObject& rhs);
	virtual ~CRenderObject() = default;

public:
	virtual _uint Set_ObjCBIndex(const UINT& index);
	virtual void Set_MatIndex(const UINT& index) { m_MatIndicies.push_back(index); }
	virtual void Set_RenderGroup(CRenderer::RENDERGROUP RG);
	_matrix	Get_WorldMatrix() { return m_TransformCom->Get_WorldMatrix(); }

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(float fTimeDelta);
	virtual void LateTick(float fTimeDelta);
	virtual void Render();
	virtual void Render(_uint i);

protected:
	UINT CalcConstantBufferByteSize(UINT byteSize)
	{
		return (byteSize + 255) & ~255;
	}

protected:
	CRenderer* m_RendererCom = {};
	CTransform* m_TexCoordTransformCom = {};

protected:
	UINT m_objCBIndex = -1;
	vector<UINT> m_MatIndicies;
	CRenderer::RENDERGROUP m_RG = CRenderer::RENDERGROUP::RG_PRIORITY;

public:
	void Free() override;
	static CRenderObject* Create();
	CRenderObject* Clone(void* pArg);
};

END