#pragma once


/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// その他名前空間
	/// </summary>
	namespace others {


		/* ========== [ コピー ] 禁止基底クラス ========== */

		/// <summary>
		/// [ コピー ] 禁止基底クラス
		/// </summary>
		class NonCopyableBase
		{
		public:
			/* ===== Publicメンバー関数 ===== */

			//	コピーコンストラクタ削除
			NonCopyableBase(const NonCopyableBase&) = delete;

			//	コピー代入演算子削除
			NonCopyableBase& operator=(const NonCopyableBase&) = delete;

			/// <summary>
			/// ムーブコンストラクタ
			/// </summary>
			/// <param name="">右辺値</param>
			NonCopyableBase(NonCopyableBase&&) = default;

			/// <summary>
			/// ムーブ代入演算子
			/// </summary>
			/// <param name="">右辺値</param>
			/// <returns>自身参照</returns>
			NonCopyableBase& operator=(NonCopyableBase&&) = default;

		protected:
			/* ===== Protectedメンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			NonCopyableBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~NonCopyableBase() = default;

		};


		/* ========== [ ムーブ ] 禁止基底クラス ========== */

		/// <summary>
		/// [ ムーブ ] 禁止基底クラス
		/// </summary>
		class NonMovableBase
		{
		public:
			/* ===== Publicメンバー関数 ===== */

			/// <summary>
			/// コピーコンストラクタ
			/// </summary>
			/// <param name="">左辺値</param>
			NonMovableBase(const NonMovableBase&) = default;

			/// <summary>
			/// コピー代入演算子
			/// </summary>
			/// <param name="">左辺値</param>
			/// <returns>自身参照</returns>
			NonMovableBase& operator=(const NonMovableBase&) = default;

			//	ムーブコンストラクタ削除
			NonMovableBase(NonMovableBase&&) = delete;

			//	ムーブ代入演算子削除
			NonMovableBase& operator=(NonMovableBase&&) = delete;

		protected:
			/* ===== Protectedメンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			NonMovableBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~NonMovableBase() = default;

		};


		/* ========== [ コピー & ムーブ ] 禁止基底クラス ========== */

		/// <summary>
		/// [ コピー & ムーブ ] 禁止基底クラス
		/// </summary>
		class NonCopyableMovableBase
		{
		public:
			/* ===== Publicメンバー関数 ===== */

			//	コピーコンストラクタ削除
			NonCopyableMovableBase(const NonCopyableMovableBase&) = delete;

			//	ムーブコンストラクタ削除
			NonCopyableMovableBase(NonCopyableMovableBase&&) = delete;

			//	コピー代入演算子削除
			NonCopyableMovableBase& operator=(const NonCopyableMovableBase&) = delete;

			//	ムーブ代入演算子削除
			NonCopyableMovableBase& operator=(NonCopyableMovableBase&&) = delete;

		protected:
			/* ===== Protectedメンバー関数 ===== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <details>
			/// このクラスはインスタンスを作成できないようにするため [ Protected ]
			/// </details>
			NonCopyableMovableBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			/// <details>
			/// メンバー変数がないため [ virtualなし ]
			/// </details>
			~NonCopyableMovableBase() = default;

		};
	}
}