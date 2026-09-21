#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"PassBase.h"

#include<functional>
#include<vector>
#include<ranges>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {


		struct CommandPass : PassBase
		{
			using Command = std::function<void(FrameContext&)>;
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CommandPass() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CommandPass() = default;

			void apply_pass(
				FrameContext& context
			) override {

				if (commands_.empty()) {
					return;
				}

				for (auto& c : commands_) {
					c(context);
				}
			}

			void add_command(
				const Command& command
			) {

				commands_.push_back(command);
			}

			template<std::ranges::range R>
				requires std::same_as<std::remove_cvref_t<std::ranges::range_reference_t<R>>, Command>
			void add_commands(
				R& value
			) {

				for (auto& v : value) {
					add_command(v);
				}
			}

			void claer_command() {

				commands_.clear();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			std::vector<Command> commands_{};

		};
	}
}