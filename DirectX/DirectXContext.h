#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/UniquePtr.h"

//	DirectX
#include<d3d12.h>

//	その他
#include<vector>
#include<optional>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	namespace ClassObject {
		class DXGI;
		class Device;
		class CommandQueue;
		class CommandList;
		class Fence;
		class SwapChain;
		class DescriptorHeap;
		class BackBuffer;
	}

	namespace ClassModule {
		class FrameResource;
	}

	/// <summary>
	/// DirectXオブジェクトインスタンス構造体
	/// </summary>
	class DirectXContext final : HandyItems::others::NonCopyableMovableBase
	{

		template<typename T>
		using UniquePtr = HandyItems::others::UniquePtr<T>;

		template<typename T>
		using WeakPtr = HandyItems::others::UniqueWeakPtr<T>;

	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXContext();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXContext();

		/* ===== 取得関数 ===== */

		[[nodiscard]] WeakPtr<ClassObject::DXGI> get_dxgi() const noexcept {

			return HandyItems::others::make_unique_weak(dxgi_);
		}

		[[nodiscard]] WeakPtr<ClassObject::Device> get_device() const noexcept {

			return HandyItems::others::make_unique_weak(device_);
		}

		[[nodiscard]] WeakPtr<ClassObject::CommandQueue> get_queue() const noexcept {

			return HandyItems::others::make_unique_weak(graphic_queue);
		}

		[[nodiscard]] WeakPtr<ClassObject::CommandList> get_list() const noexcept {

			return HandyItems::others::make_unique_weak(graphic_list);
		}

		[[nodiscard]] WeakPtr<ClassObject::Fence> get_fence() const noexcept {

			return HandyItems::others::make_unique_weak(fence_);
		}

		[[nodiscard]] std::optional<WeakPtr<ClassModule::FrameResource>> get_frame_resource(
			std::size_t index
		) const noexcept {

			if (frame_resources.size() <= index) {
				return std::nullopt;
			}

			return HandyItems::others::make_unique_weak(frame_resources[index]);
		}

		[[nodiscard]] std::vector<WeakPtr<ClassModule::FrameResource>> get_frame_resources() const noexcept {

			std::vector<WeakPtr<ClassModule::FrameResource>> array_{};

			for (auto& resource : frame_resources) {
				array_.push_back(HandyItems::others::make_unique_weak(resource));
			}

			return array_;
		}

		[[nodiscard]] WeakPtr<ClassObject::SwapChain> get_swapchain() const noexcept {

			return HandyItems::others::make_unique_weak(swapchain_);
		}

		[[nodiscard]] WeakPtr<ClassObject::DescriptorHeap> get_heap() const noexcept {

			return HandyItems::others::make_unique_weak(heap_);
		}

		[[nodiscard]] std::optional<WeakPtr<ClassObject::BackBuffer>> get_back_buffer(
			std::size_t index
		) const noexcept {

			if (back_buffers.size() <= index) {
				return std::nullopt;
			}
			return HandyItems::others::make_unique_weak(back_buffers[index]);
		}

		[[nodiscard]] std::vector<WeakPtr<ClassObject::BackBuffer>> get_back_buffers() const noexcept {

			std::vector<WeakPtr<ClassObject::BackBuffer>> array_{};

			for (auto& buffer : back_buffers) {
				array_.push_back(HandyItems::others::make_unique_weak(buffer));
			}

			return array_;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/* -- 設定 -- */

		const UINT back_buffer_size = 2;
		const UINT frame_resource_size = 3;

		/* -- Core -- */

		/// <summary>
		/// DXGIインスタンス
		/// </summary>
		UniquePtr<ClassObject::DXGI> dxgi_{};

		/// <summary>
		/// Deviceインスタンス
		/// </summary>
		UniquePtr<ClassObject::Device> device_{};

		/// <summary>
		/// 描画用コマンドキューインスタンス
		/// </summary>
		UniquePtr<ClassObject::CommandQueue> graphic_queue{};

		/// <summary>
		/// 描画用コマンドリストインスタンス
		/// </summary>
		UniquePtr<ClassObject::CommandList> graphic_list{};

		/// <summary>
		/// フェンスインスタンス
		/// </summary>
		UniquePtr<ClassObject::Fence> fence_{};

		/// <summary>
		/// フレームリソースインスタンス配列
		/// </summary>
		std::vector<UniquePtr<ClassModule::FrameResource>> frame_resources{};

		/// <summary>
		/// スワップチェーンインスタンス
		/// </summary>
		UniquePtr<ClassObject::SwapChain> swapchain_{};

		/// <summary>
		/// ディスクリプタヒープインスタンス
		/// </summary>
		UniquePtr<ClassObject::DescriptorHeap> heap_{};
		
		/// <summary>
		/// バックバッファインスタンス配列
		/// </summary>
		std::vector< UniquePtr<ClassObject::BackBuffer>> back_buffers{};

	};
}