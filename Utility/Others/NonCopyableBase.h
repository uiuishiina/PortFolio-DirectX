#pragma once

/// <summary>
/// その他名前空間
/// </summary>
namespace others {

	/* ========== [ コピー & ムーブ ] 禁止基底クラス定義 ========== */

	/// <summary>
	/// [ コピー & ムーブ ] 禁止基底クラス
	/// </summary>
	class NonCopyableBase
	{
	public:
		/* ===== メンバー関数 ===== */

		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <details>
		/// メンバー変数がないため [ virtualなし ]
		/// </details>
		~NonCopyableBase() = default;

		//	コピーコンストラクタ削除
		NonCopyableBase(const NonCopyableBase&) = delete;

		//	ムーブコンストラクタ削除
		NonCopyableBase(NonCopyableBase&&) = delete;

		//	コピー代入演算子削除
		NonCopyableBase& operator=(const NonCopyableBase&) = delete;

		//	ムーブ代入演算子削除
		NonCopyableBase& operator=(NonCopyableBase&&) = delete;

	private:
		/* ===== メンバー関数 ===== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <details>
		/// このクラスはインスタンスを作成できないようにするため [ Private]
		/// </details>
		NonCopyableBase() = default;

	};
}