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
			/// DirectX Graphics Interface
			/// </summary>
			class DXGI final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DXGI() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DXGI() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 初期化関数 -- */

				/// <summary>
				/// DXGI初期化関数
				/// </summary>
				/// <returns>初期化の成否</returns>
				[[nodiscard]] HRESULT initialize_DXGI();

				/* -- 取得関数 -- */

				/// <summary>
				/// DXGIファクトリー取得関数
				/// </summary>
				/// <returns>DXGIファクトリー参照</returns>
				[[nodiscard]] IDXGIFactory6* get_DXGI_factory() const noexcept;

				/// <summary>
				/// DXGIアダプター取得関数
				/// </summary>
				/// <returns>DXGIアダプター参照</returns>
				[[nodiscard]] IDXGIAdapter1* get_DXGI_adaptor() const noexcept;

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

				/// <summary>
				/// DXGIファクトリー作成関数
				/// </summary>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_DXGI_factory();

				/// <summary>
				/// DXGIアダプター作成関数
				/// </summary>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_DXGI_adaptor();

			};
		}
	}
}