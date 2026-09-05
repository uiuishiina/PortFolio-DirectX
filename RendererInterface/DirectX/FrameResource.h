#pragma once
#include"DirectXobject/CommandAllocator.h"
#include"DirectXobject/DepthBuffer.h"
#include"Container/StaticHeapContainer.h"
#include<memory>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// 描画リソース名前空間
		/// </summary>
		namespace resources {

			/// <summary>
			/// フレームリソースクラス
			/// </summary>
			struct FrameResource {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// 描画用コマンドアロケータークラスインスタンス
				/// </summary>
				std::unique_ptr<object::CommandAllocator> graphics_allocator{};

				/// <summary>
				/// デプスバッファクラスインスタンス
				/// </summary>
				std::unique_ptr<object::DepthBuffer> depth_buffer{};

				/// <summary>
				/// ディスクリプタヒープコンテナクラスインスタンス
				/// </summary>
				std::unique_ptr<container::StaticHeapContainer> frame_heap_container{};
		
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				FrameResource() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~FrameResource() = default;


				/* ========== Publicメンバー関数 ========== */


				/// <summary>
				/// フレームフェンス保存変数変更関数
				/// </summary>
				/// <param name="value"></param>
				void set_frame_fence_value(const UINT64& value) {
					frame_fence_value = value;
				}

				/// <summary>
				/// フレームフェンス保存変数取得関数
				/// </summary>
				/// <returns>フレームフェンス保存変数の値</returns>
				[[nodiscard]] UINT64 get_frame_fence_value()const noexcept {
					return frame_fence_value;
				}

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// フレームフェンス保存変数
				/// </summary>
				UINT64 frame_fence_value{};

			};
		};
	};
};