#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"
#include"../Container/PassContainer.h"

//	その他
#include<vector>
#include<utility>
#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 描画パス設定構造体
			/// </summary>
			struct PassDesc {
				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// 描画パス設定リスト
				/// </summary>
				std::vector<std::pair<std::string,std::unique_ptr<ClassModule::PassBase>>> pass_{};

				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画パス設定追加関数
				/// </summary>
				/// <param name="pass">追加するパス設定</param>
				void emplace(
					std::pair<std::string,std::unique_ptr<ClassModule::PassBase>>&& pass
				) {

					pass_.emplace_back(std::move(pass));
				}

				/// <summary>
				/// 代入演算子オーバーロード
				/// </summary>
				/// <details>
				/// 右辺値から左辺値に [ std::move() ]
				/// </details>
				/// <param name="right">右辺値</param>
				void operator = (
					PassDesc& right
					) {

					pass_ = std::move(right.pass_);
				}
			};
		}

		/// <summary>
		/// 描画パス初期化クラス
		/// </summary>
		class InitializePass
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializePass() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializePass() = default;

			/* ===== 初期化関数 ===== */
			
			/// <summary>
			/// 描画パス初期化関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			/// <param name="desc">描画パス設定構造体参照</param>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] std::vector<std::string> initialize_pass(
				DirectXContext* context, 
				desc::PassDesc& desc
			) {

				std::vector<std::string> pass_list{};

				for (auto& [name, pass] : desc.pass_) {

					if (context->pass_container->add_pass(
						Container::PassKey{ name.c_str() },
						std::move(pass)
					)) {
						pass_list.push_back(name);
					}
				}

				return pass_list;
			}

		};

	}
}