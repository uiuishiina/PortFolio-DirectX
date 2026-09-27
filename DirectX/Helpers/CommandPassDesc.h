#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/CommandPass.h"

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

				/// <summary>
				/// コマンド定義
				/// </summary>
				using Command = std::function<void(ClassModule::FrameContext&)>;

				/// <summary>
				/// コマンドパス設定定義
				/// </summary>
				using CommandPassDesc = std::tuple<
					std::string,
					std::vector<Command>,
					bool
				>;

			}
		}
	}
}