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
		struct PassKey : HandyItems::container::handle::LogicalKey {

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
		struct PassEncodeKey : HandyItems::container::handle::EncodeKey {};

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

			template<typename Pass>
			requires std::derived_from<Pass, ClassModule::PassBase>
			[[nodiscard]] bool add_pass(
				PassKey key,
				const Pass& pass
			) {

				return add_value(key, pass);
			}


		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ハンドルを取得できないように [ Private化 ]
			/// </summary>
			using UniqueptrKeyMap<PassKey, PassEncodeKey, ClassModule::PassBase>::get_handle;


			/* ========== Privateメンバー関数 ========== */

			using Handle = HandyItems::container::handle::HandlePtrBase<PassKey, PassEncodeKey>;


		};
	}
}