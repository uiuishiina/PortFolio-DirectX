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
		/// DirectXオブジェクト補助名前空間
		/// </summary>
		namespace utility {

			/// <summary>
			/// 初期設定データ構造体
			/// </summary>
			struct InitialBufferData {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// データ先頭ポインター
				/// </summary>
				const void* data_;

				/// <summary>
				/// 
				/// </summary>
				UINT64 size_;


				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				InitialBufferData() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="data">データ先頭ポインター</param>
				/// <param name="size">データサイズ</param>
				InitialBufferData(
					const void* data,
					UINT64 size
				) : data_{ data }, size_{ size } {}

			};
		}

		/// <summary>
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 初期作成描画バッファリソース設定構造体
			/// </summary>
			struct StaticBufferCreateDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// リソース設定
				/// </summary>
				D3D12_RESOURCE_DESC resource_desc;

				/// <summary>
				/// 初期設定データ構造体
				/// </summary>
				utility::InitialBufferData initial_data;

				/// <summary>
				/// 初期設定後リソースステート
				/// </summary>
				D3D12_RESOURCE_STATES final_state;

			};
		}

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// 初期作成描画バッファリソースクラス
			/// </summary>
			class StaticBufferResource : public GPUResourceBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~StaticBufferResource() = default;

			protected:
				
				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticBufferResource() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// 初期作成描画バッファリソース作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="upload_resource">Uploadリソース参照</param>
				/// <param name="desc">初期設定データ構造体参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_static_buffer(
					ID3D12Device* device, 
					ID3D12GraphicsCommandList* list,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, 
					const desc::StaticBufferCreateDesc& desc
				);

				/* -- 作成補助関数 -- */

				/// <summary>
				/// 設定構造体作成純粋仮想関数
				/// </summary>
				/// <details>
				/// 作成するリソースに必要な設定構造体を派生クラス先で作成できるように
				/// </details>
				/// <param name="data">初期設定データ構造体に設定する先頭ポインター</param>
				/// <param name="size">初期設定データ構造体に設定するメモリサイズ</param>
				/// <returns>作成した構造体</returns>
				[[nodiscard]] virtual desc::StaticBufferCreateDesc create_static_buffer_desc(const void* data, UINT64 size) = 0;

				/// <summary>
				/// 設定構造体作成関数
				/// </summary>
				/// <typeparam name="T">データ型</typeparam>
				/// <param name="data">初期設定データ構造体に設定するデータ配列</param>
				/// <returns>作成した構造体</returns>
				template<typename T>
				[[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(const std::vector<T>& data) {

					//	仮想関数に渡せるようにデータをまとめる
					return create_static_buffer_desc(data.data(), static_cast<UINT64>(data.size() * sizeof(T)));
				}

				/// <summary>
				/// 派生先別リソース作成仮想関数
				/// </summary>
				/// <details>
				/// 基底クラスではS_OKを返す
				/// </details>
				/// <returns>作成の成否</returns>
				[[nodiscard]] virtual HRESULT create_resource_object() { return S_OK; };

			private:
				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// バッファ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="upload_resource">uploadリソース参照</param>
				/// <param name="desc">初期作成バッファ設定</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_buffers(
					ID3D12Device* device,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, 
					const desc::StaticBufferCreateDesc& desc
				);

				/// <summary>
				/// データUpload関数
				/// </summary>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="upload_resource">uploadリソース参照(一時バッファ)</param>
				/// <param name="data">Uploadするデータ参照</param>
				/// <returns>Uploadの成否</returns>
				[[nodiscard]] HRESULT upload_data(
					ID3D12GraphicsCommandList* list,
					ID3D12Resource* upload_resource, 
					const utility::InitialBufferData& data
				);

				/// <summary>
				/// リソースバリア遷移関数
				/// </summary>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="current_state">遷移前バリアステート</param>
				/// <param name="next_state">遷移先バリアステート</param>
				void barrier_transition(
					ID3D12GraphicsCommandList* list, 
					D3D12_RESOURCE_STATES current_state, 
					D3D12_RESOURCE_STATES next_state
				);

			};
		}
	}
}