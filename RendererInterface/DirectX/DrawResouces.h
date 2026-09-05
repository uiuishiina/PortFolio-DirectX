#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"Container/StaticDrawObjectContainer.h"
#include"DirectXobject/RenderTarget.h"
#include"DirectXobject/DepthBuffer.h"
#include"DirectXobject/Mesh.h"
#include"Enum/EnumToIndex.h"
#include<array>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		//	描画先を配列で分けるため作成

		//	イメージ
		///	|バックバッファ用インデックス|GBuffer用インデックス|...

		/// <summary>
		/// レンダーターゲット識別用列挙体
		/// </summary>
		enum class RenderTargetSlot : uint32_t {
			BackBuffer,
			GBuffer,
			Count
		};

		/// <summary>
		/// デプスバッファ識別用列挙体
		/// </summary>
		enum class DepthSlot : uint32_t {
			MainDepth,

			Count
		};

		/// <summary>
		/// 描画リソース名前空間
		/// </summary>
		namespace resources {

			/// <summary>
			/// 描画リソース構造体
			/// </summary>
			/// <details>
			/// そのフレームで使う描画リソースを保存する構造体
			/// </details>
			struct DrawResources {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// 描画用コマンドリスト参照
				/// </summary>
				ID3D12GraphicsCommandList* graphics_list{};

				/// <summary>
				/// フレームリソースクラス参照
				/// </summary>
				FrameResource* frame_resource{};

				/// <summary>
				/// ディスクリプタヒープコンテナクラス参照
				/// </summary>
				container::StaticHeapContainer* static_heap_container{};

				/// <summary>
				/// 描画オブジェクトコンテナクラス参照
				/// </summary>
				container::StaticDrawObjectContainer* static_draw_object_container{};

				/// <summary>
				/// 描画先参照保存配列
				/// </summary>
				std::array<object::RenderTarget*, HandyItems::Enum::enum_to_index(RenderTargetSlot::Count)> render_targets{};


				/* ========== メンバー関数 ========== */

				/// <summary>
				/// 描画先参照取得補助関数
				/// </summary>
				/// <param name="slot">レンダーターゲット識別用列挙体</param>
				/// <returns>配列から取得した参照</returns>
				object::RenderTarget* get_render_target(RenderTargetSlot slot) const {
					return render_targets[HandyItems::Enum::enum_to_index(slot)];
				}
				
			};
		}
	}
}