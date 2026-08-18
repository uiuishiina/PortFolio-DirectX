#include"Mesh.h"
#include"../AddFile/d3dx12.h"

using namespace render::dx12::drawobject;

///====================================================================
/// 実行時処理関数
///====================================================================

//@breif	=== ポリゴン描画関数 ===
//@param	list	描画用コマンドリスト参照
void Mesh::draw(ID3D12GraphicsCommandList* list) const noexcept {

	list->IASetVertexBuffers(0, 1, vertex_buffer->get_buffer_view());

	list->IASetIndexBuffer(index_buffer->get_buffer_view());
	//	プリミティブトポロジーを設定
	list->IASetPrimitiveTopology(topology_);
	//	インデックスバッファを使用して三角形を描画
	list->DrawIndexedInstanced(index_size, 1, 0, 0, 0);
}
