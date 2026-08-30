#pragma once
#include"../DirectXobject/ShaderCompiler.h"
#include"KeyMapBase.h"
#include<unordered_map>
#include<memory>
#include<optional>

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

			/// <summary>
			/// シェーダー用エンコードキー
			/// </summary>
			struct ShaderKey {
				std::uint32_t key_value{};
			};

			/// <summary>
			/// シェーダー用ハンドル
			/// </summary>
			struct ShaderHandle {
				ShaderKey shader_key{};
				object::ShaderCompiler* shader_p{};
			};

			
			/// <summary>
			/// シェーダーコンテナクラス
			/// </summary>
			/// <typeparam name="key::DefaultKey">デフォルトキー</typeparam>
			/// <typeparam name="ShaderKey">シェーダー用エンコードキー</typeparam>
			/// <typeparam name="key::DefaultKey">シェーダー用ハンドル</typeparam>
			/// <typeparam name="std::unique_ptr<object::ShaderCompiler>">シェーダーコンパイルクラス</typeparam>
			class StaticShaderContainer final : public KeyMapBase<
				key::DefaultKey,
				ShaderKey,
				ShaderHandle,
				std::unique_ptr<object::ShaderCompiler>
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticShaderContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticShaderContainer() = default;

				/// <summary>
				/// シェーダーコンパイル関数
				/// </summary>
				/// <param name="key">倫理側キーの型</param>
				/// <param name="path">シェーダー絶対パス</param>
				/// <param name="entry_point_name">シェーダー開始関数名</param>
				/// <param name="target_profile">シェーダータイプ</param>
				/// <returns>コンパイルの成否</returns>
				[[nodiscard]] HRESULT compile_shader(const key::DefaultKey& key, const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile);


				/* ===== 取得関数 ===== */

				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key">取得したいシェーダーに紐づいた倫理側キー</param>
				/// <returns>シェーダー用ハンドル</returns>
				[[nodiscard]] ShaderHandle get_handle(const key::DefaultKey& key) noexcept override {

					ShaderHandle handle{};

					const auto* value = get_value_p(key);
					if (value != nullptr) {
						handle.shader_p = value->get();
					}

					handle.shader_key = encode_key(key);
					
					return handle;
				}

				const [[nodiscard]] ShaderHandle get_handle(const key::DefaultKey& key)const noexcept override {

					ShaderHandle handle{};

					const auto* value = get_value_p(key);
					if (value != nullptr) {
						handle.shader_p = value->get();
					}

					handle.shader_key = encode_key(key);

					return handle;
				}


				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="encode_key">取得したいシェーダーに紐づいた保存用キー</param>
				/// <returns>シェーダー用ハンドル</returns>
				[[nodiscard]] ShaderHandle get_handle(const ShaderKey& encode_key) noexcept override {

					ShaderHandle handle{};
					const auto* value = get_value_p(encode_key);
					if (value != nullptr) {
						handle.shader_p = value->get();
					}

					handle.shader_key = encode_key;

					return handle;
				}

				const [[nodiscard]] ShaderHandle get_handle(const ShaderKey& encode_key)const noexcept override {

					ShaderHandle handle{};
					const auto* value = get_value_p(encode_key);
					if (value != nullptr) {
						handle.shader_p = value->get();
					}

					handle.shader_key = encode_key;

					return handle;
				}
			};
		}
	}
}