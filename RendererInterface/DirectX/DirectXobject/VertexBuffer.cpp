#include "VertexBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化処理
///====================================================================

//@brief	=== 設定構造体作成仮想関数 ===
//@param	data	初期設定データ構造体に設定する先頭ポインター
//@param	size	初期設定データ構造体に設定するメモリサイズ
//@return	作成した構造体
[[nodiscard]] render::dx12::desc::StaticBufferCreateDesc VertexBuffer::create_static_buffer_desc(const void* data, UINT64 size) {

	render::dx12::desc::StaticBufferCreateDesc desc{};
	desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(size);
	desc.initial_data = utility::InitialBufferData(data, size);
	desc.final_state = D3D12_RESOURCE_STATE_GENERIC_READ;
	return desc;
}

//@brief	=== 派生先別リソース作成仮想関数 ===
//@details	基底クラスではS_OKを返す
//@return	作成の成否
[[nodiscard]] HRESULT VertexBuffer::create_resource_object() {

	vertex_buffer_view.BufferLocation = get_GPU_address();
	vertex_buffer_view.StrideInBytes = class_size;
	vertex_buffer_view.SizeInBytes = buffer_size;

	return S_OK;
}

///====================================================================
/// 実行時処理
///====================================================================

//@brief	=== 頂点バッファビュー取得関数 ===
//@return	頂点バッファビュー参照
[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::get_buffer_view()const noexcept {
	assert(resource_ && "頂点バッファリソース nullptr");
	return &vertex_buffer_view;
}