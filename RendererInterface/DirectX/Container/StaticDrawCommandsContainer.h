#pragma once
#include"../DrawPass/DrawCommands.h"
#include"UniqueptrKeyMap.h"
#include<string>

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 描画パスコマンド作成構造体
			/// </summary>
			struct DrawCommandDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// Beginコマンド名
				/// </summary>
				std::string begin_name{};

				/// <summary>
				/// メイン描画コマンド名配列
				/// </summary>
				std::vector<std::string> apply_names{};

				/// <summary>
				/// Endコマンド名
				/// </summary>
				std::string end_name{};

			};
		}

		/// <summary>
		/// コンテナ名前空間
		/// </summary>
		namespace container {

			/* ========== 描画パスコマンド設定キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// コマンド用倫理側派生キー
				/// </summary>
				struct CommandKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					CommandKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit CommandKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<CommandKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画パスコマンド用保存側派生キー
				/// </summary>
				struct CommandEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					CommandEncodeKey() = default;
				};


				/// <summary>
				/// 描画パスコマンド用倫理側派生キー
				/// </summary>
				struct DrawCommandsKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawCommandsKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit DrawCommandsKey(std::uint32_t key) :
						LogicalKey{ key } {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit DrawCommandsKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<DrawCommandsKey>(key_name)) } {}
				};

				/// <summary>
				/// 描画パスコマンド用保存側派生キー
				/// </summary>
				struct DrawCommandsEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					DrawCommandsEncodeKey() = default;
				};
			}



			/// <summary>
			/// 描画パスコマンド設定コンテナ
			/// </summary>
			class StaticDrawCommandsContainer final : public UniqueptrKeyMap<
				handle::DrawCommandsKey,
				handle::DrawCommandsEncodeKey,
				command::DrawCommands
			>
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticDrawCommandsContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticDrawCommandsContainer() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 追加関数 -- */

				/// <summary>
				/// 単体コマンド追加関数
				/// </summary>
				/// <param name="key">追加するコマンド名</param>
				/// <param name="func">追加するコマンド</param>
				/// <returns>追加の成否</returns>
				[[nodiscard]] bool add_command_map(const handle::CommandKey& key, utility::DrawCommand&& func);

				/// <summary>
				/// 描画パスコマンド作成関数
				/// </summary>
				/// <param name="key">登録するキーの名前</param>
				/// <param name="desc">描画パスコマンド作成構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] bool create_draw_commands(const handle::DrawCommandsKey& key, desc::DrawCommandDesc& desc);


				/* -- 取得関数 -- */

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key_name">取得したいレンダーターゲット設定用に紐づいた倫理側キーの名前</param>
				/// <returns>レンダーターゲット設定用ハンドル</returns>
				[[nodiscard]] Handle get_handle_to_name(const char* key_name) noexcept {

					return this->get_handle(handle::DrawCommandsKey(key_name));
				}

				[[nodiscard]] Handle get_handle_to_name(const char* key_name) const noexcept {

					return this->get_handle(handle::DrawCommandsKey(key_name));
				}

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// 単体コマンド保存マップ
				/// </summary>
				HandyItems::container::KeyMap<
					handle::CommandKey,
					handle::CommandEncodeKey,
					utility::DrawCommand,
					key::FeistelKeyConverter<handle::CommandKey, handle::CommandEncodeKey>
				> command_map{};

				/// <summary>
				/// 単体コマンド取得関数
				/// </summary>
				/// <param name="key">取得するコマンド名</param>
				/// <returns>取得したコマンド...ないなら [ std::nullopt ]</returns>
				[[nodiscard]] std::optional<utility::DrawCommand> get_command(const handle::CommandKey& key);
				
			};
		}
	}
}