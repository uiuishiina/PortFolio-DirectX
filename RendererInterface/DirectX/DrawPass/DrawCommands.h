#pragma once
#include"../DrawResouces.h"
#include"NonMovable.h"
#include<functional>
#include<vector>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// 描画設定名前空間
		///====================================================================

		namespace command {

			///====================================================================
			/// DrawCommands クラス
			///====================================================================

			class DrawCommands final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				DrawCommands() = default;
				~DrawCommands() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				/* -- 設定関数 -- */

				//@param	=== Beginコマンド設定関数 ===
				//@param	func	設定するコマンド
				void set_begin_command(const std::function<void(resouces::DrawResouces&)>& func);

				//@brief	=== 描画コマンド追加関数 ===
				//@param	func	追加するコマンド
				void add_apply_command(const std::function<void(resouces::DrawResouces&)>& func);

				//@param	=== Endコマンド設定関数 ===
				//@param	func	設定するコマンド
				void set_end_command(const std::function<void(resouces::DrawResouces&)>& func);

				/* -- 実行関数 -- */

				//@brief	=== 描画パス実行時Beginコマンド実行関数 ===
				//@param	resouce	描画リソース
				void begin(resouces::DrawResouces& resouce);

				//@brief	=== 描画パス実行時描画コマンド実行関数 ===
				//@param	resouce	描画リソース
				void apply(resouces::DrawResouces& resouce);

				//@brief	=== 描画パス実行時Endコマンド実行関数 ===
				//@param	resouce	描画リソース
				void end(resouces::DrawResouces& resouce);

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 描画パス開始時コマンド ==
				std::function<void(resouces::DrawResouces& resouce)> begin_command{};

				//@brief	== 描画コマンド保存配列 ==
				std::vector<std::function<void(resouces::DrawResouces& resouce)>> apply_commands{};

				//@brief	== 描画パス終了時コマンド ==
				std::function<void(resouces::DrawResouces& resouce)> end_command{};

			};
		};
	};
};