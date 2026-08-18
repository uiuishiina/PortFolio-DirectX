#pragma once
#include"DirectXRendererContext.h"
#include"WindowSize.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// DirectXInitializer クラス
		///====================================================================

		//@brief	=== DirectX描画機能初期化クラス ===
		class DirectXInitializer final
		{
		public:
			///====================================================================
			/// Public メンバー関数
			///====================================================================

			/* -- 初期化 -- */

			//@brief	=== 描画機能初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@param	back_buffe_size			バックバッファサイズ
			//@param	frame_resource_size		フレームリソースサイズ
			//@param	hwnd					描画先ウィンドウハンドル
			//@param	window_size				描画先ウィンドウサイズ構造体
			//@return	初期化の成否
			static [[nodiscard]] bool initialze_graphics(DirectXRendererContext* context,
				UINT back_buffe_size, UINT frame_resource_size, HWND hwnd, WindowSize size);

			//@brief	=== 描画機能リソース初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@return	初期化の成否
			static [[nodiscard]] bool initialize_graphics_resource(DirectXRendererContext* context);

			//@breif	=== GPUリソース初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@return	初期化の成否
			static [[nodiscard]] bool initialize_GPU_resource(DirectXRendererContext* context);

			//@brief	=== 描画パス初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@return	初期化の成否
			static [[nodiscard]] bool initialize_draw_pass(DirectXRendererContext* context);


			/* -- 実行時 -- */

			//@brief	=== 描画リソース作成関数 ===
			//@details	描画に利用するリソースをフレームごとにまとめて構造体にする関数
			//@param	context					描画機能インスタンス保存クラス参照
			//@param	current_frame_index		使用するフレームリソースインデックス
			//@return	描画リソース構造体
			static [[nodiscard]] resources::DrawResources create_draw_resources(DirectXRendererContext* context, UINT64 current_frame_index);

		private:
			///====================================================================
			/// クラス設定
			///====================================================================

			//コンストラクタ,デストラクタ
			DirectXInitializer() = default;
			~DirectXInitializer() = default;

			///====================================================================
			/// Private メンバー関数
			///====================================================================

			//@brief	=== シェーダー初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@return	初期化の成否
			static [[nodiscard]] bool compile_shader(DirectXRendererContext* context);

			//@breif	=== 描画パイプライン初期化関数 ===
			//@param	context		描画機能インスタンス保存クラス参照
			//@return	初期化の成否
			static [[nodiscard]] bool initialize_pipline(DirectXRendererContext* context);

		};
	};
};