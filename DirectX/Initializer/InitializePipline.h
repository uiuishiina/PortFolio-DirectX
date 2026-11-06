#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Debug/DebugLogSystem.h"

//	DirectX
#include"../DirectXContext.h"
#include"../Container/RootSignatureContainer.h"
#include"../Container/PiplineStateContainer.h"
#include"../Helpers/PiplineStateReference.h"

#include"InitializeLog.h"

//	その他
#include<vector>
#include<utility>
#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 描画パイプライン設定構造体
			/// </summary>
			struct PiplineDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// ルートシグネチャー設定配列
				/// </summary>
				std::vector<std::pair<std::string, ClassObject::desc::RootSignatureDesc>> root_{};


				using PiplineCreateDesc = std::tuple<
					std::string,
					ClassObject::desc::PiplineStateReferenceName,
					ClassObject::desc::PipelineStateDesc
				>;

				/// <summary>
				/// パイプラインステート設定配列
				/// </summary>
				std::vector<PiplineCreateDesc> pipline_{};

				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// ルートシグネチャー設定追加関数
				/// </summary>
				/// <param name="root">追加するルートシグネチャー設定</param>
				void emplace_root(
					std::pair<std::string, ClassObject::desc::RootSignatureDesc>&& root
				) {

					root_.emplace_back(std::move(root));
				}

				/// <summary>
				/// パイプラインステート設定追加関数
				/// </summary>
				/// <param name="pipline">追加するパイプラインステート設定</param>
				void emplace_pipline(
					PiplineCreateDesc&& pipline
				) {

					pipline_.emplace_back(std::move(pipline));
				}

			};
		}

		/// <summary>
		/// 描画パイプライン初期化クラス
		/// </summary>
		class InitializePipline
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// 描画パイプライン初期化関数
			/// </summary>
			/// <param name="context_">DirectXオブジェクトインスタンス構造体参照</param>
			/// <param name="desc_">描画パイプライン設定構造体</param>
			/// <returns>初期化の成否</returns>
			static void initialize_pipline(
				DirectXContext* context_,
				const desc::PiplineDesc& desc_
			) {

				/* ===== RootSignature作成 ===== */
				{
					std::vector<std::string> root_list{};

					for (const auto& [name, desc] : desc_.root_) {

						auto root = std::make_unique<ClassObject::RootSignature>();
						const auto hr = root->create_root_signature(
							context_->device_,
							desc
						);
						if (FAILED(hr)) {
							DEBUG_ERROR_LOG(
								"create_root_signature FAILED = ",
								name
							);
							Initialize::InitializeLog::hresult_error_log(hr);
						}
						else {
							if (!context_->root_signature_container->add_root_signature(
								Container::RootSignatureKey{ name.c_str() },
								std::move(root)
							)) {
								DEBUG_ERROR_LOG(
									"add_root_signature = false",
									"name = ", name
								);
							}
							else {
								root_list.push_back(name);
							}
						}
					}
					DEBUG_LOG(
						HandyItems::Debug::const_str::LineBreak,
						"========== RootSignatureName =========="
					);
					for (auto& name : root_list) {
						DEBUG_LOG(name);
					}
				}

				/* ===== PiplineState作成 ===== */
				{
					std::vector<std::string> pipline_list{};

					for (const auto& [name, ref, desc] : desc_.pipline_) {

						auto pipline = std::make_unique<ClassObject::PiplineState>();

						const auto copy_desc = ClassObject::desc::Factory::PipelineStateDescFactory::create_desc(
							context_,
							desc,
							ref
						);

						const auto hr = pipline->create_pipline(
							context_->device_,
							copy_desc
						);
						if (FAILED(hr)) {
							DEBUG_ERROR_LOG(
								"create_pipline FAILED = ",
								name
							);
							Initialize::InitializeLog::hresult_error_log(hr);
						}
						else {
							if (!context_->pipline_state_container->add_pipline_state(
								Container::PiplineStateKey{ name.c_str() },
								std::move(pipline)
							)) {
								DEBUG_ERROR_LOG(
									"add_pipline_state = false",
									"name = ", name
								);
							}
							else {
								pipline_list.push_back(name);
							}
						}
					}
					DEBUG_LOG(
						HandyItems::Debug::const_str::LineBreak,
						"========== PiplineStateName =========="
					);
					for (auto& name : pipline_list) {
						DEBUG_LOG(name);
					}
				}
			}

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializePipline() = default;

		};
	}
}