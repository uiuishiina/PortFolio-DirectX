#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Debug/DebugLogSystem.h"

//	DirectX
#include"../DirectXContext.h"
#include"../Helpers/MeshResourceDesc.h"

#include"../Container/DrawObjectConteiner.h"

//	その他
#include<vector>
#include<utility>
#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			struct ResourceDesc {

				/* ========== Publicメンバー変数 ========== */

				std::vector<Resource::DrawObject::Mesh::MeshResourceDesc> mesh_desc{};


				/* ========== Publicメンバー関数 ========== */

				void emplace_mesh_desc(
					std::string name,
					std::unique_ptr<Resource::DrawObject::Mesh::MeshCreateDescBase> desc
				) {

					mesh_desc.emplace_back(
						std::make_tuple(
							std::move(name), 
							std::move(desc)
						));
				}
				void emplace_mesh_desc(
					Resource::DrawObject::Mesh::MeshResourceDesc desc
				) {

					mesh_desc.emplace_back(std::move(desc));
				}

			};
		}

		class InitializeResource
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			[[nodiscard]] static HRESULT initialize_resource(
				DirectXContext* context_,
				const desc::ResourceDesc& desc
			) {

				//	コマンドアロケーター取得
				auto allocator = context_->frame_resources[2]->get_allocator();

				//	コマンドアロケータリセット
				allocator->reset_allocator();

				//	コマンドリストリセット
				context_->graphic_list->reset_list(allocator->get());


				/*
					もはやUpdater::Update()の中で
					パスコマンドを流用して、リソース作成コマンドを作ってもいいかもしれない。
				*/

				auto* upload = context_->frame_resources[0]->get_upload_resources();

				upload->add_upload(desc.mesh_desc.size() * 2);

				for (auto& [name, mesh_desc] : desc.mesh_desc) {

					auto ref_vec = upload->allocate_references(2);

					//	作成
					auto mesh = mesh_desc->make_mesh_object(
						context_->device_->get(),
						context_->graphic_list->get(),
						ref_vec
					);
					if (mesh) {

						//	登録
						if (!context_->draw_object_container->add_draw_object(
							Container::DrawObjectKey{ name.c_str() },
							std::move(mesh)
						)) {
							DEBUG_ERROR_LOG(
								"add_draw_object = false",
								"name = ", name
							);
							return E_FAIL;
						}

					}
					else {
						DEBUG_ERROR_LOG(
							"make_mesh_object = false",
							"name = ", name
						);
						return E_FAIL;
					}
				}


				//	コマンドリストをクローズ
				context_->graphic_list->get()->Close();

				//	コマンドキューにコマンドリストを送信
				ID3D12CommandList* ppCommandLists[] = { context_->graphic_list->get() };
				context_->graphic_queue->get()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

				//	シグナルを送って配列に保存
				context_->frame_resources[2]->end_frame_signal(context_->graphic_queue->get());

				const auto wait = context_->frame_resources[2]->get_frame_value();

				//	使えるまで待機
				context_->fence_->wait_to_completed_value(wait);

				return S_OK;
			}


		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializeResource() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializeResource() = default;

		};
	}
}