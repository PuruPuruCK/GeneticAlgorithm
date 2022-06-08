#include<iostream>
#include<random>
using namespace std;

double weight[50] =  //�i���̏d��
{
9, //1
7, //2
8, //3
2, //4
10, //5
7, //6
7, //7
8, //8
5, //9
4, //10
7, //11
5, //12
7, //13
5, //14
9, //15
9, //16
9, //17
8, //18
8, //19
2, //20
7, //21
7, //22
9, //23
8, //24
4, //25
7, //26
3, //27
9, //28
7,   //29
7,   //30
9, //31
5, //32
10, //33
7, //34
10, //35
10, //36
7, //37
10, //38
10, //39
10, //40
3, //41
8, //42
3, //43
4, //44
2, //45
2, //46
5, //47
3, //48
9,   //49
2   //50
};

double prise[50] = //�i���̒l�i
{
20, //1
28, //2
2, //3
28, //4
15, //5
28, //6
21, //7
7, //8
28, //9
12, //10
21, //11
4, //12
31, //13
28, //14
24, //15
36, //16
33, //17
2, //18
25, //19
21, //20
35, //21
14, //22
36, //23
25, //24
12, //25
14, //26
40, //27
36, //28
2,   //29
28,   //30
33, //31
40, //32
22, //33
2, //34
18, //35
22, //36
14, //37
22, //38
15, //39
22, //40
40, //41
7, //42
4, //43
21, //44
21, //45
28, //46
40, //47
4, //48
24,   //49
21   //50
};

const int MAXIMUM_WEIGHT = 60;
const double CROSS = 0.8;
const double MUTATION = 0.3;
const int GENERATION = 30000;
const int POPULATION = 50;

int main() {


	double pop[POPULATION][50] = { 0 };

	//�]��
	double evals[POPULATION] = { 0 };

	std::random_device rnd;

	//���Q�̐���
	for (int y = 0; y < POPULATION; y++) {
		int now_weight = 0;
		int now_eval = 0;

		for (int x = 0; x < POPULATION; x++) {
			//����
			if (rnd() % 2 == 0) {
				//�ق�Ƃɓ���Ă����̂��H
				if (now_weight + weight[x] > MAXIMUM_WEIGHT) {
					//�������̂œ���Ȃ��ł��̈�`�q�̓��[�v�I���
					continue;
				}
				//����Ă�OK�Ȃ̂œ����
				pop[y][x] = 1;
				//���ꂽ�̂�weight�̍X�V
				now_weight += weight[x];
				//�]���X�V
				now_eval += prise[x];

			}


			//�\��
			cout << pop[y][x] << ",";


		}
		//�S�̕]��
		evals[y] = now_eval;

		//�\��
		cout << "weight" << now_weight << "eval" << evals[y] << endl;
	}

	//���[���b�g�t�F�[�Y
	double* ratios = roulette(evals);

	//�e�̑I��(2��)
	//random���g���Đe��2�̑I��
	/*
	double rnd= random(0,1.0);
	double selectProb=0;
	for(int i=0;i<POPULATION;i++){
	//rnd���傫���Ȃ����炻����e�ɂ��� : �m���̕��ѕ��ł͕ς��Ȃ��͂�
		if(selectProb >= rnd) parent=i;
	}
	*/

	//����

	//�ˑR�ψ�

	//Accepting :�@�V�����q����V�����̌Q��

	//���[�v��֖߂�

}

double eval(double* pop) {
	double now_eval = 0;
	for (int i = 0; i < POPULATION; i++) {
		if (pop[i] == 1) now_eval += prise[i];
	}
	return now_eval;
}

double* roulette(double const evals[]) {
	double sum = 0;
	double ratios[50] = { 0 };

	//�S�̂̌v�Z
	for (int i = 0; i < POPULATION; i++) {
		sum += evals[i];
	}

	//���l�ɑ΂��銄���̌���
	for (int i = 0; i < POPULATION; i++) {
		ratios[i] = evals[i] / sum;
	}

	return ratios;
}
double selectParent() {
	
}