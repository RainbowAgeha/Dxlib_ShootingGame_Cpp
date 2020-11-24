#include "GameObject.h"

GameObject::GameObject(int _layer)
{
	//�I�u�W�F�N�g����������͂��ׂď��������s��
	pos = VECTOR{ 0,0,0 };
	scale = VECTOR{ 1,1,1 };
	angle = 0;
	RectW = 1;
	RectH = 1;		//�����l�͂P
	hp = 0;
	id = -1;		//�����l��-1
	parent = NULL;
	strcpy(name, "");
	hitRect.center = pos;		//�I�u�W�F�N�g�̒��S
	hitRect.ImgPos = pos;		//�摜�̕\���ʒu
	hitRect.whd = VECTOR{ 1,1,1 };
	this->layer = _layer;
	this->isDead = false;		//�����Ă���

	//���ꂽ�u�ԂɊǗ��N���X�ɓo�^����
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

//---------------���X�g�Ǘ����s���֐�-------------
GameObjectList::GameObjectList() {}
GameObjectList::~GameObjectList() {}

void GameObjectList::add(GameObject* obj)
{
	//���X�g�̍Ō�ɃI�u�W�F�N�g��ǉ�
	golist[obj->getLayer()].push_back(obj);
}

void GameObjectList::remove(GameObject* obj)
{
	golist[obj->getLayer()].remove(obj);
}

void GameObjectList::moveAll()
{
	//�o�^����Ă���I�u�W�F�N�g�̍X�V����
	for (int i = 0; i < MAX_LAYER; i++) {
		//���X�g�̍ŏ�����Ō�܂�
		for(objList::iterator itr = golist[i].begin() ;
			itr != golist[i].end(); itr++){
			//����ł���i���ɂ����Ă���j�Ȃ珈�����Ȃ�
			if ( (*itr)->isDead )continue;
			(*itr)->move();
		}
	}
	//�X�V��A���ɂ������Ă���I�u�W�F�N�g���������č폜����
	for (int i = 0; i < MAX_LAYER; i++) {
		//���X�g�̍ŏ�����Ō�܂�
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end();){
			objList::iterator obj = itr++;
			//����ł���i���ɂ����Ă���j�Ȃ珈�����Ȃ�
			if ((*obj)->isDead) {
				delete* obj;
			}
		}
	}
}

void GameObjectList::renderAll()
{
	//�����Ă���I�u�W�F�N�g���������A�`�悷��
	for (int i = 0; i < MAX_LAYER; i++) {
		//���X�g�̍ŏ�����Ō�܂�
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end(); itr++) {
			//����ł���i���ɂ����Ă���j�Ȃ珈�����Ȃ�
			if ((*itr)->isDead)continue;
			(*itr)->render();
		}
	}
}

void GameObjectList::destruct()
{
	for (int i = 0; i < MAX_LAYER; i++) {
		//���X�g�̍ŏ�����Ō�܂�
		for (objList::iterator itr = golist[i].begin();
			itr != golist[i].end();) {
			objList::iterator obj = itr++;
			//����ł���i���ɂ����Ă���j�Ȃ珈�����Ȃ�
			delete* obj;
		}
		//���X�g���̂��̂��폜
		golist[i].clear();
	}
}

bool GameObjectList::colliderCheckAABB(GameObject* obj, int layer, int id)
{
	//���X�g�̍ŏ�����Ō�܂�
	for (objList::iterator itr = golist[layer].begin();
		itr != golist[layer].end(); itr++) {
		//�����蔻��̃I�u�W�F�N�g���g�����ɂ����Ȃ珈�����Ȃ�
		if (obj->isDead)break;
		//�������g�Ƃ͓�����Ȃ�
		if (*itr == obj)continue;
		//���肪���ɂ����ȏꍇ�͏��O
		if ((*itr)->isDead)continue;
		//�����܂ł�����ǂ���������Ă���̂ŁA�����蔻����s��
		if (checkAABB((*itr)->getHitRect(), obj->getHitRect())) {
			obj->hit(*itr, id);
			(*itr)->hit(obj, id);
			//������������`����
			return true;
		}
	}
	//������Ȃ�����
	return false;
}

bool GameObjectList::colliderCheckAABB_2D(GameObject* obj, int layer, int id)
{
	//���X�g�̍ŏ�����Ō�܂�
	for (objList::iterator itr = golist[layer].begin();
		itr != golist[layer].end(); itr++) {
		//�����蔻��̃I�u�W�F�N�g���g�����ɂ����Ȃ珈�����Ȃ�
		if (obj->isDead)break;
		//�������g�Ƃ͓�����Ȃ�
		if (*itr == obj)continue;
		//���肪���ɂ����ȏꍇ�͏��O
		if ((*itr)->isDead)continue;
		//�����܂ł�����ǂ���������Ă���̂ŁA�����蔻����s��
		if (checkAABB_2D((*itr)->getHitRect(), obj->getHitRect())) {
			obj->hit(*itr, id);
			(*itr)->hit(obj, id);
			//������������`����
			return true;
		}
	}
	//������Ȃ�����
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
	//���̂U�ɓ��Ă͂܂�Ȃ��̂ł���΂������Ă���
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
	
	//����4�ɓ��Ă͂܂�Ȃ��̂ł���΂������Ă���
	return true;
}
