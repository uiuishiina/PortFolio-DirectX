#pragma once
#include"../DrawPass/DrawCommands.h"
#include"StaticContainerBase.h"
#include<unordered_map>
#include<memory>
#include<optional>
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
		/// DX12オブジェクト設定名前空間
		///====================================================================

		namespace desc {

			//@breif	=== 描画パスコマンド作成構造体 ===
			struct DrawCommandDesc {

				//@brief	== Beginコマンド名 ==
				std::string begin_name{};

				//@brief	== メイン描画コマンド名配列 ==
				std::vector<std::string> apply_names{};

				//@brief	== Endコマンド名 ==
				std::string end_name{};

			};
		};

		///====================================================================
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			//@brief	=== 描画パスコマンドコンテナクラス ===
			class StaticDrawCommandsContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				///	クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticDrawCommandsContainer() = default;
				~StaticDrawCommandsContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== 単体コマンド追加関数 ===
				//@param	name	追加するコマンド名
				//@param	func	追加するコマンド
				//@return	追加の成否
				[[nodiscard]] bool add_command_map(const std::string& name, const utility::DrawCommand& func);

				//@breif	=== 描画パスコマンド作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	desc		描画パスコマンド作成構造体
				//@return	作成の成否
				[[nodiscard]] bool create_draw_commands(const std::string& key_name, desc::DrawCommandDesc& desc);

				//@brief	=== 描画パスコマンド取得関数 ===
				//@param	key	描画パスコマンド紐づけたキー
				//@return	描画パスコマンド参照
				[[nodiscard]] command::DrawCommands* get_draw_commands(UINT key)const noexcept;

				//@breif	=== 描画パスコマンド取得オーバーロード関数 ===
				//@param	key_name	描画パスコマンドと紐づけたキーの名前
				//@return	描画パスコマンドクラス参照
				[[nodiscard]] command::DrawCommands* get_draw_commands(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief == 単体コマンド保存マップ ==
				//@details	作成できたコマンドを保存するmap
				std::unordered_map<std::string, utility::DrawCommand> command_list{};

				//@brief == 描画パスコマンド保存マップ == =
				//@details	作成できた描画パスコマンドを保存するmap
				std::unordered_map<UINT, std::unique_ptr<command::DrawCommands>> draw_commands_map{};

				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	=== 単体コマンド取得関数 ===
				//@param	key_name	取得するコマンド名
				//@return	取得したコマンド...ないなら [ std::nullopt ]
				[[nodiscard]] std::optional<utility::DrawCommand> get_command(std::string& key_name);

			};
		};
	};
};