#include "GameMain.h"
#include "ScoreData.h"

//ファイルフォルダを呼び出す関数
#include <direct.h>
#include <sys/stat.h>

//格納するスコアデータは10個まで
int ScoreData[FILEDATA_NUM];

int ScoreSave(char* SaveDataPass)
{
	//セーブデータ用のフォルダを作成する
	const char* file = "res\\SaveData";
	struct stat statBuf;

	//SaveDataフォルダがあるか確認する
	if (stat(file, &statBuf) == 0) {
		//あったならそこにセーブを作る
		//fopen:ファイルを開く("w"書き込みモード)
		FILE* fp = fopen(SaveDataPass, "w");
		//fwrite:ファイルの書き込みを実行
		//引数:書き込みたい変数、書き込むサイズ、書き込む個数、ファイル変数
		fwrite(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
		//ファイルを閉じる
		fclose(fp);
	}else {
		//なかったのでフォルダを作る。
		if (_mkdir(file) == 0) {
			//fopen:ファイルを開く("w"書き込みモード)
			FILE* fp = fopen(SaveDataPass, "w");
			//fwrite:ファイルの書き込みを実行
			//引数:書き込みたい変数、書き込むサイズ、書き込む個数、ファイル変数
			fwrite(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
			//ファイルを閉じる
			fclose(fp);
		}
		else {
			//同じ名前のフォルダが有るっぽいですよ
		}
	}

    return 0;
}

int ScoreLoad(char* SaveDataPass)
{
	//fopen:ファイルを開く("r"読み込みモード)
	FILE* fp;
	//ファイルが有るかテストを行い、なかったら強制的に作る。
	if (fopen(SaveDataPass, "r") == NULL) {
		ScoreSave(SaveDataPass);
	}
	//無事ファイルが合ったので、ロードを実行する
	fp = fopen(SaveDataPass, "r");

	//fread:ファイルの読み込みを実行
	//引数:読み込みたい変数、読み込みサイズ、読み込み個数、ファイル変数
	fread(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
	//ファイルを閉じる
	fclose(fp);
    return 0;
}

void ScoreInit()
{
	for (int i = 0; i < FILEDATA_NUM; i++) {
		ScoreData[i] = 0;
	}
}
