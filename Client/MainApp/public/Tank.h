#pragma once
#include "RenderObject.h"

BEGIN(Engine)
class CModel;
END


BEGIN(Client)

class CTank : public CRenderObject
{
public:
	struct CB_Mat_Index {
		_uint CBIndex = 1;
		_uint MatIndex = 0;
	};

private:
	CTank();
	CTank(CTank& rhs);
	virtual ~CTank() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(float fTimeDelta);
	virtual void LateTick(float fTimeDelta);
	virtual void Render();

private:
	CModel* m_VIBuffer;

	vector<CB_Mat_Index> CBMatIndicies;
	_uint m_CBIndex = 0;

	bool	KeyInput = false;
	

public:
	void set_MyPlayer() {
		_myPlayer = true;

	}
private:
	bool _myPlayer = false;

public:
	void Free() override;
	static CTank* Create();
	CRenderObject* Clone(void* pArg);
};

END