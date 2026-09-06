#pragma once
#include"Others/NonCopyableBase.h"
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// DirectX Device
			/// </summary>
			class Device final :public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				Device() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~Device() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 初期化関数 -- */

				/// <summary>
				/// Device初期化関数
				/// </summary>
				/// <param name="adapter_">DXGIアダプター参照</param>
				/// <returns>初期化の成否</returns>
				[[nodiscard]] HRESULT initialize_Device(IDXGIAdapter1* adapter_);


				/* -- 取得関数 -- */

				/// <summary>
				/// Device取得関数
				/// </summary>
				/// <returns>Device参照</returns>
				[[nodiscard]] ID3D12Device* get_device() const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// Deviceインスタンス
				/// </summary>
				/// <details>
				/// DirectXオブジェクトを生成するためのDeviceインスタンス
				/// </details>
				Microsoft::WRL::ComPtr<ID3D12Device> device_{};

				/// <summary>
				/// 要求するD3D機能レベルのリスト...DirectX 12.2からDirectX 11.0までの機能レベルを指定
				/// </summary>
				D3D_FEATURE_LEVEL levels[5] = {

				D3D_FEATURE_LEVEL_12_2,	//	49664
				D3D_FEATURE_LEVEL_12_1,	//	49408
				D3D_FEATURE_LEVEL_12_0,	//	49152
				D3D_FEATURE_LEVEL_11_1,	//	45056
				D3D_FEATURE_LEVEL_11_0	//	40960

				};


				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// Device作成関数
				/// </summary>
				/// <param name="adapter_">DXGIアダプター参照</param>
				/// <param name="featureLevel">D3D機能レベル</param>
				/// <returns>Deviceインスタンス</returns>
				Microsoft::WRL::ComPtr<ID3D12Device> create_device(
					IDXGIAdapter1* adapter_, 
					D3D_FEATURE_LEVEL featureLevel
				);

			};
		}
	}
}