#pragma once
#include"RendererInterface.h"
#include<memory>

///====================================================================
/// RendererFactory クラス
///====================================================================

//@brief	=== 描画機能ファクトリークラス ===
class RendererFactory final
{
public:
	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== 描画機能作成関数 ===
	//@param	window	作成に使用するウィンドウクラス参照
	//@return	描画機能クラスインスタンス
	static std::unique_ptr<RendererInterface> create_renderer(windowInterface* window, sharedData::ApplicationSharedData* shared_datas);

private:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	RendererFactory() = default;
	~RendererFactory() = default;

};