#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	App
#include"../Application/ApplicationDataShare.h"

//	DirectX
#include"DirectXContext.h"
#include"Initializer/InitializeCore.h"
//#include"Initializer/InitializePass.h"

//	その他
#include<concepts>
#include<cstdint>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期作成時ログ出力クラス
	/// </summary>
	class InitializeLog final
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/* ===== 実行関数 ===== */

		/// <summary>
		/// HRESULTログ出力関数
		/// </summary>
		/// <param name="hr">ログに出力するHRESULT</param>
		static void hresult_log(
			HRESULT hr
		);

		/// <summary>
		/// HRESULTエラーログ出力関数
		/// </summary>
		/// <param name="hr">ログに出力するHRESULT</param>
		static void hresult_error_log(
			HRESULT hr
		);

	private:
		/* ========== Privateメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		InitializeLog() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~InitializeLog() = default;

	};


	/// <summary>
	/// 
	/// </summary>
	namespace desc {

		struct InitializeDesc {

			/* ========== メンバー変数 ========== */

			/* -- Common -- */

			DirectXContext* context_;
			App::ApplicationDataShare* share_p;
			UINT back_buffer_size;
			UINT frame_resource_size;

			/* -- Core -- */

			Initialize::desc::CoreDesc core_{};

			/* -- Pass -- */

			//Initialize::desc::PassDesc pass_{};

		};
	}

	/* ========== 前方宣言 ========== */

	class DirectXUpdator;

	/// <summary>
	/// DirectX初期化クラス
	/// </summary>
	/// <typeparam name="Core">Core初期化クラス</typeparam>
	template<
	typename Core = Initialize::InitializeCore
	>
	requires
	std::derived_from<Core, Initialize::InitializeCore>
	class DirectXInitializer final : HandyItems::others::NonCopyableMovableBase 
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXInitializer() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXInitializer() = default;

		/* ===== 初期化関数 ===== */

		/// <summary>
		/// DirectX初期化フロー呼び出し関数
		/// </summary>
		/// <param name="context">DirectXオブジェクトインスタンスまとめクラス参照</param>
		/// <param name="share">アプリケーションデータシェアクラス参照</param>
		/// <param name="hwnd">ウィンドウハンドル</param>
		/// <param name="width">ウィンドウの横幅</param>
		/// <param name="height">ウィンドウの縦幅</param>
		/// <param name="back_buffer_size">描画バッファリングサイズ</param>
		/// <param name="frame_resource_size">リソースバッファリングサイズ</param>
		/// <returns>初期化の成否</returns>
		[[nodiscard]] bool initialize(
			desc::InitializeDesc& desc
		) {

			//	コア機能初期化

			Core core{};
			auto hr = core.initialize_core(
				desc.context_,
				desc.back_buffer_size,
				desc.core_
			);
			if (FAILED(hr)) {

				InitializeLog::hresult_error_log(hr);
				return false;
			}

			//Initialize::InitializePass pass{};
			//pass_list = pass.initialize_pass(
			//	desc.context_,
			//	desc.pass_
			//);

			return true;
		}

		std::vector<std::string> pass_list{};

	};

}