#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/CircularIndex.h"

//	DirectX
#include"DirectXContext.h"
#include"ClassModule/DrawPath/PathBase.h"

//	その他
#include<vector>

/* ========== 前方宣言 ========== */

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

	/// <summary>
	/// DirectX描画更新クラス
	/// </summary>
	class DirectXUpdator final : HandyItems::others::NonCopyableMovableBase 
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		///	引数付きコンストラクタ
		/// </summary>
		/// <param name="context">DirectXオブジェクトインスタンスまとめクラスWeak参照</param>
		explicit DirectXUpdator(
			DirectXContext* context,
			App::ApplicationDataShare* share
		) :
			context_{ context },
			share_p{ share } {};

		/* ===== 実行関数 ===== */

		/// <summary>
		/// 描画前処理関数
		/// </summary>
		/// <details>
		/// 待機前に処理できることを処理しておく関数
		/// </details>
		/// <returns>エラーなどで描画ができない場合に [ false ]</returns>
		[[nodiscard]] bool begin_update();

		/// <summary>
		/// フレームリソース待機関数
		/// </summary>
		/// <details>
		/// 次フレームに利用するリソースが使えるまで待機
		/// </details>
		void sync_frame_resource();

		/// <summary>
		/// フレームリソースリセット関数
		/// </summary>
		void reset_frame_resource();

		/// <summary>
		/// フレームリソース更新関数
		/// </summary>
		/// <details>
		/// 利用するリソースに書き込み
		/// </details>
		void update_resource();

		/// <summary>
		/// 描画パス更新関数
		/// </summary>
		void apply_path();

		/// <summary>
		/// コマンドリスト実行関数
		/// </summary>
		void execute_command_lists();

		/// <summary>
		/// スワップチェーンプレゼント関数
		/// </summary>
		void present();

		/// <summary>
		/// 描画終了時処理関数
		/// </summary>
		void end_update();

		void set_pass(ClassModule::PathBase* pass) {

			pass_order.push_back(pass);
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// DirectXオブジェクトインスタンスまとめクラスWeak参照
		/// </summary>
		DirectXContext* context_;

		/// <summary>
		/// アプリケーションデータシェアクラス参照
		/// </summary>
		App::ApplicationDataShare* share_p;

		/// <summary>
		/// 描画パス実行順参照配列
		/// </summary>
		std::vector<ClassModule::PathBase*> pass_order{};

		/// <summary>
		/// 経過フレーム
		/// </summary>
		std::uint64_t frame_count{};

		std::size_t current_resource_index{};

	};
}