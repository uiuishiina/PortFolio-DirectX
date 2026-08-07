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
		/// DirectXオブジェクト補助名前空間
		///====================================================================

		namespace utility {

			///====================================================================
			/// InitialBufferData 構造体
			///====================================================================

			//@brief	=== 初期設定データ構造体 ===
			struct InitialBufferData
			{
				//@brief	== データ先頭ポインター ==
				const void* data_;

				//@brief	== データサイズ ==
				UINT64 size_;

				//@brief	=== コンストラクタ ===
				InitialBufferData() = default;
				InitialBufferData(const void* data, UINT64 size) :
					data_(data), size_(size) {};

			};
		};

		///====================================================================
		/// DX12オブジェクト設定名前空間
		///====================================================================

		namespace desc {

			///====================================================================
			/// StaticBufferCreateDesc 構造体
			///====================================================================

			//@brief	=== 初期作成描画バッファリソース設定構造体 ===
			struct StaticBufferCreateDesc
			{
				//@brief	== リソース設定 ==
				D3D12_RESOURCE_DESC resource_desc;

				//@brief	== 初期設定データ構造体 ==
				utility::InitialBufferData initial_data;

				//@brief	== 初期設定後リソースステート ==
				D3D12_RESOURCE_STATES final_state;
			};
		};

		///====================================================================
		/// DX12オブジェクトラッパークラス名前空間
		///====================================================================

		namespace object {

			///====================================================================
			/// StaticBufferResource 基底クラス
			///====================================================================

			//@brief	=== 初期作成描画バッファリソースクラス ===
			class StaticBufferResource : public GPUResourceBase
			{
			protected:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticBufferResource() = default;
				virtual ~StaticBufferResource() = default;

				///====================================================================
				/// Protected メンバー関数
				///====================================================================

				//@brief	=== 初期作成描画バッファリソース作成関数 ===
				//@param	device		DirectX12 デバイス
				//@param	commandList	描画用コマンドリスト参照
				//@param	upload_resource		Upload用リソース参照
				//@param	data		書き込むデータ参照
				//@return	作成の成否
				[[nodiscard]] HRESULT create_static_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const desc::StaticBufferCreateDesc& desc);

				//@brief	=== 設定構造体作成仮想関数 ===
				//@param	data	初期設定データ構造体に設定する先頭ポインター
				//@param	size	初期設定データ構造体に設定するメモリサイズ
				//@return	作成した構造体
				virtual [[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(const void* data, UINT64 size) = 0;

				//@brief	=== 設定構造体作成仮想関数 ===
				//@param	data	初期設定データ構造体に設定する先頭ポインター
				//@return	作成した構造体
				template<typename T>
				[[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(const std::vector<T>& data);

				//@brief	=== 派生先別リソース作成仮想関数 ===
				//@details	基底クラスではS_OKを返す
				//@return	作成の成否
				virtual [[nodiscard]] HRESULT create_resource_object() { return S_OK; };

			private:
				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	=== バッファ作成関数 ===
				//@param	device		DirectX12 デバイス
				//@param	upload_		upload用リソース参照
				//@param	desc		初期作成バッファ設定
				//@return	作成の成否
				[[nodiscard]] HRESULT create_buffers(ID3D12Device* device,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const desc::StaticBufferCreateDesc& desc);

				//@brief	=== データUpload関数 ===
				//@param	list	描画用コマンドリスト
				//@param	upload	upload用リソース参照(一時バッファ)
				//@param	data	Uploadするデータ参照
				//@return	Uploadの成否
				[[nodiscard]] HRESULT upload_data(ID3D12GraphicsCommandList* list,
					ID3D12Resource* upload_resource, const utility::InitialBufferData& data);

				//@brief	=== リソースバリア遷移関数 ===
				//@param	list	描画用コマンドリスト
				//@param	current_state	遷移前バリアステート
				//@param	next_state		遷移先バリアステート
				void barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES current_state, D3D12_RESOURCE_STATES next_state);

			};

			template<typename T>
			[[nodiscard]] desc::StaticBufferCreateDesc StaticBufferResource::create_static_buffer_desc(const std::vector<T>& data) {
				return create_static_buffer_desc(data.data(), static_cast<UINT64>(data.size() * sizeof(T)));
			}
		};
	};
};