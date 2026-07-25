#include "HashAllocator.h"

//@brief	=== ハッシュキー取得関数 ===
//@param	key	登録するキーネーム
//@return	登録したキー...登録済みなら登録してあるキーを返す
[[nodiscard]] UINT HashAllocator::allocate_hash(const std::string& key)
{
    //  登録済みか確認
    const auto it = key_map.find(key);
    if (it != key_map.end()) {
        return it->second;
    }

    key_map.emplace(key, ++key_value);
    return key_value;
}

//@brief	=== 登録済みハッシュキー取得関数 ===
//@param	key	登録したキーネーム
//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
[[nodiscard]] std::optional<UINT> HashAllocator::get_hash(const std::string& key) {

    const auto it = key_map.find(key);
    if (it == key_map.end()) {
        return std::nullopt;
    }
    return it->second;
}