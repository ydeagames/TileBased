#include "SceneManager.h"
#include "Scene.h"

// <SceneManagerクラス>

SceneManager::SceneManager()
{
	m_active_scene = nullptr;
	m_next_scene_id = SceneID::NONE;
}

// <シーンの追加>
// scene_id       登録するシーンのID
// factory_method 登録するシーンの生成用関数
void SceneManager::AddScene(SceneID scene_id, FactoryMethod factory_method)
{
	//assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(factory_method && "生成用関数が指定されていません。");

	m_scene_factory_methods[scene_id] = factory_method;
}

// <開始シーンの設定>
// scene_id 開始シーンのID
void SceneManager::SetStartScene(SceneID scene_id)
{
	//assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	ChangeScene(scene_id);
}

// <活動中のシーンの更新>
void SceneManager::UpdateActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");

	// シーンの変更（要求があった場合)
	if (m_next_scene_id != SceneID::NONE)
	{
		ChangeScene(m_next_scene_id);
		m_next_scene_id = SceneID::NONE;
	}

	// 追加キューのオブジェクトを追加
	while (!addingObjects.empty()) {
		auto& node = addingObjects.front();
		m_active_scene->tags.insert(std::make_pair(node->tag, node));
		m_active_scene->layers[node->layer].push_back(node);
		m_active_scene->objects.emplace(node->name, node);
		addingObjects.pop();
	}

	// 活動中のシーンの更新
	m_active_scene->Update();
}

// <活動中のシーンの描画>
void SceneManager::RenderActiveScene()
{
	assert(m_active_scene && "活動中のシーンがありません。");

	// 活動中のシーンの描画
	m_active_scene->Render();
}

// <シーン変更の要求>
//    ※実際にはUpdate時に変更される
// scene_id 変更を要求するシーンのID
void SceneManager::RequestScene(SceneID scene_id)
{
	//assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");

	m_next_scene_id = scene_id;
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return m_active_scene;
}

void SceneManager::AddObject(const std::shared_ptr<GameObject>& object)
{
	addingObjects.push(object);
}

// <シーン変更>
// scene_id 変更したいシーンのID
void SceneManager::ChangeScene(SceneID scene_id)
{
	//assert(scene_id >= 0 && scene_id < NUM_SCENES && "シーンIDが不正です。");
	assert(m_scene_factory_methods[scene_id] && "生成用関数が登録されていません。");

	// 活動中のシーンの削除
	if (m_active_scene != nullptr)
	{
		m_active_scene = nullptr;
	}

	// 新しいシーンの生成
	m_active_scene = m_scene_factory_methods[scene_id]();
}
