#include"FrameResourceFactory.h"


[[nodiscard]] HRESULT FrameResourceFactory::create_frame_resources(ID3D12Device* device,
	UINT size, std::vector<std::unique_ptr<FrameResource>>& out) {

	std::vector<std::unique_ptr<FrameResource>> temp{};
	temp.resize(size);

	for (auto& p : temp) {
		p = std::make_unique<FrameResource>();
		const auto hr = p->create_frame_resource(device);
		if (FAILED(hr)) {
			return hr;
		}
	}

	out = std::move(temp);

	return S_OK;
}