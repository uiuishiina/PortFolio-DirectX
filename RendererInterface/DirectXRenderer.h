#pragma once
#include"RendererInterface.h"
#include<memory>
#include<vector>
#include<string>

/* ==================================================================== */
/// UINT互換typeof
/* ==================================================================== */

typedef unsigned int        UINT;
typedef unsigned __int64    UINT64;

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/* ==================================================================== */
	// DirectXオブジェクト統括クラス前方宣言
	/* ==================================================================== */
	namespace dx12 {
		class DirectXRendererContext;
		class DirectXUpdater;
	}

	/// <summary>
	/// DirectX描画機能クラス
	/// </summary>
	class DirectXRenderer final : public RendererInterface
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXRenderer();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXRenderer();


		/* ========== Publicメンバー関数 ========== */

		/* ===== 作成関数 ===== */

		/// <summary>
		/// 描画機能作成関数
		/// </summary>
		/// <param name="window">ウィンドウインターフェースクラス参照</param>
		/// <param name="shared_datas">プリケーションデータシェアクラス参照</param>
		/// <returns>作成の成否</returns>
		[[nodiscard]] bool create_renderer(window::windowInterface* window, sharedData::ApplicationSharedData* shared_)override;


		/* ===== 制御関数 ===== */

		/// <summary>
		/// 描画更新関数
		/// </summary>
		/// <details>
		/// 毎フレーム呼び出される関数
		/// </details>
		void update_renderer()override;

		/// <summary>
		/// 描画機能終了処理関数
		/// </summary>
		/// <details>
		/// 描画機能破棄前最終処理(非同期処理の待機など)をするための関数
		/// </details>
		void end_renderer()override;

	protected:
		/* ========== Protectedメンバー関数 ========== */

		/// <summary>
		/// 描画更新前関数
		/// </summary>
		/// <details>
		/// 描画機能を更新する際に先に処理する必要があるものを呼び出す関数
		/// </details>
		void begin_update_renderer()override;

		/// <summary>
		/// 描画更新後関数
		/// </summary>
		/// <details>
		/// 描画機能を更新した後に処理する必要があるものを呼び出す関数
		/// </details>
		void end_update_renderer()override;

	private:
		/* ========== Protectedメンバー変数 ========== */

		/* -- 設定 -- */

		/// <summary>
		/// ウィンドウサイズ保存変数
		/// </summary>
		WindowSize window_size{};

		/// <summary>
		/// フレームバッファサイズ設定変数
		/// </summary>
		/// <details>
		/// 描画バッファリングサイズを指定
		/// </details>
		const UINT buffer_size = 2;

		/// <summary>
		/// フレームリソースサイズ設定変数
		/// </summary>
		/// <details>
		/// 描画に使うフレームリソースサイズを指定
		/// </details>
		const UINT frame_resouse_size = 3;

		/// <summary>
		/// DirectX描画機能インスタンス保存クラスインスタンス
		/// </summary>
		/// <details>
		/// 制作途中
		/// </details>
		std::unique_ptr<render::dx12::DirectXRendererContext> renderer_context{};

		/// <summary>
		/// DirectX描画機能更新クラスインスタンス
		/// </summary>
		/// <details>
		/// 制作途中
		/// </details>
		std::unique_ptr<render::dx12::DirectXUpdater> renderer_updater{};

		/// <summary>
		/// 描画パス呼び出し順保存配列
		/// </summary>
		std::vector<std::string> pass_order{};

	};
}