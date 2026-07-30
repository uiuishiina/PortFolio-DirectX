#include"RenderTarget.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// クラス設定
///====================================================================

//@brief	=== コンストラクタ ==
//@details	基底クラスの引数付きコンストラクタをコンストラクタで呼び出す
RenderTarget::RenderTarget() : TextureResource(D3D12_RESOURCE_STATE_PRESENT) {};

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== RTVハンドル取得関数 ===
//@return	RTV_CPUハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle() const noexcept {
	assert(resource_ && "レンダーターゲット nullptr");
	return rtv_handle;
}
