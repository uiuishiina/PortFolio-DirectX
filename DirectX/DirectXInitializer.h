#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	App
#include"../Application/ApplicationDataShare.h"

//	DirectX
#include"DirectXContext.h"

#include"Initializer/InitializeLog.h"
#include"Initializer/InitializeCore.h"
#include"Initializer/InitializePath.h"
#include"Initializer/InitializeShader.h"
#include"Initializer/InitializePipline.h"
#include"Initializer/InitializeResource.h"

//	その他
#include<concepts>
#include<cstdint>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {


	/// <summary>
	/// 
	/// </summary>
	namespace desc {

		/// <summary>
		/// 初期化設定構造体
		/// </summary>
		struct InitializeDesc {

			/* ========== メンバー変数 ========== */

			/* -- Common -- */

			DirectXContext* context_;
			App::ApplicationDataShare* share_p;
			UINT back_buffer_size;
			UINT frame_resource_size;

			/* -- Core -- */

			Initialize::desc::CoreDesc core_{};

			/* -- Shader -- */

			Initialize::desc::ShaderDesc shader_{};

			/* -- Pipline -- */

			Initialize::desc::PiplineDesc pipline_{};

			/* -- Resources -- */

			Initialize::desc::ResourceDesc resource_{};


			/* -- Passes -- */

			Initialize::desc::PathDesc pass_{};
		};
	}

	/* ========== 前方宣言 ========== */

	class DirectXUpdator;

	/// <summary>
	/// DirectX初期化クラス
	/// </summary>
	/// <typeparam name="Core">Core初期化クラス</typeparam>
	template<
	typename Core = Initialize::InitializeCore
	>
	requires
	std::derived_from<Core, Initialize::InitializeCoreBase>
	class DirectXInitializer final : HandyItems::others::NonCopyableMovableBase 
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// DirectX初期化フロー呼び出し関数
		/// </summary>
		/// <param name="desc">初期化設定構造体参照</param>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize(
			const desc::InitializeDesc& desc
		) {

			//	コア機能初期化

			Core core{};
			auto hr = core.initialize_core(
				desc.context_,
				desc.back_buffer_size,
				desc.frame_resource_size,
				desc.core_
			);
			if (FAILED(hr)) {
				Initialize::InitializeLog::hresult_error_log(hr);
				return false;
			}


			//	シェーダー初期化

			Initialize::InitializeShader::initialize_shader(
				desc.context_,
				desc.shader_
			);

			//	描画パイプライン初期化

			Initialize::InitializePipline::initialize_pipline(
				desc.context_,
				desc.pipline_
			);

			//	描画リソース初期化

			Initialize::InitializeResource::initialize_resource(
				desc.context_,
				desc.resource_
			);

			//	描画パス初期化

			Initialize::InitializePath::initialize_path(
				desc.context_,
				desc.pass_
			);

			return true;
		}

	};
}