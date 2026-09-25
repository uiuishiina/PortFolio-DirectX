#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<d3d12.h>
#include<wrl/client.h>

//	その他
#include<string>

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
			/// HLSLシェーダー設定構造体
			/// </summary>
			struct ShaderDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// 絶対パス
				/// </summary>
				std::wstring path{};

				/// <summary>
				/// エントリーポイント名称
				/// </summary>
				std::string entry_point_name{};

				/// <summary>
				/// ターゲットプロファイル(バージョン)
				/// </summary>
				std::string target_profile{};

			};
		}

		/// <summary>
		/// HLSLシェーダーコンパイルクラス
		/// </summary>
		class ShaderCompiler final : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ShaderCompiler() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ShaderCompiler() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// HLSLシェーダーコンパイル関数
			/// </summary>
			/// <param name="desc">HLSLシェーダー設定構造体参照</param>
			/// <returns>コンパイルの成否</returns>
			[[nodiscard]] HRESULT compile_shader(
				desc::ShaderDesc& desc
			);

			/* ===== 取得関数 ===== */

			/// <summary>
			/// HLSLシェーダー参照取得関数
			/// </summary>
			/// <returns>HLSLシェーダー参照</returns>
			[[nodiscard]] ID3DBlob* get()const noexcept {

				return shader_blob.Get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// HLSLシェーダーインスタンス
			/// </summary>
			/// <details>
			/// コンパイルしたシェーダー
			/// </details>
			Microsoft::WRL::ComPtr<ID3DBlob> shader_blob;

		};
	}
}