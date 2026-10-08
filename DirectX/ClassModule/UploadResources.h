#pragma once


/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"Container/ReferenceQueue.h"

#include<d3d12.h>
#include<wrl/client.h>

#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// UploadResource確保クラス
		/// </summary>
		class UploadResources final : HandyItems::others::NonCopyableBase
		{
			using Resource = Microsoft::WRL::ComPtr<ID3D12Resource>;
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			UploadResources() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="size">初期確保サイズ</param>
			UploadResources(
				std::size_t size
			) {
				add_upload(size);
				reference_.add_references(upload_);
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~UploadResources() = default;

			/* ===== 取得関数 ===== */

			/// <summary>
			/// Upload参照確保関数
			/// </summary>
			/// <returns>確保したUpload参照</returns>
			[[nodiscard]] std::reference_wrapper<Resource> allocate_reference() {

				if (auto value = reference_.get_reference();
					value.has_value()
					) {
					return value->get();
				}
				else {
					add_upload(5);
					return allocate_reference();
				}

			}

			/// <summary>
			/// Upload参照配列確保関数
			/// </summary>
			/// <param name="size">確保するサイズ</param>
			/// <returns>確保したUpload参照配列</returns>
			[[nodiscard]] std::vector<std::reference_wrapper<Resource>> allocate_references(
				std::size_t size
			) {
				
				std::vector<std::reference_wrapper<Resource>> vec{};

				for (std::size_t i = 0; i < size; i++) {
					vec.push_back(allocate_reference());
				}

				return vec;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// UploadResource確保関数
			/// </summary>
			/// <param name="size">確保する数</param>
			void add_upload(
				std::size_t size
			) {

				upload_.reserve(size);
				for (std::size_t i = 0;i < size;i++) {
					auto ins = Microsoft::WRL::ComPtr<ID3D12Resource>();
					upload_.emplace_back(ins);
					reference_.add_reference(upload_.back());
				}
			}

			/// <summary>
			/// Upload参照クリア関数
			/// </summary>
			void clear() {

				reference_.clear();
				upload_.clear();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// UploadResourceインスタンス配列
			/// </summary>
			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> upload_{};

			/// <summary>
			/// インスタンス参照配列
			/// </summary>
			HandyItems::container::ReferenceQueue<Microsoft::WRL::ComPtr<ID3D12Resource>> reference_{};

		};
	}
}