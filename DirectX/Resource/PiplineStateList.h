#pragma once

/* ========== Includeファイル ========== */

#include"../ClassObject/RootSignature.h"
#include"../ClassObject/PiplineState.h"

#include"../Helpers/RootSignatureHelper.h"
#include"../Helpers/PiplineStateHelper.h"

#include"../Helpers/PiplineStateReference.h"

#include<vector>
#include<tuple>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// ルートシグネチャー名前空間
		/// </summary>
		namespace RootSignatures {

			using UsingRootSignature = std::pair<
				std::string, 
				ClassObject::desc::RootSignatureDesc
			>;

			const UsingRootSignature Normal{
				"Normal",
				{
					.flags_ = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
				}
			};

			const UsingRootSignature Color{
				"Color",
				{
					.flags_ = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
				}
			};

		}
		
		/// <summary>
		/// パイプラインステート名前空間
		/// </summary>
		namespace PiplineStates {

			using UsingPiplineState = std::tuple<
				std::string,
				ClassObject::desc::PiplineStateReferenceName,
				ClassObject::desc::PipelineStateDesc
			>;

			/// <summary>
			/// 設定上書き関数
			/// </summary>
			/// <typeparam name="T">上書きする設定</typeparam>
			/// <typeparam name="Func">適用する関数</typeparam>
			/// <param name="value">上書きする設定</param>
			/// <param name="func">適用する関数</param>
			/// <returns>上書き下設定</returns>
			template<typename T, typename Func>
			T Override(T value, Func&& func) {

				func(value);
				return value;
			}

			const UsingPiplineState Normal{
				"Normal",
				{
					.root_name = "Normal",
					.vs_name = "NormalVertex",
					.ps_name = "NormalPixel"
				},
				{
					.input_elements = {
						{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
					},
					.rasterizer_desc = Override(
						Helper::PiplineStateHelper::default_rasterizer(),
						[](auto& desc) {
							desc.FillMode = static_cast<D3D12_FILL_MODE>(3);
						}),
					.blend_desc = Helper::PiplineStateHelper::default_blend(),
					.depth_stencil_desc = Helper::PiplineStateHelper::default_depth()
				}
			};

			const UsingPiplineState Color{
				"Color",
				{
					.root_name = "Color",
					.vs_name = "ColorVertex",
					.ps_name = "ColorPixel"
				},
				{
					.input_elements = {
						{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
						{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
					},
					.rasterizer_desc = Override(
						Helper::PiplineStateHelper::default_rasterizer(),
						[](auto& desc) {
							desc.FillMode = static_cast<D3D12_FILL_MODE>(3);
						}),
					.blend_desc = Helper::PiplineStateHelper::enable_blend(),
					.depth_stencil_desc = Helper::PiplineStateHelper::default_depth()
				}
			};

		}
	}


	/// <summary>
	/// ルートシグネチャー作成構造体補助関数
	/// </summary>
	/// <param name="name">ルートシグネチャー名称</param>
	/// <param name="desc">ルートシグネチャー設定構造体</param>
	/// <returns>作成したルートシグネチャー作成構造体の要素</returns>
	[[nodiscard]] inline std::pair<
		std::string,
		ClassObject::desc::RootSignatureDesc
	> make_root_desc(
		std::string name,
		const ClassObject::desc::RootSignatureDesc& desc
	) {

		return { name,desc };
	}

	/// <summary>
	/// ルートシグネチャー作成構造体補助関数オーバーロード
	/// </summary>
	/// <param name="desc_">上部名前空間等で事前作成した要素</param>
	/// <returns>作成したルートシグネチャー作成構造体の要素</returns>
	[[nodiscard]] inline std::pair<
		std::string,
		ClassObject::desc::RootSignatureDesc
	> make_root_desc(
		const Resource::RootSignatures::UsingRootSignature& desc_
	) {

		return { desc_ };
	}

	/// <summary>
	/// パイプラインステート作成構造体補助関数
	/// </summary>
	/// <param name="name">パイプラインステート名称</param>
	/// <param name="ref">パイプラインステート外部参照補助構造体</param>
	/// <param name="desc">パイプラインステート設定構造体</param>
	/// <returns>作成したパイプラインステート作成構造体の要素</returns>
	[[nodiscard]] inline std::tuple<
		std::string,
		ClassObject::desc::PiplineStateReferenceName,
		ClassObject::desc::PipelineStateDesc
	> make_pipline_desc(
		std::string name,
		ClassObject::desc::PiplineStateReferenceName ref,
		ClassObject::desc::PipelineStateDesc desc
	) {

		return { name,ref,desc };
	}

	/// <summary>
	/// パイプラインステート作成構造体補助関数オーバーロード
	/// </summary>
	/// <param name="desc_">上部名前空間等で事前作成した要素</param>
	/// <returns>作成したパイプラインステート作成構造体の要素</returns>
	[[nodiscard]] inline std::tuple<
		std::string,
		ClassObject::desc::PiplineStateReferenceName,
		ClassObject::desc::PipelineStateDesc
	> make_pipline_desc(
		const Resource::PiplineStates::UsingPiplineState& desc_
	) {

		return { desc_ };
	}
}