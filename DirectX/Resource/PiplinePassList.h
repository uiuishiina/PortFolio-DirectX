#pragma once

/* ========== Includeファイル ========== */

#include"../ClassModule/DrawPath/PiplinePath.h"
#include"../Helpers/PiplinePathDesc.h"

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
		namespace Path {

			/// <summary>
			/// パイプライン名前空間
			/// </summary>
			namespace Piplines {

				const PiplinePathDesc NormalTest{
					"Pipline_NormalTest",
					{
						.root_name = "Normal",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Normal",
						.pass_names{
							"SetView"
						}
					}
				};
				const PiplinePathDesc ColorTest{
					"Pipline_ColorTest",
					{
						.root_name = "Color",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Color",
						.pass_names{
							"SetView"
						}
					}
				};

				const PiplinePathDesc ConstantTest{
					"Pipline_ConstantTest",
					{
						.root_name = "Constant",
						.root_state = ClassModule::RootState::Graphics,
						.pipline_name = "Constant",
						.pass_names{
							"SetCamera"
						}
					}
				};
			}
		}
	}


}