#pragma once

/* ========== Includeファイル ========== */

#include"../DirectXContext.h"

#include<vector>
#include<utility>
#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	namespace Initialize {

		namespace desc {

			struct PassDesc {

				std::vector<std::pair<ClassModule::PassBase, std::string>> pass_{};
			};
		}

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
			
			[[nodiscard]] std::vector<std::string> initialize_pass(
				DirectXContext* context, 
				desc::PassDesc& value
			) {

				std::vector<std::string> pass_list{};

				//for (auto& [pass,name] : value.pass_) {

				//	if (context->pass_container->add_pass(
				//		Container::PassKey{ name.c_str() },
				//		pass
				//	)) {
				//		pass_list.push_back(name);
				//	}
				//}

				return pass_list;
			}

		};
	}
}