#pragma once

/// <summary>
/// その他名前空間
/// </summary>
namespace others {

	/* ========== [ コピー ] 禁止基底クラス定義 ========== */

	/// <summary>
	/// [ コピー ] 禁止基底クラス
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

		//	コピー代入演算子削除
		NonCopyableBase& operator=(const NonCopyableBase&) = delete;

	protected:
		/* ===== メンバー関数 ===== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <details>
		/// このクラスはインスタンスを作成できないようにするため [ protected ]
		/// </details>
		NonCopyableBase() = default;

	};
}