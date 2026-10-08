#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/DrawObjectPass.h"
#include"../Container/DrawObjectConteiner.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// パス名前空間
		/// </summary>
		namespace Pass {

			/// <summary>
			/// 描画オブジェクト名前空間
			/// </summary>
			namespace DrawObject {

				/// <summary>
				/// 描画オブジェクトパス外部参照補助構造体
				/// </summary>
				struct DrawObjectPassReference {

					/// <summary>
					/// 描画オブジェクト登録名配列
					/// </summary>
					std::vector<std::string> draw_object_names{};
				};

				/// <summary>
				/// 描画オブジェクトパス作成補助関数
				/// </summary>
				/// <param name="context_">DirectXオブジェクトインスタンス構造体参照</param>
				/// <param name="ref">描画オブジェクトパス外部参照補助構造体参照</param>
				/// <returns>作成した描画オブジェクトパス</returns>
				[[nodiscard]] inline std::unique_ptr<ClassModule::DrawObjectPass> make_draw_object_pass(
					DirectXContext* context_,
					DrawObjectPassReference& ref
				) {

					auto pass = std::make_unique<ClassModule::DrawObjectPass>();

					std::vector<ClassModule::DrawObjectBase*> objs{};

					for (auto& obj_name : ref.draw_object_names) {

						if (auto obj = context_->draw_object_container->get_draw_object(
							Container::DrawObjectKey{ obj_name.c_str() }
						); obj) {

							objs.push_back(obj);
						}
					}

					pass->add_objects(objs);

					return std::move(pass);
				}

				/// <summary>
				/// 描画オブジェクトパス設定定義
				/// </summary>
				using DrwObjectPassDesc = std::tuple<
					std::string,
					DrawObjectPassReference,
					bool
				>;
			}
		}
	}
}