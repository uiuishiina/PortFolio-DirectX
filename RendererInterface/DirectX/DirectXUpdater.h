#pragma once
#include"DirectXRendererContext.h"
#include"DrawResouces.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// DirectXUpdater クラス
		///====================================================================

		//@breif	===  DirectX描画機能更新クラス ===
		class DirectXUpdater final
		{
		public:
			///====================================================================
			/// クラス設定
			///====================================================================

			//コンストラクタ削除
			DirectXUpdater() = delete;

			//@brief	=== 引数付きコンストラクタ ===
			//@param	context	DirectX描画機能インスタンス保存クラス参照
			DirectXUpdater(DirectXRendererContext* context);

			//デストラクタ
			~DirectXUpdater() = default;

			///====================================================================
			/// Public メンバー関数
			///====================================================================

			/* -- 描画更新用関数 -- */

			//@brief	=== 描画更新前関数 ===
			//@return	DirectX描画機能インスタンスが破棄されていた場合 [ false ] 破棄されていないなら [ true ]
			[[nodiscard]] bool begin_update_renderer();

			//@brief	=== フレームリソース使用可能確認関数 ===
			//@details	フレームリソースが使用可能な状態か確認する関数
			void sync_frame_resource();

			//@brief	=== フレームリソースリセット関数 ===
			//@details	フレームリソース内のリセットが必要なものをリセット
			void reset_frame_resource();

			//@breif	=== 描画パス呼び出し関数 ===
			//@detais	作成した描画パスを呼び出す関数
			//@param	pass_order	描画パス呼び出し順保存配列参照
			void apply_draw_pass(std::vector<std::string>& pass_order);

			//@brief	=== 描画コマンド送信関数 ===
			//@details	コマンドリストに記録したコマンドを送信する
			void execute_command_lists();

			//@brief	=== スワップチェーンプレゼント関数 ===
			void present();

			//@brief	=== 描画更新後関数 ===
			void end_update_renderer();


			/* -- 描画終了時関数 -- */

			//@brief	=== 描画機能終了時処理関数 ===
			//@details	内部でGPU同期チェック
			void destroy_updater();

		private:
			///====================================================================
			/// Private メンバー変数
			///====================================================================

			//@brief	== フレームカウント保存変数 ==
			//@details	何フレーム目かを保存
			UINT64 frame_count{};

			//@breif	== フレームリソースサイズ保存変数 ==
			//@details	描画に使うフレームリソースサイズを保存
			UINT frame_resouse_size{};

			//@brief	== フレームリソースサイクル管理用変数 ==
			//@details	使用するフレームリソースインデックスを保存
			UINT64 current_frame_index{};
			
			//@brief	== DirectX描画機能インスタンス保存クラス参照 ==
			DirectXRendererContext* context_{};

		};
	};
};