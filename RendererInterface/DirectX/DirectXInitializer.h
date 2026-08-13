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