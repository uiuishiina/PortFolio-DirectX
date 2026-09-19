#pragma once

/* ========== Includeファイル ========== */

//	補助関数用
#include<concepts>
#include<sstream>

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
		/// テンプレートコンセプト定義用名前空間
		/// </summary>
		namespace concepts {

			/// <summary>
			/// "<<" 変換可能コンセプト
			/// </summary>
			template<typename T>
			concept stream_insert_able = requires(
				std::ostream & os, 
				const T & value
				) {

				//	os << value が std::ostream になるか
				{ os << value } -> std::same_as<std::ostream&>;
			};
		}

		/// <summary>
		/// string作成補助関数
		/// </summary>
		/// <typeparam name="...Args">文字列にする型... [ "<<" 変換可能指定 ]</typeparam>
		/// <param name="...args">文字列にする値</param>
		/// <returns>すべてまとめた文字列</returns>
		template<concepts::stream_insert_able... Args>
		[[nodiscard]] static std::string create_string(Args&&... args) {

			//中央展開
			std::ostringstream oss;
			(oss << ... << std::forward<Args>(args));
			return oss.str();
		}


		namespace const_str {

			//	罫線
			const std::string Gridlines = std::string(100, '-');

			//	改行
			const std::string LineBreak = "\n";

			//	見やすくするようまとめ
			const std::string ErrorLine = Gridlines + LineBreak;
		}

		/// <summary>
		/// デバッグログ構造体作成クラス
		/// </summary>
		class DebugLogBuilder final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// LogObject構造体作成関数
			/// </summary>
			/// <param name="data">ログデータにしたい文字列</param>
			/// <param name="level">ログデータレベル</param>
			/// <returns>作成されたLogObject</returns>
			[[nodiscard]] static LogObject create_LogObject(
				const std::string& data,
				LogLevel level = LogLevel::Info
			) {

				//	エラーログなら
				if (level == LogLevel::Error) {

					const auto str = create_string(
						const_str::ErrorLine +
						data +
						const_str::LineBreak +
						const_str::Gridlines
					);
					return LogObject(str);
				}
				else {
					//	そのまま作成
					return LogObject(data);
				}
			}

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			DebugLogBuilder() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DebugLogBuilder() = default;

		};
	}
}