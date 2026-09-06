#include"RenderTarget.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// クラス設定
/* ==================================================================== */

/// <summary>
/// コンストラクタ
/// </summary>
/// <details>
/// 基底クラスの引数付きコンストラクタをコンストラクタで呼び出す
/// </details>
RenderTarget::RenderTarget() : TextureResource(D3D12_RESOURCE_STATE_PRESENT) {};

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// RTVハンドル取得関数
/// </summary>
/// <returns>RTV CPUハンドル</returns>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle() const noexcept {
	assert(resource_ && "レンダーターゲット nullptr");
	return rtv_handle;
}
