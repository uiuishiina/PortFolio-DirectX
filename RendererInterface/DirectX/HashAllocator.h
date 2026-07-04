#pragma once
#include<unordered_map>
#include<string>
#include<optional>

///====================================================================
/// UINT互換typeof
///====================================================================

typedef unsigned int UINT;

///====================================================================
/// HashAllocator クラス
///====================================================================

//@brief	=== ハッシュキー割り当てクラス ===
class HashAllocator final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================
	
	//コンストラクタ,デストラクタ
	HashAllocator() = default;
	~HashAllocator() = default;

	//コピー禁止,ムーブ禁止
	HashAllocator(const HashAllocator&) = delete;
	HashAllocator& operator=(const HashAllocator&) = delete;
	HashAllocator(HashAllocator&&) = delete;
	HashAllocator& operator=(HashAllocator&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ハッシュキー取得関数 ===
	//@param	key	登録するキーネーム
	//@param	登録したキー...登録済みなら登録してあるキーを返す
	[[nodiscard]] UINT allocate_hash(const std::string& key);

	//@brief	=== 登録済みハッシュキー取得関数 ===
	//@param	key	登録したキーネーム
	//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
	[[nodiscard]] std::optional<UINT> get_hash(const std::string& key);

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== ハッシュキー割り当て用変数 ==
	UINT key_value{};

	//@brief	== ハッシュキーマップ ==
	std::unordered_map<std::string, UINT> key_map{};
};