#pragma once
#include<d3d12.h>
#include<wrl/client.h>


class Fence final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	Fence() = default;
	~Fence() = default;

	//コピー禁止,ムーブ禁止
	Fence(const Fence&) = delete;
	Fence& operator=(const Fence&) = delete;
	Fence(Fence&&) = delete;
	Fence& operator=(Fence&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== フェンス作成関数 ===
	//@param	device	DirectX12 デバイス
	//@return	作成の成否
	[[nodiscard]] HRESULT create_fence(ID3D12Device* device);

	//@brief	コマンドキューにフェンスをシグナル
	//@param	command_queue	フェンスをシグナルするコマンドキュー
	[[nodiscard]] UINT64 signal(ID3D12CommandQueue* command_queue);

	//@brief	フェンス値の取得
	//@return	フェンス値
	[[nodiscard]] UINT64 get_completed_value() const noexcept;

	//@brief	=== フェンス取得関数 ===
	//@return	フェンスインスタンス
	[[nodiscard]] ID3D12Fence* get_fence()const noexcept;

private:
	///====================================================================
	/// メンバー変数
	///====================================================================

	//@brief	== フェンスインスタンス ==
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_{};

	//@brief	== フェンスイベント ==
	HANDLE wait_event{};

	//@brief	== フェンスの値 ==
	UINT64 fence_value{};
};