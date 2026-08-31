#pragma once
#include"../DirectXobject/PipelineState.h"
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


			/* ========== パイプラインステート用キー定義 ========== */

			namespace handle {

				/// <summary>
				/// パイプラインステート用倫理側派生キー
				/// </summary>
				struct PiplineStateKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					PiplineStateKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit PiplineStateKey(std::uint32_t key) :
						LogicalKey(key) {}
				};

				/// <summary>
				/// パイプラインステート用保存側派生キー
				/// </summary>
				struct PSEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					PSEncodeKey() = default;
				};
			}


			/* ========== パイプラインステートコンテナクラス定義 ========== */

			/// <summary>
			/// パイプラインステートコンテナクラス
			/// </summary>
			/// <typeparam name="key::DefaultKey">パイプラインステート用倫理側派生キー</typeparam>
			/// <typeparam name="PiplineStateKey">パイプラインステート用保存側派生キー</typeparam>
			/// <typeparam name="object::PipelineState>">パイプラインステートクラス</typeparam>
			class StaticPiplineStateContainer final : public UniqueptrKeyMap<
				handle::PiplineStateKey,
				handle::PSEncodeKey,
				object::PipelineState
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticPiplineStateContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticPiplineStateContainer() = default;


				/// <summary>
				/// パイプラインステート作成関数
				/// </summary>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="device">DirectX12デバイスポインター</param>
				/// <param name="desc">パイプラインステート設定</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_pipline_state(const handle::PiplineStateKey& key, ID3D12Device* device, desc::PipelineStateDesc& desc);

			};
		};
	};
};