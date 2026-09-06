#pragma once
#include"GPUResource.h"
#include<vector>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// 描画バッファリソース更新可能クラス
			/// </summary>
			class UploadBufferResource : public GPUResourceBase
			{
			protected:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				UploadBufferResource() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~UploadBufferResource() = default;


				/* ========== Protectedメンバー変数 ========== */

				/// <summary>
				/// マップ先ポインター
				/// </summary>
				void* mapped_{};


				/* ========== Protectedメンバー関数 ========== */

				/* -- リソース利用関数 -- */

				/// <summary>
				/// バッファリソースMap関数
				/// </summary>
				/// <returns>Mapの成否</returns>
				[[nodiscard]] HRESULT map_buffer();

				/// <summary>
				/// バッファリソースUnmap関数
				/// </summary>
				void unmap_buffer();


				/* -- 書き込み関数 -- */

				/// <summary>
				/// データUpload関数
				/// </summary>
				/// <param name="src">コピーするデータの先頭ポインター</param>
				/// <param name="size">コピーするメモリサイズ</param>
				void Upload(
					const void* src, 
					size_t size
				);
				
				/// <summary>
				/// データUpload関数
				/// </summary>
				/// <typeparam name="T">データ型</typeparam>
				/// <param name="data">コピーするVector配列参照</param>
				template<class T>
				void Upload(const std::vector<T>&data) {
					Upload(data.data(), data.size() * sizeof(T));
				}

			};
		}
	}
}