#pragma once

/* ========== Includeファイル ========== */

#include"../ClassObject/ShaderCompiler.h"

#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// シェーダー設定構造体作成補助関数
	/// </summary>
	/// <param name="name">シェーダー名称</param>
	/// <param name="desc">HLSLシェーダー設定構造体</param>
	/// <returns>作成したシェーダー設定構造体の要素</returns>
	[[nodiscard]] inline std::pair<
		std::string,
		ClassObject::desc::ShaderDesc
	> make_shader_desc(
		std::string name,
		const ClassObject::desc::ShaderDesc& desc
	) {

		return { name,desc };
	}

	/// <summary>
	/// シェーダー設定構造体作成補助関数オーバーロード
	/// </summary>
	/// <param name="desc_">下部名前空間等で事前作成した要素</param>
	/// <returns>作成したシェーダー設定構造体の要素</returns>
	[[nodiscard]] inline std::pair<
		std::string,
		ClassObject::desc::ShaderDesc
	> make_shader_desc(
		const std::pair<
		std::string,
		ClassObject::desc::ShaderDesc
		>& desc_
	) {

		return { desc_ };
	}

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// シェーダー名前空間
		/// </summary>
		namespace Shaders {

			using UsingShader = std::pair<
				std::string,
				ClassObject::desc::ShaderDesc
			>;

			const UsingShader NormalVertex{
				"NormalVertex",
				{
					L"../DirectX/Resource/HLSL/NormalVertex.hlsl",
					"main",
					"vs_5_0"
				}
			};

			const UsingShader NormalPixel{
				"NormalPixel",
				{
					L"../DirectX/Resource/HLSL/NormalPixel.hlsl",
					"main",
					"ps_5_0"
				}
			};

		}
	}
}