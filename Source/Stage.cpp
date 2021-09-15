#include"Stage.h"

//行列更新
void Stage::UpdateTransform()
{
	//スケール行列を作成
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//回転行列を作成
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3つの行列を組み合わせ、ワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;

	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}

//コンストラクタ
Stage::Stage()
{
	//ステージモデルを読み込み
	model = new Model("Data/Model/Stage/Stage2.mdl");
	//model = new Model("Data/Model/ExampleStage/ExampleStage.mdl");

	position.y = -2*3;
	position.z = 57.5;
	position.x = -0.8*3;
	angle.y = 1.5708;
	scale.x = scale.y = scale.z = 0.3;
}

//デストラクタ
Stage::~Stage()
{
	//ステージモデルを破棄
	delete model;
}

//更新処理
void Stage::Update(float elapsedTime)
{
	//今は特にやることがない
	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);
}

//描画処理
void Stage::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	//シェーダーにモデルを描画してもらう
	shader->Draw(dc, model);
}