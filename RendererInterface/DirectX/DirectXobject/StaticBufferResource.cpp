#include "StaticBufferResource.h"
#include"../Factory&Builder&Helper/ResourceCreateDescHelper.h"
#include"../Factory&Builder&Helper/ResourceBarrierHelper.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== 初期作成描画バッファリソース作成関数 ===
//@param	device		DirectX12 デバイス
//@param	commandList	描画用コマンドリスト参照
//@param	upload_resource		Upload用リソース参照
//@param	data		書き込むデータ参照
//@return	作成の成否
[[nodiscard]] HRESULT StaticBufferResource::create_static_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list,
	Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const render::dx12::desc::StaticBufferCreateDesc& desc) {

	//	バッファ作成
	auto hr = create_buffers(device, upload_resource, desc);
	if (FAILED(hr)) {
		return hr;
	}

	//	データ書き込み
	hr = upload_data(list, upload_resource.Get(), desc.initial_data);
	if (FAILED(hr)) {
		return hr;
	}

	//	リソース設定
	barrier_transition(list, D3D12_RESOURCE_STATE_COPY_DEST, desc.final_state);

	//	その他必要処理
	hr = create_resource_object();
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}


//@brief	=== バッファ作成関数 ===
//@param	device		DirectX12 デバイス
//@param	upload_		upload用リソース参照
//@param	desc		初期作成バッファ設定
//@return	作成の成否
[[nodiscard]] HRESULT StaticBufferResource::create_buffers(ID3D12Device* device,
	Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const desc::StaticBufferCreateDesc& desc) {

	//	デフォルト作成( DefaultBuffer )
	desc::ResourceCreateDesc create_desc{};

	create_desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_DEFAULT);
	create_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
	create_desc.resource_desc = desc.resource_desc;
	create_desc.initial_state = D3D12_RESOURCE_STATE_COMMON;	//	BufferはCommon

	auto hr = create_committed_resource(device, create_desc);
	if (FAILED(hr)) {
		return hr;
	}

	//	書き込み用作成( UploadBuffer )
	create_desc.heap_properties = helper::ResourceCreateDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
	create_desc.initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;	//	コピーするために読み取り専用にしておく

	hr = create_committed_resource(device, create_desc, upload_resource);
	if (FAILED(hr)) {
		return hr;
	}

	//	そのまま返していいのだが、見た目の統一のためこのような形に
	return hr;
}

//@brief	=== データUpload関数 ===
//@param	list	描画用コマンドリスト
//@param	upload	upload用リソース参照(一時バッファ)
//@param	data	Uploadするデータ参照
//@return	Uploadの成否
[[nodiscard]] HRESULT StaticBufferResource::upload_data(ID3D12GraphicsCommandList* list,
	ID3D12Resource* upload_resource, const utility::InitialBufferData& data) {
	
	assert(data.data_ && "StaticBufferResource initial_data Not Found");
	assert(data.size_ > 0 && "StaticBufferResource initial_data.size Not Set or 0");

	void* mapped_{};

	//	UploadにMap
	auto hr = upload_resource->Map(0, nullptr, &mapped_);
	if (FAILED(hr)) {
		return hr;
	}

	//	Uploadにコピー
	memcpy(mapped_, data.data_, static_cast<size_t>(data.size_));

	//	UploadをUnmap
	upload_resource->Unmap(0, nullptr);

	//	Defaultにコピー
	list->CopyBufferRegion(
		resource_.Get(),	//コピー先
		0,					//コピー先メモリオフセット
		upload_resource,	//コピー元
		0,					//コピー元メモリオフセット
		data.size_);		//コピーするメモリサイズ

	return hr;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== リソースバリア遷移関数 ===
//@param	list	描画用コマンドリスト
//@param	current_state	遷移前バリアステート
//@param	next_state	遷移先バリアステート
void StaticBufferResource::barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES current_state, D3D12_RESOURCE_STATES next_state) {

	auto barrier = helper::ResourceBarrierHelper::create_resource_barrier(resource_.Get(), current_state, next_state);
	list->ResourceBarrier(1, &barrier);
}