#pragma once

/* ========== Includeファイル ========== */

#include<string>

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// デバッグ名前空間
	/// </summary>
	namespace Debug {

		/// <summary>
		/// 文字列変換クラス
		/// </summary>
		class ConvertString 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 実行関数 ===== */

			/// <summary>
			/// wstring変換関数
			/// </summary>
			/// <param name="value">変換対象</param>
			/// <returns>変換後のstring</returns>
			[[nodiscard]] static std::string to_utf8(
				const std::wstring& value
			);

			/// <summary>
			/// string変換関数
			/// </summary>
			/// <param name="value">変換対象</param>
			/// <returns>変換後のwstring</returns>
			[[nodiscard]] static std::wstring from_utf8(
				const std::string& value
			);

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ConvertString() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ConvertString() = default;

		};

	}
}