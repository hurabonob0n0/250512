#include "..\Public\Bone.h"

CBone::CBone()
{
}

HRESULT CBone::Initialize(const aiNode * pAINode, _int iParentBoneIndex)
{
	strcpy_s(m_szName, pAINode->mName.data);

	memcpy(&m_TransformationMatrix, &pAINode->mTransformation, sizeof(_float4x4));

	XMStoreFloat4x4(&m_TransformationMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_TransformationMatrix)));

	XMStoreFloat4x4(&m_CombindTransformationMatrix, XMMatrixIdentity());

	m_iParentBoneIndex = iParentBoneIndex;

	//std::ofstream fout("../bin/BoneInfo.txt", std::ios::app); // append ���
	//if (fout.is_open())
	//{
	//	fout << g_BoneNum++ << "." << " BoneName: " << m_szName << ", ParentIndex: " << m_iParentBoneIndex << std::endl;
	//	fout.close();
	//}

	return S_OK;
}

void CBone::Invalidate_CombinedTransformationMatrix(const vector<CBone*>& Bones)
{
	if (-1 == m_iParentBoneIndex)
		m_CombindTransformationMatrix = m_TransformationMatrix;

	else
	{
		/* m_CombindTransformationMatrix  = ������ �������(TransformationMatrix) * �θ��� �������(Parent`s CombinedMatrix) */
		XMStoreFloat4x4(&m_CombindTransformationMatrix, 
			XMLoadFloat4x4(&m_TransformationMatrix) * 
			XMLoadFloat4x4(&Bones[m_iParentBoneIndex]->m_CombindTransformationMatrix));
	}
}

CBone * CBone::Create(const aiNode * pAINode, _int iParentBoneIndex)
{
	CBone* pInstance = new CBone();

	if (FAILED(pInstance->Initialize(pAINode, iParentBoneIndex)))
	{
		MSG_BOX("Failed to Created : CBone");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CBone * CBone::Clone()
{
	return new CBone(*this);
}

void CBone::Free()
{
	
}
