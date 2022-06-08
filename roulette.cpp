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

int main() {


	double pop[POPULATION][50] = { 0 };

	//評価
	double evals[POPULATION] = { 0 };

	std::random_device rnd;

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
				pop[y][x] = 1;
				//入れたのでweightの更新
				now_weight += weight[x];
				//評価更新
				now_eval += prise[x];

			}


			//表示
			cout << pop[y][x] << ",";


		}
		//全体評価
		evals[y] = now_eval;

		//表示
		cout << "weight" << now_weight << "eval" << evals[y] << endl;
	}

	//ルーレットフェーズ
	double* ratios = roulette(evals);

	//親の選択(2体)
	//randomを使って親を2体選択
	/*
	double rnd= random(0,1.0);
	double selectProb=0;
	for(int i=0;i<POPULATION;i++){
	//rndより大きくなったらそいつを親にする : 確率の並び方では変わらないはず
		if(selectProb >= rnd) parent=i;
	}
	*/

	//交叉

	//突然変異

	//Accepting :　新しい子孫を新しい個体群へ

	//ループ上へ戻る

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

	//全体の計算
	for (int i = 0; i < POPULATION; i++) {
		sum += evals[i];
	}

	//価値に対する割合の決定
	for (int i = 0; i < POPULATION; i++) {
		ratios[i] = evals[i] / sum;
	}

	return ratios;
}
double selectParent() {
	
}