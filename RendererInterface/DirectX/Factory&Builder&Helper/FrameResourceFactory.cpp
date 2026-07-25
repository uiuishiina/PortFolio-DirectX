#include"FrameResourceFactory.h"

using namespace render::dx12::factory;

//@brief	=== フレームリソース作成関数 ===
//@param	device	DirectX12 デバイス
//@param	size	フレームリソースサイズ
//@param	out	受け渡すインスタンス
//@return	作成の成否
[[nodiscard]] HRESULT FrameResourceFactory::create_frame_resources(ID3D12Device* device,
	UINT size, std::vector<std::unique_ptr<resouces::FrameResource>>& out) {

	//	仮配列を作成
	std::vector<std::unique_ptr<resouces::FrameResource>> temp{};
	temp.resize(size);

	//	サイズ分インスタンス & リソース作成
	for (auto& p : temp) {
		p = std::make_unique<resouces::FrameResource>();
		const auto hr = p->create_frame_resource(device);
		if (FAILED(hr)) {
			return hr;
		}
	}

	//	作成できたならMoveで受け渡し
	out = std::move(temp);

	return S_OK;
}