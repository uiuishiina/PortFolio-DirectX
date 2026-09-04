#pragma once
#include"DirectXRendererContext.h"
#include"DrawResouces.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DirectX描画機能更新クラス
		/// </summary>
		class DirectXUpdater final
		{
		public:
			/* ========== クラス設定 ========== */

			/// <summary>
			/// コンストラクタ削除
			/// </summary>
			DirectXUpdater() = delete;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="context">DirectX描画機能インスタンス保存クラス参照</param>
			DirectXUpdater(DirectXRendererContext* context);

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DirectXUpdater() = default;


			/* ========== Publicメンバー関数 ========== */

			/* -- 描画更新用関数 -- */

			/// <summary>
			/// 描画更新前関数
			/// </summary>
			/// <returns>DirectX描画機能インスタンスが破棄されていた場合 [ false ] 破棄されていないなら [ true ]</returns>
			[[nodiscard]] bool begin_update_renderer();

			/// <summary>
			/// フレームリソース使用可能確認関数
			/// </summary>
			/// <details>
			/// フレームリソースが使用可能な状態か確認する関数
			/// </details>
			void sync_frame_resource();

			/// <summary>
			/// フレームリソースリセット関数
			/// </summary>
			void reset_frame_resource();

			/// <summary>
			/// 描画パス呼び出し関数
			/// </summary>
			/// <details>
			/// 作成した描画パスを呼び出す関数
			/// </details>
			/// <param name="pass_order">描画パス呼び出し順保存配列参照</param>
			void apply_draw_pass(std::vector<std::string>& pass_order);

			/// <summary>
			/// 描画コマンド送信関数
			/// </summary>
			/// <details>
			/// コマンドリストに記録したコマンドを送信する
			/// </details>
			void execute_command_lists();

			/// <summary>
			/// スワップチェーンプレゼント関数
			/// </summary>
			void present();

			/// <summary>
			/// 描画更新後関数
			/// </summary>
			void end_update_renderer();


			/* -- 描画終了時関数 -- */

			/// <summary>
			/// 描画機能終了時処理関数
			/// </summary>
			/// <details>
			/// 内部でGPU同期チェック
			/// </details>
			void end_updater();

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// フレームカウント保存変数
			/// </summary>
			/// <details>
			/// 何フレーム目かを保存
			/// </details>
			UINT64 frame_count{};

			/// <summary>
			/// フレームリソースサイズ保存変数
			/// </summary>
			/// <details>
			/// 描画に使うフレームリソースサイズを保存
			/// </details>
			size_t frame_resouse_size{};

			/// <summary>
			/// フレームリソースサイクル管理用変数
			/// </summary>
			/// <details>
			/// 使用するフレームリソースインデックスを保存
			/// </details>
			UINT64 current_frame_index{};
			
			/// <summary>
			/// DirectX描画機能インスタンス保存クラス参照
			/// </summary>
			DirectXRendererContext* context_{};

		};
	};
};