#pragma once
#include"RendererInterface.h"
#include<memory>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// 描画機能ファクトリークラス
	/// </summary>
	class RendererFactory final
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// 描画機能作成関数
		/// </summary>
		/// <param name="window">ウィンドウインターフェースクラス参照</param>
		/// <param name="shared_datas">プリケーションデータシェアクラス参照</param>
		/// <returns>作成した描画機能インスタンス</returns>
		static std::unique_ptr<RendererInterface> create_renderer(window::windowInterface* window, sharedData::ApplicationSharedData* shared_datas);

	private:
		/* ========== クラス設定 ========== */
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		RendererFactory() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~RendererFactory() = default;

	};
}