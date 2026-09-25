#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassObject/PiplineState.h"


/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// コンテナ名前空間
	/// </summary>
	namespace Container {

		/* ========== ハッシュキー ========== */

		/// <summary>
		/// パイプラインステート倫理キー
		/// </summary>
		struct PiplineStateKey : public HandyItems::container::handle::LogicalKey {

			PiplineStateKey() = default;

			explicit PiplineStateKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<PiplineStateKey>(key_name)
					)
			} {}
		};

		/// <summary>
		/// パイプラインステート保存キー
		/// </summary>
		struct PiplineStateKeyEncodeKey : public HandyItems::container::handle::EncodedKey {};


		/* ========== コンテナ ========== */

		/// <summary>
		/// パイプラインステートコンテナ
		/// </summary>
		class PiplineStateContainer : HandyItems::container::UniqueptrKeyMap
			<
			PiplineStateKey,
			PiplineStateKeyEncodeKey,
			ClassObject::PiplineState
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			PiplineStateContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~PiplineStateContainer() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// パイプラインステート追加関数
			/// </summary>
			/// <param name="key">紐づけるパイプラインステート倫理キー</param>
			/// <param name="pipline">追加するパイプラインステートインスタンス</param>
			/// <returns>追加の成否</returns>
			[[nodiscard]] bool add_pipline_state(
				PiplineStateKey key,
				std::unique_ptr<ClassObject::PiplineState>&& pipline
			) {

				return add_value(key, std::move(pipline));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// パイプラインステート参照取得関数
			/// </summary>
			/// <param name="key">紐づいたパイプラインステート倫理キー</param>
			/// <returns>パイプラインステート参照</returns>
			[[nodiscard]] ClassObject::PiplineState* get_pipline_state(
				const PiplineStateKey& key
			) const noexcept {

				return get_unique(key);
			}

		};
	}
}