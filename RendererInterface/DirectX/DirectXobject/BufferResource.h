#pragma once
#include"GPUResource.h"
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
		/// DX12オブジェクトラッパークラス名前空間
		///====================================================================

		namespace object {

			///====================================================================
			/// BufferResource 基底クラス
			///====================================================================

			//@brief	=== 描画バッファリソースクラス ===
			class BufferResource : public GPUResourceBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				BufferResource() = default;
				virtual ~BufferResource() = default;

			protected:
				///====================================================================
				/// Protected メンバー関数
				///====================================================================

				//@brief	=== バッファリソースMap関数 ===
				//@param	ptr	Map先ポインター
				//@return	Mapの成否
				[[nodiscard]] HRESULT map_buffer(void** ptr);

				//@brief	=== バッファリソースUnmap関数 ===
				void unmap_buffer();

				//@brief	=== バッファリソースコピー関数 ===
				//@details	Map後、メモリにコピーしてUnmapする関数
				//@param	src	コピーするデータの先頭ポインター
				//@param	size	コピーするメモリサイズ
				//@return	コピーの成否
				[[nodiscard]] HRESULT copy_buffer(const void* src, size_t size);

				//@brief	=== バッファリソースコピー関数オーバーロード ===
				//@param	data	コピーするVector配列参照
				//@return	コピーの成否
				template<class T>
				[[nodiscard]]HRESULT copy_buffer(const std::vector<T>& data) {
					return copy_buffer(data.data(), data.size() * sizeof(T));
				}

				//@brief	=== GPUアドレス取得関数 ===
				//@return	GPUアドレス
				[[nodiscard]] D3D12_GPU_VIRTUAL_ADDRESS get_GPU_address() const noexcept;

			};
		};
	};
};