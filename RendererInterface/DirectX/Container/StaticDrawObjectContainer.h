#pragma once
#include"../DirectXobject/DrawObjectBase.h"
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

			/* ========== 描画オブジェクト用キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// 描画オブジェクト用倫理側派生キー
				/// </summary>
				struct DrawObjectKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawObjectKey() = default;

					/// <summary>
					/// デストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit DrawObjectKey(std::uint32_t key) :
						LogicalKey(key) {}
				};

				/// <summary>
				/// 描画オブジェクト用保存側派生キー
				/// </summary>
				struct DrawObjEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawObjEncodeKey() = default;
				};
			}

			
			/* ========== 描画オブジェクトコンテナクラス定義 ========== */

			/// <summary>
			/// 描画オブジェクトコンテナクラス
			/// </summary>
			/// <typeparam name="handle::RootSignatureKey">描画オブジェクト用倫理側派生キー</typeparam>
			/// <typeparam name="handle::RSEncodeKey">描画オブジェクト用保存側派生キー</typeparam>
			/// <typeparam name="object::RootSignature">描画オブジェクト基底クラス</typeparam>
			class StaticDrawObjectContainer final : public UniqueptrKeyMap<
				handle::DrawObjectKey,
				handle::DrawObjEncodeKey,
				drawobject::DrawObjectBase
			>
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticDrawObjectContainer() = default;

				/// <summary>
				/// コンストラクタ
				/// </summary>
				~StaticDrawObjectContainer() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画オブジェクト登録関数
				/// </summary>
				/// <param name="key">登録したい倫理側のキー</param>
				/// <param name="object">登録したいオブジェクト</param>
				/// <returns>登録の成否</returns>
				[[nodiscard]] bool register_draw_object(const handle::DrawObjectKey key,std::unique_ptr<drawobject::DrawObjectBase> object);

			};
		}
	}
}