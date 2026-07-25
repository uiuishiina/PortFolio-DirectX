#pragma once
#include"DirectXobject/CommandAllocator.h"
#include"NonMovable.h"
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

		namespace resouces {

			///====================================================================
			/// FrameResouse クラス
			///====================================================================

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

				//コピー禁止,ムーブ禁止
				FrameResource(const FrameResource&) = delete;
				FrameResource& operator=(const FrameResource&) = delete;
				FrameResource(FrameResource&&) = delete;
				FrameResource& operator=(FrameResource&&) = delete;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== フレームリソース作成関数 ===
				//@param	device	DirectX12 デバイス
				//@return	作成の成否
				[[nodiscard]] HRESULT create_frame_resource(ID3D12Device* device);

				//@brief	=== フレームフェンス保存変数変更関数 ===
				//@param	value	変更する値
				void set_frame_fence_value(const UINT64& value);

				//@brief	=== フレームフェンス保存変数取得関数 ===
				//@return	フレームフェンス保存変数の値
				[[nodiscard]] UINT64 get_frame_fence_value()const noexcept;

				//@brief	===	描画用コマンドアロケータークラス参照取得関数 ===
				//@return	コマンドアロケータークラスインスタンス
				[[nodiscard]] object::CommandAllocator* get_graphics_allocator()const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== フレームフェンス保存変数 ==
				UINT64 frame_fence_value{};

				//@breif	== 描画用コマンドアロケータークラス ==
				std::unique_ptr<object::CommandAllocator> graphics_allocator{};

			};
		};
	};
};