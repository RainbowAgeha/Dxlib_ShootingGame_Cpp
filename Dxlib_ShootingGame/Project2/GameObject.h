#pragma once
#pragma warning(disable:4996)	//strcpyを無視
#include "GameMain.h"
#include "ColliderID.h"
#include <list>

//回転とかに使うやつ
#define PI    3.1415926535897932384626433832795f

//オブジェクトを簡易的に回す処理for_each
#define forEach(castName,layer) for(castName* ptr = static_cast<castName*>(GameObjectList::instance()->start(layer)) ;ptr != NULL; ptr = static_cast<castName*>(GameObjectList::instance()->next()))

//レイヤーの定数
enum OBJECT_LIST {
	PLAYER_LAYER,
	ENEMY_LAYER,
	SHOT_LAYER,
	ENEMYSHOT_LAYER,		//敵用の弾？
	EFFECT_LAYER,
	ITEM_LAYER,

	MAX_LAYER
};

//当たり判定の設定
struct HIT_AABB {
	VECTOR center; //中心の座標
	VECTOR ImgPos;	//2D版原点(画像左上)
	VECTOR whd;		//横幅、縦幅、奥行き
};

bool checkAABB(HIT_AABB* a , HIT_AABB* b);
bool checkAABB_2D(HIT_AABB* a, HIT_AABB* b);

class GameObject
{
private:

public:
	VECTOR pos, scale;	//位置、大きさ、角度
	float angle;		//角度
	float RectW, RectH;			//画像の横幅、縦幅
	bool isDead;		//生きている？
	int hp;				//色々使えるHP
	char id;
	char name[8];

	GameObject* parent;	//このオブジェクトの管理者
	
protected:
	int layer;	//オブジェクトの管理名簿(階層)

	HIT_AABB hitRect;	//当たり判定の領域

public:
	//呼び出す関数定義
	GameObject(int _layer = 0);	//コンストラクタ
	virtual ~GameObject();	//デストラクタ

	virtual void move() = 0;
	virtual void render() = 0;
	virtual void hit(GameObject* obj, int collideID) = 0;

	//生成元の取得
	GameObject* getParent() {
		return parent;
	}
	//オブジェクトレイヤーの呼び出し
	int getLayer() {
		return layer;
	}

	//当たり判定を取得
	HIT_AABB* getHitRect() {
		return &hitRect;
	}

	//AABBの当たり判定を作る。
	bool colliderCheckAABB(int layer, int id);
	//AABBの当たり判定を作る(2D版)
	bool colliderCheckAABB_2D(int layer, int id);
};

class GameObjectList {
private:
	GameObjectList();
	~GameObjectList();
	//リストの宣言
	typedef std::list<GameObject*> objList;
	objList golist[MAX_LAYER];
public:
	void add(GameObject* obj);
	void remove(GameObject* obj);

	//更新処理
	void moveAll();		//更新処理
	void renderAll();		//描画処理

	//オブジェクトをすべて削除する
	void destruct();

	//オブジェクトで登録されたすべてと当たり判定
	bool colliderCheckAABB(GameObject* obj, int layer, int id);
	//オブジェクトで登録されたすべてと当たり判定
	bool colliderCheckAABB_2D(GameObject* obj, int layer, int id);

	//オブジェクトリストの検索、初期位置
	objList::iterator p, end;
	GameObject* start(int layer){
		p = golist[layer].begin();
		end = golist[layer].end();
		if (p == end)return NULL; //このレイヤーは登録なし
		return *p;
	}

	//オブジェクトの次を参照
	GameObject* next() {
		p++;
		if (p == end)return NULL;	//次のオブジェクトはもうないよ
		return *p;
	}

	//オブジェクトの数を取得
	size_t getObjectNum(int layer) {
		return golist[layer].size();
	}

	//呼び出しは常に１つのみとする為、シングルトン化
	static GameObjectList* instance() {
		static GameObjectList list;
		return &list;
	}
};



