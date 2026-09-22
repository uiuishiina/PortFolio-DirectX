#pragma once

/* ========== Includeファイル ========== */

#include"../DirectXContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	namespace Initialize {

		namespace desc {

			struct CoreDesc {

				HWND hwnd;
				std::uint32_t width;
				std::uint32_t height;
				
			};
		}

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
			[[nodiscard]] HRESULT initialize_core(
				DirectXContext* context,
				std::uint32_t back_buffer_size,
				desc::CoreDesc& desc
			);

		};
	}
}