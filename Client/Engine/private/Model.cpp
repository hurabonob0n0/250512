#include "..\Public\Model.h"
#include "Bone.h"
#include "Mesh.h"
#include "Texture.h"
#include "Animation.h"

CModel::CModel(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
	: CComponent(pDevice, pCommandList)
{
}

CModel::CModel(const CModel & rhs)
	: CComponent(rhs)
	, m_iNumMeshes(rhs.m_iNumMeshes)
	, m_Meshes(rhs.m_Meshes)
	, m_eModelType(rhs.m_eModelType)
	, m_PivotMatrix(rhs.m_PivotMatrix)
{
	for (auto& pPrototypeBone : rhs.m_Bones)
	{
		m_Bones.push_back(pPrototypeBone->Clone());
	}

	for (auto& pMesh : m_Meshes)
	{
		pMesh->Set_Bone(m_Bones);
		Safe_AddRef(pMesh);	
	}
}

HRESULT CModel::Initialize_Prototype(TYPE eModelType, const string& strModelFilePath, _fmatrix PivotMatrix)
{
	m_eModelType = eModelType;

	/* aiProcess_PreTransformVertices : */
	/* �� ���� �����ϴ� �޽õ��� Ȥ�� ������ ���´�� �׷������Ѵٸ�.(�޽��� �̸��� ���� �̸��� ���� ���� �����Ѵٸ�) */
	/* �� ������ ����������� �� �޽��� ������ �̸� ���ؼ� �ε��Ѵ�. */
	/* aiProcess_PreTransformVertices�ɼ��� �־ �ε��ϰԵǸ� �̹� ������ ���� ���°� ����Ǿ��ִ°��̴�. */
	/* ���Ŀ� ���� �����̰ԵǸ� ������ ���ִ� �� ���¸� ���� �ִ´ٶ�� �����Ѱ���. */
	/* �׷��� �ش� �ɼ��� �ְ� �ε��ϰԵǸ� �������ü���� �ִϸ��̼ǿ� ���õ� ������ �����ع�����. */
	/* �� �ɼ��� ���� �ε��ϴ� ���� �ݵ�� �ִϸ��̼��� ���� ��쿡�� ó���� �ؾߵǰڴ�. */
	_uint		iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast;

	if (TYPE_NONANIM == eModelType)
		iFlag |= aiProcess_PreTransformVertices;

	/* m_pAIScene�ȿ� .fbx���Ͽ� ����ִ� �������� ����.  */	
	m_pAIScene = m_Importer.ReadFile(strModelFilePath, iFlag);
	if (nullptr == m_pAIScene)
		return E_FAIL;

	XMStoreFloat4x4(&m_PivotMatrix, PivotMatrix);

	/* m_pAIScene�ȿ� ���ִ� �������� �츮�� ����ϱ� ���� ���·� ����, �������ִ� �۾��� �����ϸ� �ǰڴ�. */
	/* mRootNode : ��� ���� ���� �����̵Ǵ� ����. */	
	/* �� ���� ��� ���� ���о��� �� �ε��Ѵ�. */
	/* WHY? ������ ���������� ���� ���� ������ ����. */
	/* ���� �������� = ������ ���� * �θ���� ���� */
	/* ������ ������ �ʿ��ѰԾƴ϶� �� ���� �θ� ��ü �������°�?! */
	/* �θ��ڽİ��� ���� ���� + ���� ���¸� �ε��ϴ� �۾��� Ready_Bones�Լ��� ��Ȱ�̴�. */
	/* aiNode */
	if (FAILED(Ready_Bones(m_pAIScene->mRootNode, -1)))
		return E_FAIL;
	//Todo : ����� ��� �� �� ó��

	/* �� = �޽� + �޽� + ...*/
	/* ������ �޽� = VB, IB */
	/* �ᱹ, �޽��� ������ �ε������� �ε��ϴ� �۾�. VB, IB�� �����Ѵ�. */
	if (FAILED(Ready_Meshes()))
		return E_FAIL;

	
	return S_OK;
}

HRESULT CModel::Initialize(void * pArg)
{
	return S_OK;
}

void CModel::Set_MatOffsets(_uint MatOffset)
{
	for (auto& Mesh : m_Meshes)
		Mesh->Set_MaterialIndexOffset(MatOffset);
}

void CModel::Set_MatIndex(_uint MeshIndex, _uint MatIndex)
{
	m_Meshes[MeshIndex]->Set_MaterialIndex(MatIndex);
}

void CModel::Invalidate_Bones()
{
	for (auto& pBone : m_Bones)
	{
		pBone->Invalidate_CombinedTransformationMatrix(m_Bones);
	}
}

void CModel::Update()
{
	for (auto& mesh : m_Meshes) {
		mesh->Update();
	}
}

/* ������ ���� ���µ��� ���̴��� ������. */
/* Bind_BoneMatrices()�Լ��� ȣ���� Render() �Լ����� ���� ȣ��Ǿ��־���Ѵ�. */
/* ���� �׸��� �������� ���� ���Ÿ� ���󰡾��ϱⶫ���� .*/

/* �������� �׸���. */
HRESULT CModel::Render(_uint iMeshIndex)
{
	/* iMeshIndex�� �ش��ϴ� �޽ÿ� ������ �ִ� ������ ��Ƽ� ���̴��� �����Ѵ�. */
	m_Meshes[iMeshIndex]->Render();

	/*for (auto& Mesh : m_Meshes)
		Mesh->Render();*/

	return S_OK;
}

void CModel::Make_Root_Combined_Matrix(_fmatrix WorldMat)
{
	m_Bones[0]->Set_CombinedMatrix( m_Bones[0]->Get_BoneMatrix() * WorldMat);
}



HRESULT CModel::Ready_Meshes()
{
	/* ���� ���� �����ϴ� �޽��� ����. */
	m_iNumMeshes = m_pAIScene->mNumMeshes;

	m_Meshes.reserve(m_iNumMeshes);

	for (size_t i = 0; i < m_iNumMeshes; i++)
	{
		/* VB, IB�� �����. */
		CMesh*			pMesh = CMesh::Create(m_Device, m_CommandList, m_eModelType, m_pAIScene->mMeshes[i], m_Bones, XMLoadFloat4x4(&m_PivotMatrix));
		if (nullptr == pMesh)
			return E_FAIL;

		m_Meshes.push_back(pMesh);
	}

	return S_OK;
}

HRESULT CModel::Ready_Bones(aiNode* pAINode, _int iParentBoneIndex)
{
	CBone*		pBone = CBone::Create(pAINode, iParentBoneIndex);
	if (nullptr == pBone)
		return E_FAIL;
			
	m_Bones.push_back(pBone);

	_int iParentIndex = m_Bones.size() - 1;

	for (size_t i = 0; i < pAINode->mNumChildren; i++)
	{
		Ready_Bones(pAINode->mChildren[i], iParentIndex);
	}
	return S_OK;
}

void CModel::Set_Matrix_to_Bone(_uint iBoneIndex, _matrix Mat)
{
	m_Bones[iBoneIndex]->Set_TransformationMatrix(Mat);
}

CModel * CModel::Create(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pContext, TYPE eModelType, const string & strModelFilePath, _fmatrix PivotMatrix)
{
	CModel* pInstance = new CModel(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(eModelType, strModelFilePath, PivotMatrix)))
	{
		MSG_BOX("Failed to Created : CModel");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CModel::Clone(void * pArg)
{
	CModel* pInstance = new CModel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CModel");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CModel::Free()
{
	__super::Free();

	for (auto& pBone : m_Bones)
		Safe_Release(pBone);

	m_Bones.clear();

	for (auto& pMesh : m_Meshes)
		Safe_Release(pMesh);

	m_Importer.FreeScene();

}
