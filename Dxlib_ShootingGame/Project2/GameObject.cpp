#include "GameObject.h"

GameObject::GameObject(int _layer)
{
	//オブジェクトを作った時はすべて初期化を行う
	pos = VECTOR{ 0,0,0 };
	scale = VECTOR{ 1,1,1 };
	angle = 0;
	RectW = 1;
	RectH = 1;		//初期値は１
	hp = 0;
	id = -1;		//初期値は-1
	parent = NULL;
	strcpy(name, "");
	hitRect.center = pos;		//オブジェクトの中心
	hitRect.ImgPos = pos;		//画像の表示位置
	hitRect.whd = VECTOR{ 1,1,1 };
	this->layer = _layer;
	this->isDead = false;		//生きている

	//作られた瞬間に管理クラスに登録する
	GameObjectList::instance()->add(this);

}

GameObject::~GameObject()
{
	GameObjectList::instance()->remove(this);
}

void GameObject::move()
{
}

void GameObject::render()
{
}

void GameObject::hit(GameObject* obj, int collideID)
{
}

bool GameObject::colliderCheckAABB(int layer, int id) {
	return GameObjectList::instance()->colliderCheckAABB(this,layer,id);
}
bool GameObject::colliderCheckAABB_2D(int layer, int id) {
	return GameObjectList::instance()->colliderCheckAABB_2D(this, layer, id);
}

//---------------リスト管理を行う関数-------------
GameObjectList::GameObjectList() {}
GameObjectList::~GameObjectList() {}

void GameObjectList::add(GameObject* obj)
{
	//リストの最後にオブジェクトを追加
	golist[obj->getLayer()].push_back(obj);
}

void GameObjectList::remove(GameObject* obj)
{
	golist[obj->getLayer()].remove(obj);
}

void GameObjectList::moveAll()
{
	//登録されているオブジェクトの更新処理
	for (int i = 0; i < MAX_LAYER; i++) {
		//リストの最初から最後まで
		for(objList::iterator itr = golist[i].begin() ;
			itr != golist[i].end(); itr++){
			//死んでいる（死にかけている）なら処理しない
			if ( (*itr)->isDead )continue;
			(*itr)->move();
		}
	}
	//更新後、死にたがっているオブジェクトを検索して削除する
	for (int i = 0; i < MAX_LAYER; i++) {
		//リストの最初から最後まで
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end();){
			objList::iterator obj = itr++;
			//死んでいる（死にかけている）なら処理しない
			if ((*obj)->isDead) {
				delete* obj;
			}
		}
	}
}

void GameObjectList::renderAll()
{
	//生きているオブジェクトを検索し、描画する
	for (int i = 0; i < MAX_LAYER; i++) {
		//リストの最初から最後まで
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end(); itr++) {
			//死んでいる（死にかけている）なら処理しない
			if ((*itr)->isDead)continue;
			(*itr)->render();
		}
	}
}

void GameObjectList::destruct()
{
	for (int i = 0; i < MAX_LAYER; i++) {
		//リストの最初から最後まで
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end();) {
			objList::iterator obj = itr++;
			//死んでいる（死にかけている）なら処理しない
			delete* obj;
		}
		//リストそのものを削除
		golist[i].clear();
	}
}

bool GameObjectList::colliderCheckAABB(GameObject* obj, int layer, int id)
{
	//リストの最初から最後まで
	for (objList::iterator itr = golist[layer].begin();
		itr != golist[layer].end(); itr++) {
		//当たり判定のオブジェクト自身が死にそうなら処理しない
		if (obj->isDead)break;
		//自分自身とは当たらない
		if (*itr == obj)continue;
		//相手が死にそうな場合は除外
		if ((*itr)->isDead)continue;
		//ここまできたらどちらも生きているので、当たり判定を行う
		if (checkAABB((*itr)->getHitRect(), obj->getHitRect())) {
			obj->hit(*itr, id);
			(*itr)->hit(obj, id);
			//当たった事を伝える
			return true;
		}
	}
	//当たらなかった
	return false;
}

bool GameObjectList::colliderCheckAABB_2D(GameObject* obj, int layer, int id)
{
	//リストの最初から最後まで
	for (objList::iterator itr = golist[layer].begin();
		itr != golist[layer].end(); itr++) {
		//当たり判定のオブジェクト自身が死にそうなら処理しない
		if (obj->isDead)break;
		//自分自身とは当たらない
		if (*itr == obj)continue;
		//相手が死にそうな場合は除外
		if ((*itr)->isDead)continue;
		//ここまできたらどちらも生きているので、当たり判定を行う
		if (checkAABB_2D((*itr)->getHitRect(), obj->getHitRect())) {
			obj->hit(*itr, id);
			(*itr)->hit(obj, id);
			//当たった事を伝える
			return true;
		}
	}
	//当たらなかった
	return false;
}

bool checkAABB(HIT_AABB* a, HIT_AABB* b)
{
	if (a->center.x - a->whd.x > b->center.x + b->whd.x)return false;
	if (a->center.x + a->whd.x < b->center.x - b->whd.x)return false;
	if (a->center.y - a->whd.y > b->center.y + b->whd.y)return false;
	if (a->center.y + a->whd.y < b->center.y - b->whd.y)return false;
	if (a->center.z - a->whd.z > b->center.z + b->whd.z)return false;
	if (a->center.z + a->whd.z < b->center.z - b->whd.z)return false;
	//この６つに当てはまらないのであればあたっている
	return true;
}
bool checkAABB_2D(HIT_AABB* a, HIT_AABB* b)
{
	if (a->ImgPos.x > b->ImgPos.x + b->whd.x)return false;
	if (a->ImgPos.x + a->whd.x < b->ImgPos.x )return false;
	if (a->ImgPos.y  > b->ImgPos.y + b->whd.y)return false;
	if (a->ImgPos.y + a->whd.y < b->ImgPos.y)return false;
	//if (a->center.z - a->whd.z > b->center.z + b->whd.z)return false;
	//if (a->center.z + a->whd.z < b->center.z - b->whd.z)return false;
	
	//この4つに当てはまらないのであればあたっている
	return true;
}
