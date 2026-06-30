#include"GraphicsCommandObjectFactory.h"
#include"DirectXobject/Device.h"

//@brief	=== 描画用コマンドオブジェクト構造体作成関数 ===
//@param	outout	受け渡すインスタンス
//@return	作成の成否
HRESULT GraphicsCommandObjectFactory::create_GraphicsCommandObject(ID3D12Device* device,GraphicsCommandObject& out) {

	//	CommandQueue作成
	auto hr = out.queue_->create_command_queue(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
	if (FAILED(hr)) {
		return hr;
	}

	//	CommandAllocator作成
	for (auto& p : out.allocators_) {
		hr = p->create_command_allocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
		if (FAILED(hr)) {
			return hr;
		}
	}

	//	GraphicsCommandList作成
	hr = out.list_->create_graphics_command_list(device,
		D3D12_COMMAND_LIST_TYPE_DIRECT, out.allocators_[0]->get_command_allocator());
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;
}