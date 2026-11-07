#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	その他
#include<memory>

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
	class DirectXUpdator;

	/// <summary>
	/// DirectX描画機能集約クラス
	/// </summary>
	class DirectXRenderer final : HandyItems::others::NonCopyableMovableBase
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

		/// <summary>
		/// 描画機能初期化関数
		/// </summary>
		/// <param name="hwnd">ウィンドウハンドル</param>
		/// <param name="width">ウィンドウの横幅</param>
		/// <param name="height">ウィンドウの縦幅</param>
		/// <param name="shera_">アプリケーションデータシェアクラス参照</param>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize_renderer(
			HWND hwnd,
			std::uint32_t width,
			std::uint32_t height,
			App::ApplicationDataShare* shera_
		);

		/* ===== 実行関数 ===== */

		/// <summary>
		/// 描画機能更新関数
		/// </summary>
		void update_renderer();

		/* ===== 終了関数 ===== */

		/// <summary>
		/// 描画機能終了時処理関数
		/// </summary>
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

		/// <summary>
		/// DirectXオブジェクトインスタンスまとめクラス
		/// </summary>
		std::unique_ptr<DirectXContext> context_{};

		/// <summary>
		/// DirectX描画機能更新クラス
		/// </summary>
		std::unique_ptr<DirectXUpdator> updator_{};

		/// <summary>
		/// 最終描画先バッファリングサイズ
		/// </summary>
		const std::uint32_t back_buffer_size = 3;

		/// <summary>
		/// フレームリソースサイズ
		/// </summary>
		const std::uint32_t frame_resource_size = 4;

	};
}