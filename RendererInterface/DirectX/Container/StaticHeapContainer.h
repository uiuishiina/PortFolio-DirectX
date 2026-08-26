#pragma once
#include"../DirectXobject/DescriptorHeap.h"
#include"../DirectXobject/ResourceUtility.h"
#include"NonMovable.h"
#include<unordered_map>
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
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			///====================================================================
			/// StaticHeapContainer クラス
			///====================================================================

			//@brief	=== 初期作成ディスクリプタヒープコンテナクラス ===
			class StaticHeapContainer final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticHeapContainer() = default;
				~StaticHeapContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== ディスクリプタヒープコンテナ作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	desc	ディスクリプタヒープ設定配列
				//@return	作成の可否
				[[nodiscard]] HRESULT create_static_heap_container(ID3D12Device* device, const std::vector<desc::DescriptorHeapDesc>& desc);

				//@brief	=== ディスクリプタヒープ参照取得関数 ===
				//@param	type	ディスクリプターヒープタイプ
				//@return	ディスクリプターヒープポインター
				[[nodiscard]] object::DescriptorHeap* get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE type);

				[[nodiscard]] utility::Descripter_Handles get_handles(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT index);

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== ディスクリプタヒープマップ ==
				std::unordered_map<D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<object::DescriptorHeap>> static_heap_map{};

			};
		};
	};
};