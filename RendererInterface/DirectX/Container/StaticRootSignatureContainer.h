#pragma once
#include"../DirectXobject/RootSignature.h"
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


			/* ========== ルートシグネチャー用キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// ルートシグネチャー用倫理側派生キー
				/// </summary>
				struct RootSignatureKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					RootSignatureKey() = default;
				
					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit RootSignatureKey(std::uint32_t key) :
						LogicalKey(key) {}
				};

				/// <summary>
				/// ルートシグネチャー用保存側派生キー
				/// </summary>
				struct RSEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					RSEncodeKey() = default;
				};
			}


			/* ========== ルートシグネチャーコンテナクラス定義 ========== */

			/// <summary>
			/// ルートシグネチャーコンテナクラス
			/// </summary>
			/// <typeparam name="handle::RootSignatureKey">ルートシグネチャー用倫理側派生キー</typeparam>
			/// <typeparam name="handle::RSEncodeKey">ルートシグネチャー用保存側派生キー</typeparam>
			/// <typeparam name="object::RootSignature">ルートシグネチャークラス</typeparam>
			class StaticRootSignatureContainer final : public UniqueptrKeyMap<
				handle::RootSignatureKey,
				handle::RSEncodeKey,
				object::RootSignature
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticRootSignatureContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticRootSignatureContainer() = default;


				/// <summary>
				/// ルートシグネチャー作成関数
				/// </summary>
				/// <param name="key">追加したい倫理側のキー</param>
				/// <param name="device">DirectX12デバイスポインター</param>
				/// <param name="desc">ルートシグネチャー設定</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_root_signature(const handle::RootSignatureKey& key, ID3D12Device* device, desc::RootSignatureDesc& desc);

			};
		};
	};
};
