#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Container/UniqueptrKeyMap.h"

//	DirectX
#include"../ClassModule/PassBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// コンテナ名前空間
	/// </summary>
	namespace Container {

		/// <summary>
		/// 描画パス倫理キー
		/// </summary>
		struct PassKey : public HandyItems::container::handle::LogicalKey {

			PassKey() = default;

			explicit PassKey(const char* key_name) :

				HandyItems::container::handle::LogicalKey{
				static_cast<std::uint32_t>(
					HandyItems::id::get_id::get_name_id<PassKey>(key_name)
					) 
				} {}
		};

		

		/// <summary>
		/// 描画パス保存キー
		/// </summary>
		struct PassEncodeKey : public HandyItems::container::handle::EncodedKey {};

		/// <summary>
		/// 描画パスコンテナ
		/// </summary>
		class PassContainer : public HandyItems::container::UniqueptrKeyMap
			<
			PassKey,
			PassEncodeKey,
			ClassModule::PassBase
			>
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			PassContainer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~PassContainer() = default;
			
			/* ===== 追加関数 ===== */

			[[nodiscard]] bool add_pass(
				PassKey key,
				std::unique_ptr<ClassModule::PassBase>&& pass
			) {

				return add_value(key, std::move(pass));
			}

			[[nodiscard]] ClassModule::PassBase* get_pass(PassKey key)const noexcept {

				const auto* value = this->get_value_p(key);
				return value->get();
			}

		private:
			
		};
	}
}