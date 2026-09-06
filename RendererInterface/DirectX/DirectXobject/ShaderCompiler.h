#pragma once
#include"Others/NonCopyableBase.h"
#include<d3d12.h>
#include<wrl/client.h>
#include<string>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// シェーダーコンパイラークラス
			/// </summary>
			class ShaderCompiler final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ShaderCompiler() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ShaderCompiler() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// HLSLシェーダーコンパイル関数
				/// </summary>
				/// <param name="path">コンパイルするHLSLシェーダーの絶対パス</param>
				/// <param name="entry_point_name">HLSLシェーダーのエントリーポイントの名前</param>
				/// <param name="target_profile">HLSLシェーダーのターゲットプロファイル(バージョン)</param>
				/// <returns>コンパイルの成否</returns>
				[[nodiscard]] HRESULT compile_shader(
					const std::wstring& path, 
					const std::string& entry_point_name, 
					const std::string& target_profile
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// HLSLシェーダー取得関数
				/// </summary>
				/// <returns>HLSLシェーダー参照</returns>
				[[nodiscard]] ID3DBlob* get_shader()const noexcept;

			private:
				/* ========== Publicメンバー変数 ========== */

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
}
