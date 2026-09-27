#pragma once


/* ========== Includeファイル ========== */

#include"../ClassModule/CommandPass.h"

#include<vector>

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
			/// コマンド名前空間
			/// </summary>
			namespace Commands {

				using Command = std::function<void(ClassModule::FrameContext&)>;

				using CommandPassDesc = std::tuple<
					std::string,
					std::vector<Command>,
					bool
				>;

			}
		}
	}
}