#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"Container/StaticDrawObjectContainer.h"
#include"DirectXobject/RenderTarget.h"
#include"DirectXobject/DepthBuffer.h"
#include"DirectXobject/Mesh.h"
#include"EnumToIndex.h"
#include<array>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		//	描画先を配列で分けるため作成

		//	イメージ
		///	|バックバッファ用インデックス|GBuffer用インデックス|...

		enum class RenderTargetSlot : uint32_t {
			BackBuffer,
			GBuffer,
			Count
		};

		enum class DepthSlot : uint32_t {
			MainDepth,

			Count
		};

		///====================================================================
		/// 描画リソース名前空間
		///====================================================================

		namespace resources {

			//そのフレームで使う描画リソースを保存する構造体

			///====================================================================
			/// DrawResources クラス
			///====================================================================

			//@brief	=== 描画リソース構造体 ===
			struct DrawResources {

				//@brief	== 描画用コマンドリスト参照 ==
				ID3D12GraphicsCommandList* graphics_list{};

				//@brief	== フレームリソースクラス参照 ==
				FrameResource* frame_resource{};

				//@brief	== ディスクリプタヒープコンテナクラス参照 ==
				container::StaticHeapContainer* static_heap_container{};

				//@brief	== 描画オブジェクトコンテナクラス参照 ==
				container::StaticDrawObjectContainer* static_draw_object_container{};

				//@brief	== 描画先参照保存配列 ==
				std::array<object::RenderTarget*, to_index(RenderTargetSlot::Count)> render_targets{};

				//@brief	=== 描画先参照取得補助関数 ===
				object::RenderTarget* get_render_target(RenderTargetSlot slot) const {
					return render_targets[to_index(slot)];
				}
				
			};
		};
	};
};