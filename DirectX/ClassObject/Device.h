#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>
#include<utility>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {


		class Device final : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Device() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~Device() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// デバイス作成関数
			/// </summary>
			/// <param name="adapter_">DXGIアダプター参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_device(
				IDXGIAdapter1* adapter_
			);

			/* ===== 取得関数 ===== */

			/// <summary>
			/// デバイス参照取得関数
			/// </summary>
			/// <returns>デバイス参照</returns>
			[[nodiscard]] ID3D12Device* get_device() const noexcept {
				return device_.Get();
			}

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
			std::pair<D3D_FEATURE_LEVEL,const char*> levels_[3] = {

			{D3D_FEATURE_LEVEL_12_2,"D3D_FEATURE_LEVEL_12_2"},	//	49664
			{D3D_FEATURE_LEVEL_12_1,"D3D_FEATURE_LEVEL_12_1"},	//	49408
			{D3D_FEATURE_LEVEL_12_0,"D3D_FEATURE_LEVEL_12_0"}	//	49152
			
			};

			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// レベル選択関数
			/// </summary>
			/// <param name="adapter_">DXGIアダプター参照</param>
			/// <param name="level">D3D機能レベル</param>
			/// <returns>作成したDevice... 失敗なら[ nullptr ]</returns>
			[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Device> select_level(
				IDXGIAdapter1* adapter_,
				D3D_FEATURE_LEVEL level
			);

		};
	}
}