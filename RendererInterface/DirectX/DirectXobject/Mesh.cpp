#include"Mesh.h"
#include"../AddFile/d3dx12.h"

///====================================================================
/// 実行時処理関数
///====================================================================

//@breif	=== ポリゴン描画関数 ===
//@param	list	描画用コマンドリスト参照
void render::mesh::Mesh::draw_mesh(ID3D12GraphicsCommandList* list) const noexcept {

	list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
	list->IASetIndexBuffer(&index_buffer_view);
	//	プリミティブトポロジーを設定
	list->IASetPrimitiveTopology(topology_);
	//	インデックスバッファを使用して三角形を描画
	list->DrawIndexedInstanced(index_size, 1, 0, 0, 0);
}

///====================================================================
/// 初期化時関数
///====================================================================

//@brief	=== 頂点バッファ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	T_memory_size	データ型サイズ
//@return	作成の成否
[[nodiscard]] HRESULT render::mesh::Mesh::create_vertex_buffer(ID3D12Device* device, UINT T_buffer_size, UINT T_memory_size) {

	const auto heap_propeties =CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto resource_desc = CD3DX12_RESOURCE_DESC::Buffer(T_buffer_size);

	const auto hr= device->CreateCommittedResource(
		&heap_propeties,
		D3D12_HEAP_FLAG_NONE,
		&resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertex_buffer.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return hr;
	}

	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = T_memory_size;
	vertex_buffer_view.SizeInBytes = T_buffer_size;

	return S_OK;
}

//@brief	=== インデックスバッファ作成関数 ===
//@param	device	DirectX12 デバイス
//@param	T_data_size	データ配列サイズ
//@return	作成の成否
[[nodiscard]] HRESULT  render::mesh::Mesh::create_index_buffer(ID3D12Device* device, UINT T_data_size, DXGI_FORMAT format) {

	const auto heap_propeties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	const auto resource_desc = CD3DX12_RESOURCE_DESC::Buffer(T_data_size);

	const auto hr = device->CreateCommittedResource(
		&heap_propeties,
		D3D12_HEAP_FLAG_NONE,
		&resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(index_buffer.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return hr;
	}

	index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
	index_buffer_view.SizeInBytes = T_data_size;
	index_buffer_view.Format = format;

	return S_OK;
}