#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/DrawPath/CommandPath.h"

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
				using CommandPathDesc = std::tuple<
					std::string,
					std::vector<Command>
				>;

			}
		}
	}
}