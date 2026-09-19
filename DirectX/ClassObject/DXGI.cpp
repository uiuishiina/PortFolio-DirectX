
/* ========== Includeファイル ========== */

#include "DXGI.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

using namespace DirectX::ClassObject;

/* ========== Privateメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// DXGIファクトリー作成関数
/// </summary>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT DXGI::create_factory() {

#if _DEBUG
	// デバッグレイヤーオン
	Microsoft::WRL::ComPtr<ID3D12Debug> debug{};
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
		debug->EnableDebugLayer();
	}
#endif

	UINT Flags = 0;
#if _DEBUG
	Flags |= DXGI_CREATE_FACTORY_DEBUG;	// デバッグフラグを設定
#endif

	// DXGIファクトリー作成
	return CreateDXGIFactory2(Flags, IID_PPV_ARGS(&factory_));
}

/// <summary>
/// DXGIアダプター作成関数
/// </summary>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT DXGI::create_adaptor() {

	Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter{};
	SIZE_T max_vram = 0;

	// 最大VRAMを持つアダプターを選択
	for (UINT i = 0; factory_->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {

		DXGI_ADAPTER_DESC1 desc{};
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue; // ソフトウェアアダプターはスキップ
		}
		// 最大VRAMを持つアダプターを選択
		if (desc.DedicatedVideoMemory > max_vram) {
			max_vram = desc.DedicatedVideoMemory;
			adapter_ = adapter;
		}
	}

	// アダプターが見つからなかった場合はエラーを返す
	return adapter_ ? S_OK : E_FAIL;
}