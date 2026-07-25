#pragma once
#include"NonMovable.h"
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

///====================================================================
/// RootSignatureDesc 構造体
///====================================================================

//@brief	=== ルートシグネチャ設定構造体 ===
struct RootSignatureDesc
{
	//@brief	== ルートパラメーター設定配列 ==
	std::vector<D3D12_ROOT_PARAMETER> parameters_;

	//@brief	== サンプラー設定配列 ==
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplers_;

	//@brief	== パイプラインステートフラグ ==
	D3D12_ROOT_SIGNATURE_FLAGS flags_;
};

///====================================================================
/// RootSignature クラス
///====================================================================

//@brief	=== ルートシグネチャクラス ===
class RootSignature final :public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	RootSignature() = default;
	~RootSignature() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ルートシグネチャ作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	desc	ルートシグネチャー設定
	//@return	作成の成否
	[[nodiscard]] HRESULT create_root_signature(ID3D12Device* device, RootSignatureDesc& desc);

	//@brief	=== ルートシグネチャ取得関数 ===
	//@return	ルートシグネチャインスタンス
	[[nodiscard]] ID3D12RootSignature* get_root_signature() const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	=== ルートシグネチャインスタンス ===
	Microsoft::WRL::ComPtr<ID3D12RootSignature> root_signature{};
};