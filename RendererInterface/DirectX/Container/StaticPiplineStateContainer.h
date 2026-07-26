#pragma once
#include"../DirectXobject/PipelineState.h"
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
			/// StaticPiplineStateContainer クラス
			///====================================================================

			//@brief	=== パイプラインステートコンテナクラス ===
			class StaticPiplineStateContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticPiplineStateContainer() = default;
				~StaticPiplineStateContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== パイプラインステート作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	device	DirectX12 デバイス
				//@param	desc	パイプラインステート設定
				//@return	作成の成否
				[[nodiscard]] HRESULT create_pipline_state(const std::string& key_name, ID3D12Device* device, desc::PipelineStateDesc& desc);

				//@brief	=== パイプラインステート取得関数 ===
				//@param	key	パイプラインステートと紐づけたキー
				//@return	パイプラインステート参照
				[[nodiscard]] ID3D12PipelineState* get_pipline_state(UINT key)const noexcept;

				//@brief	=== パイプラインステート取得関数オーバーロード ===
				//@param	key_name	パイプラインステートと紐づけたキーの名前
				//@return	パイプラインステート参照
				[[nodiscard]] ID3D12PipelineState* get_pipline_state(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== パイプラインステート保存マップ ===
				//@details	作成できたパイプラインステートを保存するmap
				std::unordered_map<UINT, std::unique_ptr<object::PipelineState>> pipline_map{};

			};
		};
	};
};