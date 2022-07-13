#include<iostream>
#include<random>
using namespace std;

double weight[50] =  //品物の重さ
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

double prise[50] = //品物の値段
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
const int MAXIMUM_GENOTYPE = 50;

void writeGenotypeEval(double (* genotype)[MAXIMUM_GENOTYPE], double* evals);
double eval(double* pop);
int highestPopNum(double* evals);
void writeRouletteRatios(double const evals[],double*);
int selectParent(double* const ratios);
void writeCrossoveredGenotype(double* offspring, double* const parentA, double* const parentB);
void writeMutatedGenotype(double* offspring);

double get_rand_real() {
	// 乱数生成器
	static std::mt19937_64 mt64(0);

	std::uniform_real_distribution<double> get_rand_uni_real(0.0, 1.0);

	// 乱数を生成
	return get_rand_uni_real(mt64);
}

int main() {

	
	std::random_device rnd;

	double genotype[POPULATION][MAXIMUM_GENOTYPE] = { 0 };

	//評価
	double evals[POPULATION] = { 0 };


	//第一群の生成
	for (int y = 0; y < POPULATION; y++) {
		int now_weight = 0;
		int now_eval = 0;

		for (int x = 0; x < POPULATION; x++) {
			//生成
			if (rnd() % 2 == 0) {
				//ほんとに入れてええのか？
				if (now_weight + weight[x] > MAXIMUM_WEIGHT) {
					//超えたので入れないでこの遺伝子はループ終わり
					continue;
				}
				//入れてもOKなので入れる
				genotype[y][x] = 1;
				//入れたのでweightの更新
				now_weight += weight[x];
				//評価更新
				now_eval += prise[x];

			}


			//表示
			cout << genotype[y][x] << ",";


		}
		//全体評価
		evals[y] = now_eval;

		//表示
		cout << "weight" << now_weight << "eval" << evals[y] << endl;
	}

	//進化ループ
	for (int gen = 0; gen < 2; gen++){
		//ルーレットフェーズ
		double ratios[POPULATION] = { 0 };

		writeRouletteRatios(evals,ratios);

		//交配（POPULATION体分）
		for (int newPOP = 0; newPOP < POPULATION; newPOP++) {
			
			//親の選択(2体)
			//randomを使って親を2体選択
			int parentA = selectParent(ratios);
			int parentB = selectParent(ratios);

			//交叉

			//子孫
			double offspring[MAXIMUM_GENOTYPE] = { 0 };

			//交叉判定よりも小さいなら交叉
			if (get_rand_real() < CROSS) {
				writeCrossoveredGenotype(offspring, genotype[parentA], genotype[parentB]);
			}
			else {
				//交叉しない場合はparentA
				for (int i = 0; i < MAXIMUM_GENOTYPE; i++) {
					offspring[i] = genotype[parentA][i];
				}
			}

			//突然変異
			if (get_rand_real() < MUTATION) writeMutatedGenotype(offspring);


			//Accepting :　新しい子孫を新しい個体群へ
			for (int i = 0; i < MAXIMUM_GENOTYPE; i++) {
				genotype[newPOP][i] = offspring[i];
			}
		}
			
		
		//評価
		writeGenotypeEval(genotype, evals);

		//優秀な奴
		int highestPop = highestPopNum(evals);

		cout << "GEN"<<gen<<"*"<<"evals" << evals[highestPop] << endl;
	}
}

//引数は，MAXIMUM_GENOTYPEこの要素をもった配列へのポインタ
void writeGenotypeEval(double (* genotype)[MAXIMUM_GENOTYPE], double* evals) {
	for (int y = 0; y < POPULATION; y++) {
		int now_weight = 0;
		int now_eval = 0;

		for (int x = 0; x < POPULATION; x++) {
			if (genotype[y][x] == 1) {
				//入ってるのでweightの更新
				now_weight += weight[x];
			}
			//評価更新
			now_eval += prise[x];
		}
		//全体評価
		evals[y] = now_eval;
	}
}

double eval(double* pop) {
	double now_eval = 0;
	for (int i = 0; i < POPULATION; i++) {
		if (pop[i] == 1) now_eval += prise[i];
	}
	return now_eval;
}

int highestPopNum(double* evals) {
	int highest = 0;

	for (int i = 1; i < POPULATION; i++) {
		if (evals[highest] < evals[i]) highest = i;
	}
	return highest;
}

//価値の配列をもらって，それぞれの価値を正規化した配列を返す
void writeRouletteRatios(double const evals[],double *ratios) {
	double sum = 0;

	//全体の計算
	for (int i = 0; i < POPULATION; i++) {
		sum += evals[i];
	}

	//価値に対する割合の決定
	for (int i = 0; i < POPULATION; i++) {
		ratios[i] = evals[i] / sum;
	}
}
int selectParent(double* const ratios) {
	std::random_device rnd;

	double rndProb = get_rand_real();
	double selectProb = 0;

	

	int selecter = 0;

	for (selecter = 0; selecter < POPULATION; selecter++) {
		//rndより大きくなったらそいつを親にする : 確率の並び方では変わらないはず
		if (selectProb >= rndProb) {
			//selecterを親として返す
			break;
		}
		else
		{
			selectProb += ratios[selecter];
		}
	}

	return selecter;
}

void writeCrossoveredGenotype(double* offspring, double* const parentA, double* const parentB) {
	//一転交叉
	std::random_device rnd;

	int crossover_point = (int)std::floor(get_rand_real() * MAXIMUM_GENOTYPE);

	//交叉
	for (int i = 0; i < MAXIMUM_GENOTYPE; i++) {
		offspring[i] = (crossover_point > i) ? parentA[i] : parentB[i];
	}
}

//突然変異
void writeMutatedGenotype(double* offspring) {

	std::random_device rnd;

	//3個ぐらい入れ替える
	const int MUTATION_NUM = 3;

	for (int i = 0; i < MUTATION_NUM; i++) {

		int point = (int)floor(get_rand_real() * MAXIMUM_GENOTYPE);

		//反転
		offspring[point] = 1 - offspring[point];
	}
}


//参考になる https://www.slideshare.net/kzokm/genetic-algorithm-41617242