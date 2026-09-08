#pragma once
#include"../DirectXobject/GPUResource.h"
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
		/// テンプレートコンセプト名前空間
		/// </summary>
		namespace concepts {

			/// <summary>
			/// 初期作成描画バッファ継承コンセプト
			/// </summary>
			template<typename T>
			concept FromGPUBuffer = std::derived_from<T, object::GPUResourceBase>;
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
				struct GPUBufferKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					GPUBufferKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit GPUBufferKey(std::uint32_t key) :
						LogicalKey{ key } {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit GPUBufferKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<GPUBufferKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画バッファ設定用保存側派生キー
				/// </summary>
				struct GPUBufferEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					GPUBufferEncodeKey() = default;
				};
			}


			/// <summary>
			/// 描画バッファリソースコンテナクラス
			/// </summary>
			class GPUBufferContainer final : public UniqueptrKeyMap<
				handle::GPUBufferKey,
				handle::GPUBufferEncodeKey,
				object::GPUResourceBase
			>
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				GPUBufferContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~GPUBufferContainer() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画バッファリソース登録関数
				/// </summary>
				/// <typeparam name="T">描画バッファ継承型</typeparam>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="buffer">設定する描画バッファ</param>
				/// <returns>登録の成否</returns>
				template<concepts::FromGPUBuffer T>
				[[nodiscard]] bool register_buffer(
					const handle::GPUBufferKey& key, 
					std::unique_ptr<T> buffer
				) {

					return add_value(key, std::move(buffer));
				}

			};
		}
	}
}