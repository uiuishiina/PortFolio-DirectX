#pragma once

/* ========== Includeファイル ========== */

#include"../ClassModule/PiplinePass.h"
#include"../Helpers/PiplinePassDesc.h"

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
			/// パイプライン名前空間
			/// </summary>
			namespace Piplines {

				const PiplinePassDesc Test{
					"Test",
					{
						.root_name = "Test",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Test",
						.command_pass_names{
							"Begin",
							"Clear",
							"End"
						}
					},
					true
				};

			}
		}
	}


}