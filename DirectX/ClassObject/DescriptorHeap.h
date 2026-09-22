#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include<d3d12.h>
#include<wrl/client.h>
#include<utility>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DirectXオブジェクト設定構造体名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// ディスクリプタヒープ設定ラッパー構造体
			/// </summary>
			struct DescriptorHeapDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// ディスクリプターヒープタイプ設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_TYPE type_{};

				/// <summary>
				/// ディスクリプターヒープサイズ設定
				/// </summary>
				UINT numDescriptors_{};

				/// <summary>
				/// シェーダー可視設定
				/// </summary>
				D3D12_DESCRIPTOR_HEAP_FLAGS flags_{};

				/// <summary>
				/// ノードマスク
				/// </summary>
				UINT node_{};

				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DescriptorHeapDesc() = default;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="type">ディスクリプターヒープタイプ設定</param>
				/// <param name="size">ディスクリプターヒープサイズ設定</param>
				/// <param name="flags">シェーダー可視設定</param>
				/// <param name="node">ノードマスク... 初期設定[ 0 ]</param>
				DescriptorHeapDesc(
					D3D12_DESCRIPTOR_HEAP_TYPE type,
					UINT size,
					D3D12_DESCRIPTOR_HEAP_FLAGS flags,
					UINT node = 0
				) :
					type_{ type },
					numDescriptors_{ size },
					flags_{ flags },
					node_{ node } {}

				/* ===== 取得関数 ===== */

				/// <summary>
				/// ディスクリプタヒープ設定構造体取得関数
				/// </summary>
				/// <details>
				/// [ d3d12.h ] 内の構造体に変換する
				/// </details>
				/// <returns>ディスクリプタヒープ設定構造体</returns>
				[[nodiscard]] D3D12_DESCRIPTOR_HEAP_DESC get() const noexcept {

					D3D12_DESCRIPTOR_HEAP_DESC desc_{};
					desc_.Type = type_;
					desc_.NumDescriptors = numDescriptors_;
					desc_.Flags = flags_;
					desc_.NodeMask = node_;

					return desc_;
				}

			};
		}

		/// <summary>
		/// ディスクリプタヒープクラス
		/// </summary>
		class DescriptorHeap final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DescriptorHeap() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DescriptorHeap() = default;
			
			/* ===== 初期化関数 ===== */

			/// <summary>
			/// ディスクリプタヒープ作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="desc">ディスクリプタヒープ設定ラッパー構造体</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_descriptor_heap(
				ID3D12Device* device,
				const desc::DescriptorHeapDesc& desc
			) {

				const auto desc_ = desc.get();

				//	ディスクリプタヒープ作成
				const auto hr = device->CreateDescriptorHeap(&desc_, IID_PPV_ARGS(&heap_));
				if (FAILED(hr)) {
					return hr;
				}

				//	ディスクリプタヒープのメモリサイズを取得
				descriptor_size = device->GetDescriptorHandleIncrementSize(desc.type_);

				max_size = desc.numDescriptors_;

				return hr;
			}

			/* ===== 取得関数 ===== */

			/* -- 本体 -- */

			/// <summary>
			/// ディスクリプタヒープ参照取得関数
			/// </summary>
			/// <returns>ディスクリプタヒープ参照</returns>
			[[nodiscard]] ID3D12DescriptorHeap* get() const noexcept {

				return heap_.Get();
			}

			/// <summary>
			/// ディスクリプタヒープ参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>ディスクリプタヒープ参照</returns>
			[[nodiscard]] ID3D12DescriptorHeap* operator -> () const noexcept {

				return get();
			}

			/* -- ディスクリプタハンドル -- */

			/// <summary>
			/// [ CPU ] ディスクリプタハンドル取得関数
			/// </summary>
			/// <param name="index">取得したいインデックス</param>
			/// <returns>取得した [ CPU ] ディスクリプタハンドル</returns>
			[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_CPU_handle(
				UINT index
			) const noexcept {

				if (max_size <= index) {
					return {};
				}

				D3D12_CPU_DESCRIPTOR_HANDLE handle{};
				handle.ptr = (
					heap_.Get()->GetCPUDescriptorHandleForHeapStart().ptr + 
					index * descriptor_size
					);

				return handle;
			}

			/// <summary>
			///  [ GPU ]ディスクリプタハンドル取得関数
			/// </summary>
			/// <param name="index">取得したいインデックス</param>
			/// <returns>取得した [ GPU ] ディスクリプタハンドル</returns>
			[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE get_GPU_handle(
				UINT index
			) const noexcept {

				if (max_size <= index) {
					return {};
				}

				D3D12_GPU_DESCRIPTOR_HANDLE handle{};
				handle.ptr = (
					heap_.Get()->GetGPUDescriptorHandleForHeapStart().ptr +
					index * descriptor_size
					);

				return handle;
			}

			/// <summary>
			/// ディスクリプタハンドル取得関数
			/// </summary>
			/// <param name="index">取得したいインデックス</param>
			/// <returns>[ CPU ][ GPU ] の構造化束縛</returns>
			[[nodiscard]] std::pair<
				D3D12_CPU_DESCRIPTOR_HANDLE, 
				D3D12_GPU_DESCRIPTOR_HANDLE
			> get_handles(
				UINT index
			) const noexcept {

				return { 
					get_CPU_handle(index),
					get_GPU_handle(index)
				};
			}

			/// <summary>
			/// ディスクリプタハンドル添字演算子オーバーロード
			/// </summary>
			/// <param name="index">取得したいインデックス</param>
			/// <returns>[ CPU ][ GPU ] の構造化束縛</returns>
			[[nodiscard]] std::pair<
				D3D12_CPU_DESCRIPTOR_HANDLE, 
				D3D12_GPU_DESCRIPTOR_HANDLE
			> operator [] (
				std::size_t index
				) const noexcept {

				return get_handles(static_cast<UINT>(index));
			}


		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ディスクリプタヒープメモリサイズ
			/// </summary>
			UINT descriptor_size{};

			/// <summary>
			/// ディスクリプターヒープサイズ
			/// </summary>
			UINT max_size{};

			/// <summary>
			/// ディスクリプタヒープインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};

		};
	}
}