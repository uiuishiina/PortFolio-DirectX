#pragma once
#include<concepts>
#include<queue>
#include<optional>

///====================================================================
/// ReferenceQueue クラス
///====================================================================

/*

	参照を保存するためだけに用意するテンプレートキュークラス
	参照先のライフタイムに関しては外部に依存

*/

//@brief	=== 参照保存キュークラス ===
//@details	T 保存する参照の型
template<typename T>
class ReferenceQueue final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	ReferenceQueue() = default;
	~ReferenceQueue() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	/* -- 追加関数 -- */

	//@breif	=== 参照追加関数 ===
	//@param	value	追加する参照
	void push_queue(T& value) {
		reference_queue.push(value);
	}

	//@breif	=== 参照追加オーバーロード関数 ===
	//@param	value	追加する参照配列
	template<std::ranges::range R>
	void push_queue(R& range) {
		for (auto& p : range) {
			reference_queue.push(p);
		}
	}

	/* -- 取得関数 -- */

	//@brief	=== 参照取得関数 ===
	//@return	キューから取り出した参照 ...ないなら [ std::nullpot ]
	[[nodiscard]] std::optional<std::reference_wrapper<T>> get_reference() {

		if (reference_queue.empty()) {
			return std::nullopt;
		}

		auto ref = reference_queue.front();
		reference_queue.pop();
		return ref;
	}

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	=== 参照保存キュー ==
	//@details	外部から追加された参照を保存するだけ
	std::queue<std::reference_wrapper<T>> reference_queue{};
};