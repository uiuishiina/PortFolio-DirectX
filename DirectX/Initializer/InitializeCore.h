#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// コア機能設定構造体
			/// </summary>
			struct CoreDesc {
				
				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// ウィンドウハンドル
				/// </summary>
				HWND hwnd;

				/// <summary>
				/// 横幅
				/// </summary>
				std::uint32_t width;

				/// <summary>
				/// 縦幅
				/// </summary>
				std::uint32_t height;
				
			};
		}

		/// <summary>
		/// コア機能初期化クラス
		/// </summary>
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