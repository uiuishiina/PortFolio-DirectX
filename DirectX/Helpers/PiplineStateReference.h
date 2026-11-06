#pragma once

#include"../ClassObject/PiplineState.h"

#include"../DirectXContext.h"

#include"../Container/RootSignatureContainer.h"
#include"../Container/ShaderContainer.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DirectXオブジェクト設定構造体名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// パイプラインステート外部参照補助構造体
			/// </summary>
			struct PiplineStateReferenceName {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// ルートシグネチャー登録名
				/// </summary>
				std::string root_name{};

				/// <summary>
				/// 頂点シェーダー登録名
				/// </summary>
				std::string vs_name{};

				/// <summary>
				/// ピクセルシェーダー登録名
				/// </summary>
				std::string ps_name{};

				/// <summary>
				/// ジオメトリシェーダー登録名
				/// </summary>
				std::string gs_name{};

				/// <summary>
				/// ハルシェーダー登録名
				/// </summary>
				std::string hs_name{};

				/// <summary>
				/// ドメインシェーダー登録名
				/// </summary>
				std::string ds_name{};

				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 参照設定関数
				/// </summary>
				/// <details>
				/// 内部でコンテナから参照を取得し、desc に設定する関数
				/// </details>
				/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
				/// <param name="desc">パイプラインステート設定構造体参照</param>
				void set(
					DirectXContext* context_,
					ClassObject::desc::PipelineStateDesc& desc
				) const {

				}

			};


			/// <summary>
			/// ファクトリー名前空間
			/// </summary>
			namespace Factory {

				class PipelineStateDescFactory final
				{
				public:

					[[nodiscard]] static const PipelineStateDesc create_desc(
						DirectXContext* context_,
						const PipelineStateDesc& base_desc,
						const PiplineStateReferenceName& ref
					) {

						PipelineStateDesc copy = base_desc;

						if (!ref.root_name.empty()) {

							if (auto root = context_->root_signature_container->get_root_signature(
								Container::RootSignatureKey{ ref.root_name.c_str() }
							); root) {
								copy.root_ = root->get();
							}
						}

						if (!ref.vs_name.empty()) {

							if (auto vs = context_->shader_container->get_shader(
								Container::ShaderKey{ ref.vs_name.c_str() }
							); vs) {
								copy.vs_hlsl = vs->get();
							}
						}

						if (!ref.ps_name.empty()) {

							if (auto ps = context_->shader_container->get_shader(
								Container::ShaderKey{ ref.ps_name.c_str() }
							); ps) {
								copy.ps_hlsl = ps->get();
							}
						}

						if (!ref.gs_name.empty()) {

							if (auto gs = context_->shader_container->get_shader(
								Container::ShaderKey{ ref.gs_name.c_str() }
							); gs) {
								copy.gs_hlsl = gs->get();
							}
						}

						if (!ref.hs_name.empty()) {

							if (auto hs = context_->shader_container->get_shader(
								Container::ShaderKey{ ref.hs_name.c_str() }
							); hs) {
								copy.ps_hlsl = hs->get();
							}
						}

						if (!ref.ds_name.empty()) {

							if (auto ds = context_->shader_container->get_shader(
								Container::ShaderKey{ ref.ds_name.c_str() }
							); ds) {
								copy.ps_hlsl = ds->get();
							}
						}

						return copy;
					}

				private:

					PipelineStateDescFactory() = default;

				};
			}
		}
	}
}