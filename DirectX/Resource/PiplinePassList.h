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

				const PiplinePassDesc NormalTest{
					"Pipline_NormalTest",
					{
						.root_name = "Normal",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Normal",
						.pass_names{
							"SetView",
							"DrawNormalObject"
						}
					}
				};
				const PiplinePassDesc ColorTest{
					"Pipline_ColorTest",
					{
						.root_name = "Color",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Color",
						.pass_names{
							"SetView",
							"DrawColorObject"
						}
					}
				};

			}
		}
	}


}