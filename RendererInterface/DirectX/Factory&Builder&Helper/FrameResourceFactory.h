#pragma once
#include"../FrameResource.h"
#include"../DirectXRendererContext.h"
#include"WindowSize.h"
#include<vector>
#include<memory>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// Factory名前空間
		///====================================================================

		namespace factory {

			///====================================================================
			/// FrameResourceFactory クラス
			///====================================================================

			//@brief	=== フレームリソースファクトリークラス ===
			class FrameResourceFactory final
			{
			public:
				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== フレームリソース作成関数 ===
				//@param	context		DirectX描画機能インスタンス保存クラス
				//@param	window_size	ウィンドウサイズ
				//@param	size		フレームリソースサイズ
				//@param	heaps_desc	ディスクリプタヒープ設定配列
				//@return	作成の成否
				static [[nodiscard]] HRESULT create_frame_resources(DirectXRendererContext* context,
					WindowSize window_size, UINT size, const std::vector<desc::DescriptorHeapDesc>& heaps_desc);

			private:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				FrameResourceFactory() = default;
				~FrameResourceFactory() = default;

			};
		};
	};
};