#pragma once
#include"KeyMapBase.h"
#include<unordered_map>
#include<memory>
#include<optional>

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

			/* ========== unique_ptr用キーマップ基底クラス定義 ========== */

			/// <summary>
			/// unique_ptr用キーマップ基底クラス
			/// </summary>
			/// <typeparam name="KeyT">倫理側の派生キー型</typeparam>
			/// <typeparam name="EncodeKeyT">保存側の派生キー型</typeparam>
			/// <typeparam name="Object">unique_ptrとして保存する型</typeparam>
			template<
				typename KeyT,
				typename EncodeKeyT,
				typename Object
			>
			/// <summary>
			/// 派生キーの型チェック
			/// </summary>
			requires 
				std::derived_from<KeyT, handle::LogicalKey> &&
				std::derived_from<EncodeKeyT, handle::EncodeKey>
			class UniqueptrKeyMap : public KeyMapBase<
				KeyT,
				EncodeKeyT,
				handle::HandlePtrBase<Object, EncodeKeyT>,	///Ptr指定
				std::unique_ptr<Object>
			>
			{
			public:
				using Handle = handle::HandlePtrBase<Object, EncodeKeyT>;

				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				UniqueptrKeyMap() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~UniqueptrKeyMap() = default;


				/* ===== 取得関数 ===== */

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key">取得したいハンドルに紐づいた倫理側キー</param>
				/// <returns>取得したいハンドル</returns>
				[[nodiscard]] Handle get_handle(const KeyT& key) noexcept override {

					Handle handle{};

					const auto* value = this->get_value_p(key);
					if (value != nullptr) {
						handle.handle_p = value->get();
					}

					handle.handle_key = this->encode_key(key);

					return handle;
				}

				[[nodiscard]] Handle get_handle(const KeyT& key) const noexcept override {

					Handle handle{};

					const auto* value = this->get_value_p(key);
					if (value != nullptr) {
						handle.handle_p = value->get();
					}

					handle.handle_key = this->encode_key(key);

					return handle;
				}


				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key">取得したいハンドルに紐づいた保存側キー</param>
				/// <returns>取得したいハンドル</returns>
				[[nodiscard]] Handle get_handle(const EncodeKeyT& encode_key) noexcept override {

					Handle handle{};

					const auto* value = this->get_value_p(encode_key);
					if (value != nullptr) {
						handle.handle_p = value->get();
					}

					handle.handle_key = encode_key;

					return handle;
				}

				[[nodiscard]] Handle get_handle(const EncodeKeyT& encode_key) const noexcept override {

					Handle handle{};

					const auto* value = this->get_value_p(encode_key);
					if (value != nullptr) {
						handle.handle_p = value->get();
					}

					handle.handle_key = encode_key;

					return handle;
				}

			};
		}
	}
}