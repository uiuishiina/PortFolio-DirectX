#pragma once
#include"DirectXRendererContext.h"
#include"WindowSize.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DirectX描画機能初期化クラス
		/// </summary>
		class DirectXInitializer final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* -- 初期化 -- */

			/// <summary>
			/// 描画機能初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <param name="back_buffe_size">バックバッファサイズ</param>
			/// <param name="frame_resource_size">フレームリソースサイズ</param>
			/// <param name="hwnd">描画先ウィンドウハンドル</param>
			/// <param name="size">描画先ウィンドウサイズ構造体</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool initialze_graphics(DirectXRendererContext* context,
				UINT back_buffe_size, UINT frame_resource_size, HWND hwnd, WindowSize size);

			/// <summary>
			/// 描画機能リソース初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool initialize_graphics_resource(DirectXRendererContext* context);

			/// <summary>
			/// GPUリソース初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool initialize_GPU_resource(DirectXRendererContext* context);

			/// <summary>
			/// 描画パス初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool initialize_draw_pass(DirectXRendererContext* context);

			/// <summary>
			/// 描画パス順取得関数
			/// </summary>
			/// <details>
			/// 内部でグローバル変数で保持(この先設計変更になる可能性あり)
			/// </details>
			/// <returns>初期化時に作った描画パス順配列</returns>
			static [[nodiscard]] std::vector<std::string> get_draw_pass_order() noexcept;


			/* -- 実行時 -- */

			/// <summary>
			/// 描画リソース作成関数
			/// </summary>
			/// <details>
			/// 描画に利用するリソースをフレームごとにまとめて構造体にする関数
			/// </details>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <param name="current_frame_index">使用するフレームリソースインデックス</param>
			/// <returns>描画リソース構造体</returns>
			static [[nodiscard]] resources::DrawResources create_draw_resources(DirectXRendererContext* context, UINT64 current_frame_index);

		private:
			/* ========== クラス設定 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DirectXInitializer() = default;

			/// <summary>
			/// コンストラクタ
			/// </summary>
			~DirectXInitializer() = default;


			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// シェーダー初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool compile_shader(DirectXRendererContext* context);

			/// <summary>
			/// 描画パイプライン初期化関数
			/// </summary>
			/// <param name="context">描画機能インスタンス保存クラス参照</param>
			/// <returns>初期化の成否</returns>
			static [[nodiscard]] bool initialize_pipline(DirectXRendererContext* context);

		};
	}
}