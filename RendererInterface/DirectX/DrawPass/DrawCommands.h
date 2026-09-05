#pragma once
#include"../DrawResouces.h"
#include"NonMovable.h"
#include<functional>
#include<vector>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DirectXオブジェクト補助名前空間
		/// </summary>
		namespace utility {

			/// <summary>
			/// 可読性向上用名称定義
			/// </summary>
			using DrawCommand = std::function<void(resources::DrawResources&)>;

		}

		/// <summary>
		/// 描画設定名前空間
		/// </summary>
		namespace command {

			/// <summary>
			/// 描画パスコマンドクラス
			/// </summary>
			class DrawCommands final : public NonMovableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DrawCommands() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DrawCommands() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 設定関数 -- */

				/// <summary>
				/// Beginコマンド設定関数
				/// </summary>
				/// <param name="func">追加するコマンド</param>
				void set_begin_command(const utility::DrawCommand& func);

				/// <summary>
				/// メイン描画コマンド追加関数
				/// </summary>
				/// <param name="func">追加するコマンド</param>
				void add_apply_command(const utility::DrawCommand& func);

				/// <summary>
				/// Endコマンド設定関数
				/// </summary>
				/// <param name="func">追加するコマンド</param>
				void set_end_command(const utility::DrawCommand& func);

				/* -- 実行関数 -- */

				/// <summary>
				/// 描画パスBeginコマンド実行関数
				/// </summary>
				/// <param name="resouce">描画リソース構造体参照</param>
				void begin(resources::DrawResources& resouce);

				/// <summary>
				/// 描画パスメイン描画コマンド実行関数
				/// </summary>
				/// <param name="resouce">描画リソース構造体参照</param>
				void apply(resources::DrawResources& resouce);

				/// <summary>
				/// 描画パスEndコマンド実行関数
				/// </summary>
				/// <param name="resouce">描画リソース構造体参照</param>
				void end(resources::DrawResources& resouce);

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// 描画パス開始時コマンド
				/// </summary>
				utility::DrawCommand begin_command{};

				/// <summary>
				/// メイン描画コマンド保存配列
				/// </summary>
				std::vector<utility::DrawCommand> apply_commands{};

				/// <summary>
				/// 描画パス終了時コマンド
				/// </summary>
				utility::DrawCommand end_command{};

			};
		}
	}
}