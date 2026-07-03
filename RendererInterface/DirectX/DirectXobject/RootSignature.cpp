#include"RootSignature.h"

#include"../../../Debug/DebugLogSystem.h"
#include<cassert>

///====================================================================
/// 初期化時処理関数
///====================================================================

//@brief	=== ルートシグネチャ作成関数 ===
//@param	device	DirectX12 デバイス
//@return	作成の成否
[[nodiscard]] HRESULT RootSignature::create_root_signature(ID3D12Device* device, RootSignatureDesc& desc) {

	//	ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC root_desc{};

	//	ルートパラメーラー設定
	root_desc.NumParameters = static_cast<UINT>(desc.parameters_.size());
	root_desc.pParameters = desc.parameters_.data();

	//	サンプラー設定
	root_desc.NumStaticSamplers = static_cast<UINT>(desc.samplers_.size());
	root_desc.pStaticSamplers = desc.samplers_.data();

	//	パイプラインステートフラグ設定
	root_desc.Flags = desc.flags_;

	//	ルートシグネチャのシリアライズ
	Microsoft::WRL::ComPtr<ID3DBlob> serialized;
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob;
	auto hr = D3D12SerializeRootSignature(&root_desc, D3D_ROOT_SIGNATURE_VERSION_1, &serialized, &error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			DEBUG_ERROR_LOG(static_cast<const char*>(error_blob.Get()->GetBufferPointer()));
		}
		return hr;
	}

	//	ID3D12RootSignatureの作成
	hr = device->CreateRootSignature(0,serialized->GetBufferPointer(),serialized->GetBufferSize(),IID_PPV_ARGS(&root_signature));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== ルートシグネチャ取得関数 ===
//@return	ルートシグネチャインスタンス
[[nodiscard]] ID3D12RootSignature* RootSignature::get_root_signature() const noexcept {
	assert(root_signature && "ルートシグネチャ nullptr");
	return root_signature.Get();
}