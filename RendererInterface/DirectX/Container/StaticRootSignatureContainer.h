#pragma once
#include"../DirectXobject/RootSignature.h"
#include"StaticContainerBase.h"
#include<string>
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
			/// StaticRootSignatureContainer クラス
			///====================================================================

			//@brief	=== 初期作成ルートシグネチャーコンテナクラス ===
			class StaticRootSignatureContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticRootSignatureContainer() = default;
				~StaticRootSignatureContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== ルートシグネチャー作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	device	DirectX12 デバイス
				//@param	desc	ルートシグネチャー設定
				//@return	作成の成否
				[[nodiscard]] HRESULT create_root_signature(const std::string& key_name, ID3D12Device* device, desc::RootSignatureDesc& desc);

				//@brief	=== ルートシグネチャー取得関数 ===
				//@param	key	ルートシグネチャーと紐づけたキー
				//@return	ルートシグネチャーインスタンス
				[[nodiscard]] ID3D12RootSignature* get_root_signature(UINT key)const noexcept;

				//@brief	=== ルートシグネチャー取得関数オーバーロード ===
				//@param	key_name	ルートシグネチャーと紐づけたキーの名前
				//@return	ルートシグネチャーインスタンス
				[[nodiscard]] ID3D12RootSignature* get_root_signature(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== ルートシグネチャー保存マップ ===
				//@details	作成できたルートシグネチャーを保存するmap
				std::unordered_map<UINT, std::unique_ptr<object::RootSignature>> root_map{};

			};
		};
	};
};
