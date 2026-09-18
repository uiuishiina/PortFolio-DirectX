#pragma once

/* ========== Includeファイル ========== */

#include"DataShare/DataShare.h"
#include"Input/InputStateManager.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	/// <summary>
	/// アプリケーションデータシェアクラス
	/// </summary>
	class ApplicationDataShare final : public HandyItems::DataShare::DataShare
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ削除
		/// </summary>
		ApplicationDataShare() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ApplicationDataShare() = default;

		/* ===== 取得関数 ===== */

		/// <summary>
		/// 入力機能マネージャー取得関数
		/// </summary>
		/// <returns>入力機能マネージャークラス参照</returns>
		[[nodiscard]] HandyItems::input::InputStateManager* get_input() noexcept {
			return &input_manager;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// 入力機能マネージャークラス参照
		/// </summary>
		HandyItems::input::InputStateManager input_manager{};

	};
}