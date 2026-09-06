#include"Mesh.h"
#include"../AddFile/d3dx12.h"

using namespace render::dx12::drawobject;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 描画関数 -- */

/// <summary>
/// ポリゴン描画関数
/// </summary>
/// <param name="list">描画用コマンドリスト参照</param>
void Mesh::draw(ID3D12GraphicsCommandList* list) const noexcept {

	//	VertexBuffer設定
	list->IASetVertexBuffers(0, 1, vertex_buffer->get_buffer_view());

	//	IndexBuffer設定
	list->IASetIndexBuffer(index_buffer->get_buffer_view());

	//	プリミティブトポロジー設定
	list->IASetPrimitiveTopology(topology_);

	//	インデックスバッファを使用して描画
	list->DrawIndexedInstanced(index_size, 1, 0, 0, 0);
}