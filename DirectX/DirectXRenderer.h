#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"Others/UniquePtr.h"

/* ========== 前方宣言 ========== */

/// <summary>
/// HWND用前方宣言
/// </summary>
struct HWND__;
using HWND = HWND__*;

namespace App {

	/// <summary>
	/// アプリケーションデータシェアクラス用前方宣言
	/// </summary>
	class ApplicationDataShare;
}

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	struct DirectXContext;

	/// <summary>
	/// DirectX描画機能クラス
	/// </summary>
	class DirectXRenderer final : HandyItems::others::NonCopyableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXRenderer();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXRenderer();

		/* ===== 初期化関数 ===== */

		[[nodiscard]] bool initialize_renderer(
			HWND hwnd,
			App::ApplicationDataShare* shera
		);

		/* ===== 実行関数 ===== */

		void update_renderer();

		/* ===== 終了関数 ===== */

		void end_renderer();

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// ウィンドウハンドル
		/// </summary>
		HWND hwnd_{};

		/// <summary>
		/// アプリケーションデータシェアクラス参照
		/// </summary>
		App::ApplicationDataShare* shera_p{};

		HandyItems::others::UniquePtr<DirectXContext> context_{};

		/* ========== Privateメンバー関数 ========== */

	};
}