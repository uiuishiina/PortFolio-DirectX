#include "VertexBuffer.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// 設定構造体作成関数
/// </summary>
/// <param name="data">初期設定データ構造体に設定する先頭ポインター</param>
/// <param name="size">初期設定データ構造体に設定するメモリサイズ</param>
/// <returns>作成した構造体</returns>
[[nodiscard]] render::dx12::desc::StaticBufferCreateDesc VertexBuffer::create_static_buffer_desc(
	const void* data, 
	UINT64 size
) {

	//	VerTexBuffer用リソース設定作成
	render::dx12::desc::StaticBufferCreateDesc desc{};

	//	バッファサイズをデータサイズ分用意
	desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(size);

	//	初期データ(今回は作成後変更なし)作成
	desc.initial_data = utility::InitialBufferData(data, size);

	//	最終的なリソース設定を、読み取り専用で作成
	desc.final_state = D3D12_RESOURCE_STATE_GENERIC_READ;

	return desc;
}

/// <summary>
/// 派生先別リソース作成仮想関数
/// </summary>
/// <details>
/// ここでは頂点バッファビューを作成
/// </details>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT VertexBuffer::create_resource_object() {

	//	VertexBufferViweを作成
	vertex_buffer_view.BufferLocation = get_GPU_address();
	vertex_buffer_view.StrideInBytes = class_size;
	vertex_buffer_view.SizeInBytes = static_cast<UINT>(buffer_size);

	return S_OK;
}


/* -- 取得関数 -- */

//@brief	=== 頂点バッファビュー取得関数 ===
//@return	頂点バッファビュー参照
[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::get_buffer_view()const noexcept {
	assert(resource_ && "頂点バッファリソース nullptr");
	return &vertex_buffer_view;
}