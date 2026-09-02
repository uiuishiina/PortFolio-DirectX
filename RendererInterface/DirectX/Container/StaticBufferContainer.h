#pragma once
#include"../DirectXobject/StaticBufferResource.h"
#include"UniqueptrKeyMap.h"

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		///====================================================================
		/// テンプレートコンセプト名前空間
		///====================================================================

		namespace concepts {

			//@brief	=== 初期作成描画バッファ継承コンセプト ===
			template<typename T>
			concept FromStaticBuffer = std::derived_from<T, object::StaticBufferResource>;
		};


		/// <summary>
		/// コンテナ名前空間
		/// </summary>
		namespace container {

			/* ========== 描画バッファ設定用キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// 描画バッファ設定用倫理側派生キー
				/// </summary>
				struct StaticBufferKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					StaticBufferKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit StaticBufferKey(std::uint32_t key) :
						LogicalKey{ key } {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit StaticBufferKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<StaticBufferKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画バッファ設定用保存側派生キー
				/// </summary>
				struct StaticBufferEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					StaticBufferEncodeKey() = default;
				};
			}



			///====================================================================
			/// StaticBufferContainer クラス
			///====================================================================

			//@brief	=== 初期作成描画バッファリソースコンテナクラス ===
			class StaticBufferContainer final : public UniqueptrKeyMap<
				handle::StaticBufferKey,
				handle::StaticBufferEncodeKey,
				object::StaticBufferResource
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticBufferContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticBufferContainer() = default;

				/* ===== 追加関数 ===== */

				/// <summary>
				/// 描画バッファリソース登録関数
				/// </summary>
				/// <typeparam name="T">描画バッファ継承型</typeparam>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="buffer">設定する描画バッファ</param>
				/// <returns>登録の成否</returns>
				template<concepts::FromStaticBuffer T>
				[[nodiscard]] bool register_buffer(const handle::StaticBufferKey& key, std::unique_ptr<T> buffer);

			};

			/// <summary>
			/// 描画バッファリソース登録関数
			/// </summary>
			/// <typeparam name="T">描画バッファ継承型</typeparam>
			/// <param name="key">追加したい倫理側のキー</param>
			/// <param name="buffer">設定する描画バッファ</param>
			/// <returns>登録の成否</returns>
			template<concepts::FromStaticBuffer T>
			[[nodiscard]] bool StaticBufferContainer::register_buffer(const handle::StaticBufferKey& key, std::unique_ptr<T> buffer) {

				return add_value(key, std::move(buffer));
			}
		};
	};
};