#pragma once

/* ========== Includeファイル ========== */

#include"LogObject.h"	//LogObject

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

		/// <summary>
		/// Debug出力担当クラス
		/// </summary>
		class DebugLogOutPut final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// 出力文字列受付関数
			/// </summary>
			/// <param name="log">LogObject構造体</param>
			static void reception_log(
				const LogObject& log
			);

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DebugLogOutPut() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DebugLogOutPut() = default;
			
			/* ===== 実行関数 ===== */
			
			/// <summary>
			/// 出力本体関数
			/// </summary>
			/// <param name="log">Log用文字列</param>
			static void OutPutLog(
				const std::string& log
			);

		};
	}
}