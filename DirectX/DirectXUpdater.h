#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/CircularIndex.h"

//	DirectX
#include"DirectXContext.h"

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


	class DirectXUpdator final : HandyItems::others::NonCopyableMovableBase 
	{

		template<typename T>
		using WeakPtr = HandyItems::others::UniqueWeakPtr<T>;

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
			const WeakPtr<DirectXContext>& context,
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

		void execute_command_lists();

		void present();

		void end_update();

	private:
		/* ========== Privateメンバー変数 ========== */

		HandyItems::others::CircularIndex current_index;

		/// <summary>
		/// DirectXオブジェクトインスタンスまとめクラスWeak参照
		/// </summary>
		WeakPtr<DirectXContext> context_;

		App::ApplicationDataShare* share_p;

	};
}