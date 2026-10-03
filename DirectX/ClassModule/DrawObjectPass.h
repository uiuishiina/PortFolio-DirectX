#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"DrawObject/DrawObjectBase.h"
#include"PassBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// オブジェクト描画パス
		/// </summary>
		class DrawObjectPass : public PassBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DrawObjectPass() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DrawObjectPass() = default;

			/* ===== 追加関数 ===== */

			/// <summary>
			/// 描画オブジェクト追加関数
			/// </summary>
			/// <param name="object">追加するオブジェクト</param>
			void add_object(
				DrawObjectBase* object
			) {

				if (object) {
					draw_objects.push_back(object);
				}
			}

			/// <summary>
			/// 描画オブジェクト配列追加関数
			/// </summary>
			/// <param name="objects">追加する描画オブジェクト配列</param>
			void add_objects(
				const std::span<DrawObjectBase*>& objects
			) {

				for (auto& obj : objects) {
					add_object(obj);
				}
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// 描画パス呼び出し純粋仮想関数
			/// </summary>
			/// <param name="context"></param>
			void apply_pass(
				FrameContext& context_
			) override {

				for (auto& p : draw_objects) {
					p->draw(context_.graphic_list->get());
				}
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			std::vector<DrawObjectBase*> draw_objects{};

		};
	}
}