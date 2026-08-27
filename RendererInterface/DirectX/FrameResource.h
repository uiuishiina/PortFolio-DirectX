#pragma once
#include"DirectXobject/CommandAllocator.h"
#include"DirectXobject/DepthBuffer.h"
#include"Container/StaticHeapContainer.h"
#include"Container/UploadBufferContainer.h"
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
		/// 描画リソース名前空間
		///====================================================================

		namespace resources {

			///====================================================================
			/// FrameResouse クラス
			///====================================================================
			
			//	GPUが非同期に動く際に同時利用しないようにする

			//@brief	=== フレームリソースクラス ===
			class FrameResource final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				FrameResource() = default;
				~FrameResource() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== フレームリソース作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	depth_desc	デプスバッファ設定
				//@param	heaps_desc	ディスクリプタヒープ設定配列
				//@return	作成の成否
				[[nodiscard]] HRESULT create_frame_resource(
					ID3D12Device* device,
					desc::DepthBufferDesc depth_desc, const std::vector<desc::DescriptorHeapDesc>& heaps_desc);

				//@brief	=== フレームフェンス保存変数変更関数 ===
				//@param	value	変更する値
				void set_frame_fence_value(const UINT64& value);

				//@brief	=== フレームフェンス保存変数取得関数 ===
				//@return	フレームフェンス保存変数の値
				[[nodiscard]] UINT64 get_frame_fence_value()const noexcept;

				//@brief	===	描画用コマンドアロケータークラス取得関数 ===
				//@return	コマンドアロケータークラス参照
				[[nodiscard]] object::CommandAllocator* get_graphics_allocator()const noexcept;

				//@brief	===	デプスバッファクラス取得関数 ===
				//@return	デプスバッファクラス参照
				[[nodiscard]] object::DepthBuffer* get_deprh_buffer()const noexcept;

				[[nodiscard]] container::StaticHeapContainer* get_heap_container()const noexcept {
					return frame_heap_container.get();
				}

				[[nodiscard]] container::UploadBufferContainer* get_upload_container()const noexcept {
					return upload_resource_container.get();
				}

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== フレームフェンス保存変数 ==
				UINT64 frame_fence_value{};

				//@breif	== 描画用コマンドアロケータークラスインスタンス ==
				std::unique_ptr<object::CommandAllocator> graphics_allocator{};

				//@brief	== デプスバッファクラスインスタンス ==
				std::unique_ptr<object::DepthBuffer> depth_buffer{};

				//@brief	== ディスクリプタヒープコンテナクラスインスタンス ==
				std::unique_ptr<container::StaticHeapContainer> frame_heap_container{};


				std::unique_ptr<container::UploadBufferContainer> upload_resource_container{};

			};
		};
	};
};