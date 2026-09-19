#pragma once

/* ========== Includeファイル ========== */

//	構造体用
#include<string>
#include<string_view>

/* ==================================================================== */
/// LogObject構造体
/* ==================================================================== */
/// 作成意図としてしっかりオブジェクトに変換してから渡すということを明確に定義したいため
/// また、今後の拡張にも対応しやすいため
/* ==================================================================== */

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

		/// <summary>
		/// ログデータ構造体
		/// </summary>
		struct LogObject {

			/* ========== Publicメンバー変数 ========== */

			/// <summary>
			/// ログデータ
			/// </summary>
			std::string Log_data{};


			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			LogObject() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="str">設定する文字列</param>
			LogObject(
				const std::string& str
			) :
				Log_data(str) {};
		};

		/// <summary>
		/// ログデーターレベル列挙体
		/// </summary>
		enum class LogLevel {
			Info, Error
		};
	}
}