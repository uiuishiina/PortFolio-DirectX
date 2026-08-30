#pragma once
#include<DirectXMath.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace directx {

	/// <summary>
	/// 行列名前空間
	/// </summary>
	namespace matrix {

		/// <summary>
		/// 行列ラッパークラス
		/// </summary>
		struct matrix {


			DirectX::XMMATRIX matrix_{};

			matrix() :matrix_(create_identety()) {}

			float& pos_x() {
				return matrix_.r[3].m128_f32[0];
			}

			float& pos_y() noexcept	{
				return matrix_.r[3].m128_f32[1];
			}

			float& pos_z() noexcept	{
				return matrix_.r[3].m128_f32[2];
			}



		};

		[[nodiscard]] DirectX::XMMATRIX create_identety() noexcept {
			return DirectX::XMMatrixIdentity();
		};



	}
}