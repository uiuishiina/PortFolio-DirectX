#pragma once

/* ========== Includeファイル ========== */

#include"DirectXContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {


	class DirectXEnder final
	{
	public:
		/* ========== Publicメンバー関数 ========== */


		/* ===== 終了関数 ===== */

		static void end(
			DirectXContext* context
		) {

			//	GPUに投入済みのすべてのコマンドが完了するまで待機
			//	アプリケーション終了時は次フレームが存在しないため通常のフレーム同期ではなく終了用のFenceを使用する

			const auto signal = context->fence_->signal(context->graphic_queue->get());
			context->fence_->wait_to_completed_value(signal);
		}


	private:
		/* ========== Privateメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXEnder() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXEnder() = default;

	};
}