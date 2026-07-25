#pragma once
#include"../DrawPass/DrawPass.h"
#include"NonMovable.h"
#include<unordered_map>
#include<memory>
#include<vector>

///====================================================================
/// 前方宣言
///====================================================================

class HashAllocator;

///====================================================================
/// StaticDrawPassContainer クラス
///====================================================================

//@brief	=== 描画パスコンテナクラス ===
class StaticDrawPassContainer final : public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================



private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== 描画パス保存マップ ===
	//@details	作成できた描画パスを保存するmap
	std::unordered_map<UINT, std::unique_ptr<render::pass::DrawPass>> pass_map{};

	//@brief	== ハッシュアロケーターインスタンス ==
	//@details	シェーダーハッシュキー登録クラス
	std::unique_ptr<HashAllocator> hash_allocator{};
};