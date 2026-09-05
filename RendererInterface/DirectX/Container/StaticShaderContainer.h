#pragma once
#include"../DirectXobject/ShaderCompiler.h"
#include"UniqueptrKeyMap.h"

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// コンテナ名前空間
		/// </summary>
		namespace container {


			/* ========== シェーダー用キー定義 ========== */

			namespace handle {

				/// <summary>
				/// シェーダー用倫理側派生キー
				/// </summary>
				struct ShaderKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					ShaderKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit ShaderKey(std::uint32_t key) :
						LogicalKey(key) {}
				};

				/// <summary>
				/// シェーダー用保存側派生キー
				/// </summary>
				struct ShaderEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					ShaderEncodeKey() = default;
				};
			}


			/* ========== シェーダーコンテナクラス定義 ========== */
			
			/// <summary>
			/// シェーダーコンテナクラス
			/// </summary>
			/// <typeparam name="handle::ShaderKey">シェーダー用倫理側派生キー</typeparam>
			/// <typeparam name="handle::ShaderEncodeKey">シェーダー用保存側派生キー</typeparam>
			/// <typeparam name="std::unique_ptr<object::ShaderCompiler>">シェーダーコンパイルクラス</typeparam>
			class StaticShaderContainer final : public UniqueptrKeyMap<
				handle::ShaderKey,
				handle::ShaderEncodeKey,
				object::ShaderCompiler
			>
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticShaderContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticShaderContainer() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// シェーダーコンパイル関数
				/// </summary>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="path">シェーダー絶対パス</param>
				/// <param name="entry_point_name">シェーダー開始関数名</param>
				/// <param name="target_profile">シェーダータイプ</param>
				/// <returns>コンパイルの成否</returns>
				[[nodiscard]] HRESULT compile_shader(const handle::ShaderKey& key, const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile);

			};
		}
	}
}