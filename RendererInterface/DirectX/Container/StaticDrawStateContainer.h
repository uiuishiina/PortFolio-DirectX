#pragma once
#include"../DrawPass/DrawState.h"
#include"UniqueptrKeyMap.h"

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
			

			/* ========== 描画パス設定用キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// 描画パス設定用倫理側派生キー
				/// </summary>
				struct DrawStateKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawStateKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit DrawStateKey(std::uint32_t key) :
						LogicalKey{ key } {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit DrawStateKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<DrawStateKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画パス設定用保存側派生キー
				/// </summary>
				struct DrawStateEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawStateEncodeKey() = default;
				};
			}

			/// <summary>
			/// 描画パス設定コンテナ
			/// </summary>
			class StaticDrawStateContainer final : public UniqueptrKeyMap<
				handle::DrawStateKey,
				handle::DrawStateEncodeKey,
				state::Drawstate
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticDrawStateContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticDrawStateContainer() = default;


				/* ===== 追加関数 ===== */
				
				/// <summary>
				/// 描画設定作成関数
				/// </summary>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="desc">設定する描画設定</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] bool create_draw_state(const handle::DrawStateKey& key, desc::DrawStateDesc& desc);


				/* ===== 取得関数 ===== */

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key_name">取得したい描画設定に紐づいた倫理側キーの名前</param>
				/// <returns>描画設定用ハンドル</returns>
				[[nodiscard]] Handle get_handle_to_name(const char* key_name) noexcept {

					return this->get_handle(handle::DrawStateKey(key_name));
				}

				[[nodiscard]] Handle get_handle_to_name(const char* key_name) const noexcept {

					return this->get_handle(handle::DrawStateKey(key_name));
				}
			};
		};
	};
};