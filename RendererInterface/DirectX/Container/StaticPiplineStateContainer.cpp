#include "StaticPiplineStateContainer.h"

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// パイプラインステート作成関数
/// </summary>
/// <param name="key">追加したい倫理側のキー</param>
/// <param name="device">DirectX12デバイスポインター</param>
/// <param name="desc">パイプラインステート設定</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT StaticPiplineStateContainer::create_pipline_state(const handle::PiplineStateKey& key, ID3D12Device* device, desc::PipelineStateDesc& desc) {
    
    //  パイプラインステート作成
    auto pipline = std::make_unique<object::PipelineState>();
    const auto hr = pipline->create_piplinestate(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    return add_value(key, std::move(pipline)) ? S_OK : E_FAIL;
}
