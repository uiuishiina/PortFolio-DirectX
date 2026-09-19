#pragma once

/* ========== Includeファイル ========== */

#include"../DirectXContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	namespace Initialize {

		class InitializeCore
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializeCore() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializeCore() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// コア機能初期化関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] virtual HRESULT initialize_core(
				DirectXContext* context
			) {

				void* value[2] = {
					context->dxgi_.get(),
					context->device_.get()
				};

				for (auto p : value) {
					if (!p) {
						return E_FAIL;
					}
				}

				HRESULT hr{};

				//	DXGI作成
				hr = context->dxgi_->initialize_DXGI();
				if (FAILED(hr)) {
					return hr;
				}

				//	Device作成
				hr = context->device_->create_device(context->dxgi_->get_adapter());
				if (FAILED(hr)) {
					return hr;
				}



				return S_OK;
			}

		};
	}
}