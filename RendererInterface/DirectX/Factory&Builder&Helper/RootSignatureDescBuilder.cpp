#include"RootSignatureDescBuilder.h"

using namespace render::dx12::builder;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- ルートパラメーター追加関数群 -- */

/// <summary>
/// CBV設定追加関数
/// </summary>
/// <param name="desc">設定構造体参照</param>
/// <param name="shaderRegister">シェーダーレジスター(r0など)</param>
/// <param name="registerSpace">レジスタースペース</param>
/// <param name="visibility">参照可能シェーダー設定フラグ</param>
void RootSignatureDescBuilder::add_CBV(
	desc::RootSignatureDesc& desc,
	UINT base_shader_register,
	UINT register_space, 
	D3D12_SHADER_VISIBILITY visibility
) {

	D3D12_ROOT_PARAMETER root{};
	root.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	root.ShaderVisibility = visibility;
	root.Descriptor.ShaderRegister = base_shader_register;
	root.Descriptor.RegisterSpace = register_space;

	desc.parameters_.push_back(root);
}


/* -- サンプラー追加関数群 -- */



/* -- パイプラインステートフラグ追加関数 -- */

/// <summary>
/// パイプラインステートフラグ追加関数
/// </summary>
/// <param name="desc">設定構造体参照</param>
/// <param name="flags">パイプラインステートフラグ</param>
void RootSignatureDescBuilder::add_flags(
	desc::RootSignatureDesc& desc,
	D3D12_ROOT_SIGNATURE_FLAGS flags
) {
	desc.flags_ = flags;
}