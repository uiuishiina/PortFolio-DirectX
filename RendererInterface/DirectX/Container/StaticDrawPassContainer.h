#pragma once
#include"../DrawPass/PassBase.h"
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

			/* ========== 描画パス用キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// 描画パス用倫理側派生キー
				/// </summary>
				struct PassKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					PassKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit PassKey(std::uint32_t key) :
						LogicalKey{ key } {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit PassKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<PassKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画パス用保存側派生キー
				/// </summary>
				struct PassEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					PassEncodeKey() = default;
				};
			}

			//@brief	=== 描画パスコンテナクラス ===
			class StaticDrawPassContainer final : public UniqueptrKeyMap<
				handle::PassKey,
				handle::PassEncodeKey,
				pass::PassBase
			>
			{
			public:
				/* ========== メンバー関数 ========== */
				
				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticDrawPassContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticDrawPassContainer() = default;


				/* ========== 追加関数 ========== */

				//@breif	=== 描画パス作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	pass		登録するパスクラスインスタンス
				//@return	作成の成否
				[[nodiscard]] bool register_draw_pass(const handle::PassKey& key, std::unique_ptr<pass::PassBase> pass);


				/* ========== 取得関数 ========== */

				/// <summary>
				/// 描画パス呼び出し関数
				/// </summary>
				/// <param name="key">呼び出す描画パスに紐づいた倫理側キー</param>
				/// <param name="resource">そのフレームで使う描画リソース参照構造体</param>
				void apply_draw_pass(const handle::PassKey& key, resources::DrawResources& resource)const noexcept {
					const auto handle = this->get_handle(key);
					if (handle.handle_p != nullptr) {
						handle.handle_p->apply(resource);
					}
				}
				void apply_draw_pass(const handle::PassEncodeKey& encodekey, resources::DrawResources& resource)const noexcept {
					const auto handle = this->get_handle(encodekey);
					if (handle.handle_p != nullptr) {
						handle.handle_p->apply(resource);
					}
				}
				void apply_draw_pass(const char* key_name, resources::DrawResources& resource)const noexcept {
					const auto handle = this->get_handle(handle::PassKey(key_name));
					if (handle.handle_p != nullptr) {
						handle.handle_p->apply(resource);
					}
				}

			private:

				/// <summary>
				/// ハンドルを取得できないように [ Private化 ]
				/// </summary>
				using UniqueptrKeyMap<handle::PassKey, handle::PassEncodeKey, pass::PassBase>::get_handle;
			};
		};
	};
};