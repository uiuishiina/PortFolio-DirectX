#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/RootSignature.h"

//	その他
#include<span>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 補助名前空間
	/// </summary>
	namespace Helper {

		/// <summary>
		/// ルートシグネチャー設定構造体補助クラス
		/// </summary>
		class RootSignatureHelper 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプタテーブル追加関数
			/// </summary>
			/// <param name="ranges">追加するテーブル配列</param>
			/// <param name="visibility">シェーダー可視フラグ</param>
			/// <returns>追加するルートパラメーター</returns>
			[[nodiscard]] static D3D12_ROOT_PARAMETER add_table(
				std::span<const D3D12_DESCRIPTOR_RANGE> ranges,
				D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL
			) {

				auto root = initialize(
					D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, 
					visibility
				);

				root.DescriptorTable.NumDescriptorRanges = static_cast<UINT>(ranges.size());
				root.DescriptorTable.pDescriptorRanges = ranges.data();

				return root;
			}

			/// <summary>
			/// コンスタント追加関数
			/// </summary>
			/// <param name="shader_register">シェーダー登録番号</param>
			/// <param name="num_values">コンスタントに入れる値</param>
			/// <param name="register_space">レジスタースペース</param>
			/// <param name="visibility">シェーダー可視フラグ</param>
			/// <returns>追加するルートパラメーター</returns>
			[[nodiscard]] static D3D12_ROOT_PARAMETER add_constant(
				UINT shader_register,
				UINT num_values,
				UINT register_space = 0,
				D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL
			) {

				auto root = initialize(
					D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS, 
					visibility
				);

				root.Constants.ShaderRegister = shader_register;
				root.Constants.RegisterSpace = register_space;
				root.Constants.Num32BitValues = num_values;

				return root;
			}

			/// <summary>
			/// ディスクリプター追加関数
			/// </summary>
			/// <param name="type">ディスクリプタータイプ</param>
			/// <param name="shader_register">シェーダー登録番号</param>
			/// <param name="register_space">レジスタースペース</param>
			/// <param name="visibility">シェーダー可視フラグ</param>
			/// <returns>追加するルートパラメーター</returns>
			[[nodiscard]] static D3D12_ROOT_PARAMETER add_descriptor(
				D3D12_ROOT_PARAMETER_TYPE type,
				UINT shader_register,
				UINT register_space = 0,
				D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL
			) {

				auto root = initialize(type, visibility);

				root.Descriptor.ShaderRegister = shader_register;
				root.Descriptor.RegisterSpace = register_space;

				return root;
			}

		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			RootSignatureHelper() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~RootSignatureHelper() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// ルートパラメーター初期化関数
			/// </summary>
			/// <param name="type">ルートパラメータータイプ</param>
			/// <param name="visibility">シェーダー可視フラグ</param>
			/// <returns>初期化したルートパラメーター</returns>
			[[nodiscard]] static D3D12_ROOT_PARAMETER initialize(
				D3D12_ROOT_PARAMETER_TYPE type,
				D3D12_SHADER_VISIBILITY visibility
			) {

				D3D12_ROOT_PARAMETER root{};
				root.ParameterType = type;
				root.ShaderVisibility = visibility;

				return root;
			}

		};
	}
}