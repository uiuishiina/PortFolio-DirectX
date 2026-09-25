#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/CircularIndex.h"

//	DirectX
#include"DirectXContext.h"
#include"ClassModule/PassBase.h"

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

		//	コンストラクタ削除
		DirectXUpdator() = delete;

		/// <summary>
		///	引数付きコンストラクタ
		/// </summary>
		/// <param name="context">DirectXオブジェクトインスタンスまとめクラスWeak参照</param>
		DirectXUpdator(
			std::size_t size,
			DirectXContext* context,
			App::ApplicationDataShare* share
		) :
			current_index{ size },
			context_{ context },
			share_p{ share } {};

		/// <summary>
		///	デストラクタ
		/// </summary>
		~DirectXUpdator() = default;

		/* ===== 実行関数 ===== */

		[[nodiscard]] bool begin_update();

		void sync_frame_resource();

		void reset_frame_resource();


		void update();

		void apply_pass();

		void execute_command_lists();

		void present();

		void end_update();

		void set_pass(ClassModule::PassBase* pass) {

			pass_order.push_back(pass);
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// フレームリソースインデックス循環クラス
		/// </summary>
		HandyItems::others::CircularIndex current_index;

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
		std::vector<ClassModule::PassBase*> pass_order{};

	};
}