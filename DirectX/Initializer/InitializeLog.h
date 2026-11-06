#pragma once

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		using HRESULT = long;

		/// <summary>
		/// 初期作成時ログ出力クラス
		/// </summary>
		class InitializeLog final
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 実行関数 ===== */

			/// <summary>
			/// HRESULTログ出力関数
			/// </summary>
			/// <param name="hr">ログに出力するHRESULT</param>
			static void hresult_log(
				HRESULT hr
			);

			/// <summary>
			/// HRESULTエラーログ出力関数
			/// </summary>
			/// <param name="hr">ログに出力するHRESULT</param>
			static void hresult_error_log(
				HRESULT hr
			);

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializeLog() = default;

		};

	}
}