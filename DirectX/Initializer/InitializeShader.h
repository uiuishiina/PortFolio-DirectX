#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Debug/DebugLogSystem.h"

//	DirectX
#include"../DirectXContext.h"
#include"../Container/ShaderContainer.h"

//	その他
#include<utility>


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
			/// シェーダー設定構造体
			/// </summary>
			struct ShaderDesc {
				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// シェーダー設定リスト
				/// </summary>
				std::vector<std::pair<std::string,ClassObject::desc::ShaderDesc>> shader_{};

				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// シェーダー設定追加関数
				/// </summary>
				/// <param name="shader">追加する設定</param>
				void emplace(
					std::pair<std::string, ClassObject::desc::ShaderDesc>&& shader
				) {

					shader_.push_back(shader);
				}

			};
		}

		/// <summary>
		/// シェーダー初期化クラス
		/// </summary>
		class InitializeShader
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializeShader() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializeShader() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// シェーダー初期化関数
			/// </summary>
			/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
			/// <param name="desc">シェーダー設定構造体参照</param>
			/// <returns>初期化の成否</returns>
			[[nodiscard]] static HRESULT initialize_shader(
				DirectXContext* context,
				desc::ShaderDesc& desc_
			) {

				for (auto& [name,desc] : desc_.shader_) {

					auto shader = std::make_unique<ClassObject::ShaderCompiler>();
					const auto hr = shader->compile_shader(desc);
					if (FAILED(hr)) {
						DEBUG_ERROR_LOG(
							"initialize_shader FAILED = ",
							name,
							HandyItems::Debug::const_str::LineBreak,

							HandyItems::Debug::ConvertString::to_utf8(desc.path),
							HandyItems::Debug::const_str::LineBreak,

							desc.entry_point_name,
							HandyItems::Debug::const_str::LineBreak,

							desc.target_profile
							);
						return hr;
					}

					if (!context->shader_container->add_shader(
						Container::ShaderKey{ name.c_str() },
						std::move(shader)
					)) {

						DEBUG_ERROR_LOG(
							"add_shader = false",
							"name = ", name
						);
						return E_FAIL;
					}
				}

				return S_OK;
			}

		};
	}
}