#pragma once
#include"../DirectXobject/ShaderCompiler.h"
#include"StaticContainerBase.h"
#include<unordered_map>
#include<memory>
#include<optional>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			///====================================================================
			/// StaticShaderContainer クラス
			///====================================================================

			//@breif	=== シェーダーコンテナクラス ===
			class StaticShaderContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticShaderContainer() = default;
				~StaticShaderContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== シェーダーコンパイル関数 ===
				//@param	key_name	登録するキーの名前
				//@param	path	登録するシェーダーパス
				//@param	entry_point_name	登録するシェーダーのエントリーポイントの名前
				//@param	target_profile	登録するシェーダーのターゲットプロファイル
				//@return	コンパイルの成否...登録してあるなら [ S_OK ] 
				[[nodiscard]] HRESULT compile_shader(const std::string& key_name, const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile);

				//@brief	=== シェーダー取得関数 ===
				//@param	key	シェーダーと紐づけたキー
				//@return	シェーダー参照
				[[nodiscard]] ID3DBlob* get_shader(UINT key)const noexcept;

				//@brief	=== シェーダー取得関数オーバーロード ===
				//@param	key_name	シェーダーと紐づけたキーの名前
				//@return	シェーダー参照
				[[nodiscard]] ID3DBlob* get_shader(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== シェーダー保存マップ ===
				//@details	コンパイルできたシェーダーを保存するmap
				std::unordered_map<UINT, std::unique_ptr<object::ShaderCompiler>> shader_map{};

			};
		};
	};
};