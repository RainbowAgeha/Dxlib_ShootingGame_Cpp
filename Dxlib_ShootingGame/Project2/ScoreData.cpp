#include "GameMain.h"
#include "ScoreData.h"

//�t�@�C���t�H���_���Ăяo���֐�
#include <direct.h>
#include <sys/stat.h>

//�i�[����X�R�A�f�[�^��10�܂�
int ScoreData[FILEDATA_NUM];

int ScoreSave(char* SaveDataPass)
{
	//�Z�[�u�f�[�^�p�̃t�H���_���쐬����
	const char* file = "res\\SaveData";
	struct stat statBuf;

	//SaveData�t�H���_�����邩�m�F����
	if (stat(file, &statBuf) == 0) {
		//�������Ȃ炻���ɃZ�[�u�����
		//fopen:�t�@�C�����J��("w"�������݃��[�h)
		FILE* fp = fopen(SaveDataPass, "w");
		//fwrite:�t�@�C���̏������݂����s
		//����:�������݂����ϐ��A�������ރT�C�Y�A�������ތ��A�t�@�C���ϐ�
		fwrite(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
		//�t�@�C�������
		fclose(fp);
	}else {
		//�Ȃ������̂Ńt�H���_�����B
		if (_mkdir(file) == 0) {
			//fopen:�t�@�C�����J��("w"�������݃��[�h)
			FILE* fp = fopen(SaveDataPass, "w");
			//fwrite:�t�@�C���̏������݂����s
			//����:�������݂����ϐ��A�������ރT�C�Y�A�������ތ��A�t�@�C���ϐ�
			fwrite(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
			//�t�@�C�������
			fclose(fp);
		}
		else {
			//�������O�̃t�H���_���L����ۂ��ł���
		}
	}

    return 0;
}

int ScoreLoad(char* SaveDataPass)
{
	//fopen:�t�@�C�����J��("r"�ǂݍ��݃��[�h)
	FILE* fp;
	//�t�@�C�����L�邩�e�X�g���s���A�Ȃ������狭���I�ɍ��B
	if (fopen(SaveDataPass, "r") == NULL) {
		ScoreSave(SaveDataPass);
	}
	//�����t�@�C�����������̂ŁA���[�h�����s����
	fp = fopen(SaveDataPass, "r");

	//fread:�t�@�C���̓ǂݍ��݂����s
	//����:�ǂݍ��݂����ϐ��A�ǂݍ��݃T�C�Y�A�ǂݍ��݌��A�t�@�C���ϐ�
	fread(&ScoreData, sizeof(int), FILEDATA_NUM, fp);
	//�t�@�C�������
	fclose(fp);
    return 0;
}

void ScoreInit()
{
	for (int i = 0; i < FILEDATA_NUM; i++) {
		ScoreData[i] = 0;
	}
}
