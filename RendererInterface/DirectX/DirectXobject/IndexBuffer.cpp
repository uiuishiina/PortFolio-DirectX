#include "IndexBuffer.h"
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
[[nodiscard]] render::dx12::desc::StaticBufferCreateDesc IndexBuffer::create_static_buffer_desc(const void* data, UINT size) {
	
	//	IndexBuffer用リソース作成
	render::dx12::desc::StaticBufferCreateDesc desc{};

	//	バッファサイズをデータサイズ分用意
	desc.resource_desc = helper::ResourceCreateDescHelper::get_buffer_desc(size);

	//	初期データ(今回は作成後変更なし)作成
	desc.initial_data = utility::InitialBufferData(data, size);

	//	最終的なリソース設定を、読み取り専用で作成
	desc.final_state = D3D12_RESOURCE_STATE_GENERIC_READ;

	return desc;
}

//@brief	=== 派生先別リソース作成仮想関数 ===
//@details	基底クラスではS_OKを返す
//@return	作成の成否
[[nodiscard]] HRESULT IndexBuffer::create_resource_object() {

	//	IndexBufferView作成
	index_buffer_view.BufferLocation = get_GPU_address();
	index_buffer_view.SizeInBytes = buffer_size;
	index_buffer_view.Format = format_;

	return S_OK;
}

///====================================================================
/// 実行時処理
///====================================================================

//@brief	=== インデックスバッファビュー取得関数 ===
//@return	インデックスバッファビュー参照
[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW* IndexBuffer::get_buffer_view()const noexcept {
	assert(resource_ && "インデックスバッファリソース nullptr");
	return &index_buffer_view;
}