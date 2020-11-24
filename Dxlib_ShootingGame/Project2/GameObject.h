#pragma once
#pragma warning(disable:4996)	//strcpy�𖳎�
#include "GameMain.h"
#include "ColliderID.h"
#include <list>

//��]�Ƃ��Ɏg�����
#define PI    3.1415926535897932384626433832795f

//�I�u�W�F�N�g���ȈՓI�ɉ񂷏���for_each
#define forEach(castName,layer) for(castName* ptr = static_cast<castName*>(GameObjectList::instance()->start(layer)) ;ptr != NULL; ptr = static_cast<castName*>(GameObjectList::instance()->next()))

//���C���[�̒萔
enum OBJECT_LIST {
	PLAYER_LAYER,
	ENEMY_LAYER,
	SHOT_LAYER,
	ENEMYSHOT_LAYER,		//�G�p�̒e�H
	EFFECT_LAYER,
	ITEM_LAYER,

	MAX_LAYER
};

//�����蔻��̐ݒ�
struct HIT_AABB {
	VECTOR center; //���S�̍��W
	VECTOR ImgPos;	//2D�Ō��_(�摜����)
	VECTOR whd;		//�����A�c���A���s��
};

bool checkAABB(HIT_AABB* a , HIT_AABB* b);
bool checkAABB_2D(HIT_AABB* a, HIT_AABB* b);

class GameObject
{
private:

public:
	VECTOR pos, scale;	//�ʒu�A�傫���A�p�x
	float angle;		//�p�x
	float RectW, RectH;			//�摜�̉����A�c��
	bool isDead;		//�����Ă���H
	int hp;				//�F�X�g����HP
	char id;
	char name[8];

	GameObject* parent;	//���̃I�u�W�F�N�g�̊Ǘ���
	
protected:
	int layer;	//�I�u�W�F�N�g�̊Ǘ�����(�K�w)

	HIT_AABB hitRect;	//�����蔻��̗̈�

public:
	//�Ăяo���֐���`
	GameObject(int _layer = 0);	//�R���X�g���N�^
	virtual ~GameObject();	//�f�X�g���N�^

	virtual void move() = 0;
	virtual void render() = 0;
	virtual void hit(GameObject* obj, int collideID) = 0;

	//�������̎擾
	GameObject* getParent() {
		return parent;
	}
	//�I�u�W�F�N�g���C���[�̌Ăяo��
	int getLayer() {
		return layer;
	}

	//�����蔻����擾
	HIT_AABB* getHitRect() {
		return &hitRect;
	}

	//AABB�̓����蔻������B
	bool colliderCheckAABB(int layer, int id);
	//AABB�̓����蔻������(2D��)
	bool colliderCheckAABB_2D(int layer, int id);
};

class GameObjectList {
private:
	GameObjectList();
	~GameObjectList();
	//���X�g�̐錾
	typedef std::list<GameObject*> objList;
	objList golist[MAX_LAYER];
public:
	void add(GameObject* obj);
	void remove(GameObject* obj);

	//�X�V����
	void moveAll();		//�X�V����
	void renderAll();		//�`�揈��

	//�I�u�W�F�N�g�����ׂč폜����
	void destruct();

	//�I�u�W�F�N�g�œo�^���ꂽ���ׂĂƓ����蔻��
	bool colliderCheckAABB(GameObject* obj, int layer, int id);
	//�I�u�W�F�N�g�œo�^���ꂽ���ׂĂƓ����蔻��
	bool colliderCheckAABB_2D(GameObject* obj, int layer, int id);

	//�I�u�W�F�N�g���X�g�̌����A�����ʒu
	objList::iterator p, end;
	GameObject* start(int layer){
		p = golist[layer].begin();
		end = golist[layer].end();
		if (p == end)return NULL; //���̃��C���[�͓o�^�Ȃ�
		return *p;
	}

	//�I�u�W�F�N�g�̎����Q��
	GameObject* next() {
		p++;
		if (p == end)return NULL;	//���̃I�u�W�F�N�g�͂����Ȃ���
		return *p;
	}

	//�I�u�W�F�N�g�̐����擾
	size_t getObjectNum(int layer) {
		return golist[layer].size();
	}

	//�Ăяo���͏�ɂP�݂̂Ƃ���ׁA�V���O���g����
	static GameObjectList* instance() {
		static GameObjectList list;
		return &list;
	}
};



