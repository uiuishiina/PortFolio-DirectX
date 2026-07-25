#pragma once

///====================================================================
/// NonMovableBase 基底クラス
///====================================================================

//@brief	=== コピー禁止,ムーブ禁止基底クラス ===
class NonMovableBase
{
protected:
	///====================================================================
	/// クラス設定
	///====================================================================

	/*
		このクラス単体で生成できないようにProtectedで作成
	*/

	//コンストラクタ,デストラクタ
	NonMovableBase() = default;
	~NonMovableBase() = default;

public:
	///====================================================================
	/// 継承する設定
	///====================================================================

	//コピー禁止,ムーブ禁止
	NonMovableBase(const NonMovableBase&) = delete;
	NonMovableBase& operator=(const NonMovableBase&) = delete;
	NonMovableBase(NonMovableBase&&) = delete;
	NonMovableBase& operator=(NonMovableBase&&) = delete;
};