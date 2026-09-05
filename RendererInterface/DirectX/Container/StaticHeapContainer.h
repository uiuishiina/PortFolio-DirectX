#pragma once
#include"../DirectXobject/DescriptorHeap.h"
#include"Others/NonCopyableBase.h"
#include"Container/UnorderedMapBase.h"
#include<vector>
#include<memory>

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// コンテナ名前空間
		/// </summary>
		namespace container {

			/// <summary>
			/// ディスクリプタヒープコンテナクラス
			/// </summary>
			class StaticHeapContainer final : others::NonCopyableBase
			{
			public:
				/* ===== クラス設定 ===== */
				
				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticHeapContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticHeapContainer() = default;


				/* ===== Publicメンバー関数 ===== */
				
				/* -- 作成関数 -- */

				/// <summary>
				/// ディスクリプタヒープコンテナ作成関数
				/// </summary>
				/// <param name="device">デバイスインスタンス</param>
				/// <param name="desc">ディスクリプタヒープ設定配列</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_static_heap_container(ID3D12Device* device, const std::vector<desc::DescriptorHeapDesc>& desc);

				/* -- 取得関数 -- */

				/// <summary>
				/// ディスクリプタヒープ参照取得関数
				/// </summary>
				/// <param name="type">取得したいディスクリプタヒープタイプ</param>
				/// <returns>ディスクリプタヒープ参照</returns>
				[[nodiscard]] object::DescriptorHeap* get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE type);

			private:
				/* ===== Publicメンバー変数 ===== */

				/// <summary>
				/// ディスクリプタヒープマップ
				/// </summary>
				HandyItems::container::UnorderedMapBase<D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<object::DescriptorHeap>> heap_map{};

			};
		}
	}
}