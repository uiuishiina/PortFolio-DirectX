#include"RootSignatureDescBuilder.h"

using namespace render::dx12::builder;

///====================================================================
/// 追加関数群
///====================================================================

/* -- ルートパラメーター追加関数群 -- */

//@brief	=== CBV設定追加関数 ===
//@param	desc	設定を追加するインスタンス参照
//@param	shaderRegister	シェーダーレジスター(r0など)
//@param	registerSpace	レジスタースペース
//@param	visibility	参照可能シェーダー設定フラグ
void RootSignatureDescBuilder::add_CBV(desc::RootSignatureDesc& desc, UINT base_shader_register,
	UINT register_space, D3D12_SHADER_VISIBILITY visibility) {

	D3D12_DESCRIPTOR_RANGE r0{};
	r0.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r0.NumDescriptors = 1;
	r0.BaseShaderRegister = base_shader_register;
	r0.RegisterSpace = register_space;
	r0.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	desc.ranges_.push_back(r0);

	D3D12_ROOT_PARAMETER root{};
	root.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	root.ShaderVisibility = visibility;
	root.DescriptorTable.NumDescriptorRanges = 1;
	root.DescriptorTable.pDescriptorRanges = &desc.ranges_.back();

	desc.parameters_.push_back(root);
}



/* -- パイプラインステートフラグ追加関数 -- */

//@brief	=== パイプラインステートフラグ追加関数　===
//@param	desc 設定を追加するインスタンス参照
//@param	flags パイプラインステートフラグ
void RootSignatureDescBuilder::add_flags(desc::RootSignatureDesc& desc, D3D12_ROOT_SIGNATURE_FLAGS flags) {
	desc.flags_ = flags;
}