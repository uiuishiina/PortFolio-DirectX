#pragma once
#include"../windowInterface/windowInterface.h"
#include"../Application/SharedData/ApplicationSharedData.h"
#include"NonMovable.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// 描画機能インターフェース基底クラス
	/// </summary>
	class RendererInterface : public NonMovableBase
	{
	public:
		/* ========== クラス設定 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		RendererInterface() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~RendererInterface() = default;


		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// 描画機能作成関数
		/// </summary>
		/// <param name="window">ウィンドウインターフェースクラス参照</param>
		/// <param name="shared_datas">プリケーションデータシェアクラス参照</param>
		/// <returns>作成の成否</returns>
		virtual [[nodiscard]] bool create_renderer(window::windowInterface* window, sharedData::ApplicationSharedData* shared_) = 0;

		/// <summary>
		/// 描画更新関数
		/// </summary>
		/// <details>
		/// 毎フレーム呼び出される関数
		/// </details>
		virtual void update_renderer() = 0;

		/// <summary>
		/// 描画機能終了処理関数
		/// </summary>
		/// <details>
		/// 描画機能破棄前最終処理(非同期処理の待機など)をするための関数
		/// </details>
		virtual void end_renderer() = 0;

	protected:
		/* ========== Protectedメンバー関数 ========== */

		/// <summary>
		/// 描画更新前関数
		/// </summary>
		/// <details>
		/// 描画機能を更新する際に先に処理する必要があるものを呼び出す関数
		/// </details>
		virtual void begin_update_renderer() = 0;

		/// <summary>
		/// 描画更新後関数
		/// </summary>
		/// <details>
		/// 描画機能を更新した後に処理する必要があるものを呼び出す関数
		/// </details>
		virtual void end_update_renderer() = 0;


		/* ========== Protectedメンバー変数 ========== */

		/// <summary>
		/// プリケーションデータシェアクラス参照
		/// </summary>
		sharedData::ApplicationSharedData* shared_datas{};

		/// <summary>
		/// ウィンドウハンドル参照
		/// </summary>
		const std::any* window_handle{};

	};
}