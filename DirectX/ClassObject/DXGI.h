#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DXGIクラス
		/// </summary>
		class DXGI final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DXGI() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DXGI() = default;

			/* ===== 初期化関数 ===== */
			
			/// <summary>
			/// DXGI初期化関数
			/// </summary>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] HRESULT initialize_DXGI() {

				// DXGIファクトリー作成
				auto hr = create_factory();
				if (FAILED(hr)) {
					return hr;
				}

				// DXGIアダプター作成
				hr = create_adaptor();
				if (FAILED(hr)) {
					return hr;
				}

				return hr;
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// DXGIファクトリー参照取得関数
			/// </summary>
			/// <returns>DXGIファクトリー参照</returns>
			[[nodiscard]] IDXGIFactory6* get_factory() const noexcept {

				return factory_.Get();
			}

			/// <summary>
			/// DXGIアダプター参照取得関数
			/// </summary>
			/// <returns>DXGIアダプター参照</returns>
			[[nodiscard]] IDXGIAdapter1* get_adapter() const noexcept {

				return adapter_.Get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// DXGIファクトリーインスタンス
			/// </summary>
			/// <details>
			/// DirectXオブジェクトを生成するためのファクトリーインスタンス
			/// </details>
			Microsoft::WRL::ComPtr<IDXGIFactory6> factory_{};

			/// <summary>
			/// DXGIアダプターインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter_{};

			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// DXGIファクトリー作成関数
			/// </summary>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_factory();

			/// <summary>
			/// DXGIアダプター作成関数
			/// </summary>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_adaptor();

		};
	}
}