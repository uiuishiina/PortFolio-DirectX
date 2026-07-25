#pragma once
#include"../DirectXobject/CommandQueue.h"
#include"../DirectXobject/CommandAllocator.h"
#include"../DirectXobject/GraphicsCommandList.h"
#include<memory>
#include<vector>

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
			/// CommandObjectFactoryクラス
			///====================================================================

			//@brief	=== コマンドオブジェクトファクトリー ===
			class CommandObjectFactory final
			{
			public:
				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== 描画用コマンドキュー作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	out	受け渡すインスタンス
				//@return	作成の成否
				static [[nodiscard]] HRESULT create_graphics_command_queue(ID3D12Device* device, object::CommandQueue& out);

				//@brief	=== 描画用コマンドアロケーター作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	out	受け渡すインスタンス
				//@return	作成の成否
				static [[nodiscard]] HRESULT create_graphics_command_allocator(ID3D12Device* device, object::CommandAllocator& out);

				//@brief	=== 描画用コマンドリスト作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	allocator	作成に利用する描画用アロケーター
				//@param	out	受け渡すインスタンス
				//@return	作成の成否
				static [[nodiscard]] HRESULT create_graphics_command_list(ID3D12Device* device,
					ID3D12CommandAllocator* allocator, object::GraphicsCommandList& out);

			private:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				CommandObjectFactory() = default;
				~CommandObjectFactory() = default;

			};
		};
	};
};