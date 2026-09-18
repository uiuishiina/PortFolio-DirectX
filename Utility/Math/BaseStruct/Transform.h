#pragma once
#include"../Function/MathFQuaternion.h"
#include"../Function/MathFMatrix.h"

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItem {

	/// <summary>
	/// 数学名前空間
	/// </summary>
	namespace Math {

		/// <summary>
		/// トランスフォーム構造体
		/// </summary>
		struct Transform {

			/* ========== メンバー変数 ========== */

			/// <summary>
			/// 平行移動量
			/// </summary>
			Float3 translation_{};

			/// <summary>
			/// 回転量
			/// </summary>
			Quaternion rotation_{};

			/// <summary>
			/// 拡大率
			/// </summary>
			Float3 scale_{ 1,1,1 };

			/// <summary>
			/// 親トランスフォーム構造体
			/// </summary>
			Transform* parent_{};

			/* ========== メンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Transform() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="translate">平行移動量</param>
			/// <param name="rotate">回転量</param>
			/// <param name="scale">拡大率</param>
			Transform(
				const Float3& translate,
				const Quaternion& rotate,
				const Float3& scale
			) :
				translation_{ translate },
				rotation_{ rotate },
				scale_{ scale } {
			}

			/// <summary>
			/// 行列取得関数
			/// </summary>
			/// <returns>取得した行列</returns>
			[[nodiscard]] Matrix get_matrix() const {

				const auto mat = MathF::transform_to_matrix(
					translation_,
					rotation_,
					scale_
				);

				return parent_ ? parent_->get_matrix() * mat : mat;
			}

			/// <summary>
			/// 平行移動適用関数
			/// </summary>
			/// <param name="move">適用する移動ベクトル</param>
			void translate(
				const Float3& move
			) {

				translation_ += move;
			}
			
			/// <summary>
			/// 回転適用関数
			/// </summary>
			/// <param name="rotation">適用するクオータニオン</param>
			void rotate(
				const Quaternion& delta
			) {

				rotation_ = (
					rotation_ * delta
					).normalized();
			}

			/// <summary>
			/// 回転適用関数
			/// </summary>
			/// <param name="euler">適用するオイラー角</param>
			void rotate(
				const Float3& euler
			) {

				rotate(
					MathF::from_euler(euler)
				);
			}

			/// <summary>
			/// 拡大率適用関数
			/// </summary>
			/// <param name="scale">適用する拡大率</param>
			void scale_by(
				const Float3& scale
			) {

				scale_.x_ *= scale.x_;
				scale_.y_ *= scale.y_;
				scale_.z_ *= scale.z_;
			}
		
			void set_parent(Transform& trans) {

				parent_ = &trans;
			}

			void delete_parent() {

				parent_ = nullptr;
			}

		};
	}
}