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

					if (!root_name.empty()) {

						if (auto root = context_->root_signature_container->get_root_signature(
							Container::RootSignatureKey{ root_name.c_str() }
						); root) {
							desc.root_ = root->get();
						}
					}

					if (!vs_name.empty()) {

						if (auto vs = context_->shader_container->get_shader(
							Container::ShaderKey{ vs_name.c_str() }
						); vs) {
							desc.vs_hlsl = vs->get();
						}
					}

					if (!ps_name.empty()) {

						if (auto ps = context_->shader_container->get_shader(
							Container::ShaderKey{ ps_name.c_str() }
						); ps) {
							desc.ps_hlsl = ps->get();
						}
					}

					if (!gs_name.empty()) {

						if (auto gs = context_->shader_container->get_shader(
							Container::ShaderKey{ gs_name.c_str() }
						); gs) {
							desc.gs_hlsl = gs->get();
						}
					}

					if (!hs_name.empty()) {

						if (auto hs = context_->shader_container->get_shader(
							Container::ShaderKey{ hs_name.c_str() }
						); hs) {
							desc.ps_hlsl = hs->get();
						}
					}

					if (!ds_name.empty()) {

						if (auto ds = context_->shader_container->get_shader(
							Container::ShaderKey{ ds_name.c_str() }
						); ds) {
							desc.ps_hlsl = ds->get();
						}
					}
				}

			};
		}
	}
}