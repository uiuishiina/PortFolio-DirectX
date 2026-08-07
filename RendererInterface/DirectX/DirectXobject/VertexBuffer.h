#pragma once
#include"StaticBufferResource.h"

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
			/// VertexBuffer 派生クラス
			///====================================================================

			//@brief	=== 頂点バッファ派生クラス ===
			class VertexBuffer final : public StaticBufferResource
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				VertexBuffer() = default;
				~VertexBuffer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================
				
				//@brief	=== 頂点バッファ作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	list	描画用コマンドリスト参照
				//@param	upload_resource		Upload用リソース参照
				//@param	buffer_data	頂点バッファに書き込むデータ型配列
				//@return	作成の成否
				template<typename T>
				[[nodiscard]] HRESULT create_vertex_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list, 
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const std::vector<T>& buffer_data);

				//@brief	=== 頂点バッファビュー取得関数 ===
				//@return	頂点バッファビュー参照
				[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			protected:
				///====================================================================
				/// Protected メンバー関数
				///====================================================================

				//@brief	=== 設定構造体作成仮想関数 ===
				//@param	data	初期設定データ構造体に設定する先頭ポインター
				//@param	size	初期設定データ構造体に設定するメモリサイズ
				//@return	作成した構造体
				[[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(const void* data, UINT64 size) override;

				//@brief	=== 派生先別リソース作成仮想関数 ===
				//@details	基底クラスではS_OKを返す
				//@return	作成の成否
				[[nodiscard]] HRESULT create_resource_object() override;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 頂点バッファビュー ==
				D3D12_VERTEX_BUFFER_VIEW	vertex_buffer_view{};

				//@brief	== バッファデータ全体のメモリサイズ保存変数 ==
				UINT buffer_size{};

				//@brief	== バッファデータのクラス型のメモリサイズ保存変数 ==
				UINT class_size{};

			};

			//@brief	=== 頂点バッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	list	描画用コマンドリスト参照
			//@param	upload_resource		Upload用リソース参照
			//@param	buffer_data	頂点バッファに書き込むデータ型配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT VertexBuffer::create_vertex_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list, 
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const std::vector<T>& buffer_data) {

				//	サイズを取得
				class_size = sizeof(T);
				buffer_size = static_cast<UINT>(buffer_data.size() * class_size);
				
				//	リソース設定作成
				const auto desc = create_static_buffer_desc(buffer_data.data(), buffer_size);

				//	リソース作成
				return create_static_buffer(device, list, upload_resource, desc);

			};
		};
	};
};