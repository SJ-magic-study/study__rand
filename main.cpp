/************************************************************
rand()関数の使用
	description
		rand() 関数は、stdlib.hで定義されている関数で、 0 から RAND_MAX の間(0以上 RAND_MAX以下)の疑似乱数整数を返します。 
		この関数を用いて、0より大きくNより小さい一様乱数（実数）を生成するには
			((double)rand() / ((double)RAND_MAX + 1)) * N
		とすればできます。
		
		
		整数がほしいなら、
			(int)( ((double)rand() / ((double)RAND_MAX + 1)) * N )
			
		整数が必要で、浮動小数を使うことが気になるのなら、
			rand() / (RAND_MAX / N + 1)
		としてください。
		
		どちらもNがRAND_MAXにくらべて十分小さいことを仮定しています。
		
	
	乱数の質
		すぐに思いつく方法として
		rand() % N
		も考えられますが、この方法 (これは 0から N-1までの数を返そうとする)は乱数の質が低いので使わないでください。
		なぜなら乱数発生器の多くで下位のビットは、ランダムにならないからです。
		
	srand() 関数
		srand()関数は、 rand()関数で作られる疑似乱数整数系列の新しい種として、その引数の値を使用します。 
		この関数を使用して作られた疑似乱数系列は、同じ値を引数に使用してsrand()を呼ぶことによって、 再現することが可能です。 
		種の値が与えられない場合には、rand()関数は自動的に 1 を種とします。 
		本当にランダムに乱数を発生したいときは、srand()を使って、擬似乱数発生器にランダムな初期値を与えてください。
		よくある乱数の種は、時刻などです。
		注意：プログラム中で srand()を2回以上呼んで役にたつことは滅多にありません。 本当にランダムな数を得ようと思って、rand()を呼ぶ前に毎回srand() を呼ぶような真似はぜったいにしてはいけません。
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************
******************************/
int main(int argc, char **argv)
{
	/********************
	********************/
	enum MODE{
		MODE_DOUBLE,
		MODE_INT,
		MODE_INT_INT,
		
		NUM_MODE,
	};
	
	/********************
	********************/
	MODE mode;
	int N;
	int NUM;
	
	if(argc < 4){
		printf("*.exe [mode] [max] [Num]\n");
		printf("\t0:double\n");
		printf("\t1:int\n");
		printf("\t2:int int\n");
		return 1;
		
	}else{
		int mode_temp = atoi(argv[1]);
		if( (mode_temp < 0) || (NUM_MODE <= mode_temp) ){
			mode_temp = 0;
		}
		mode = MODE(mode_temp);
		
		
		N = atoi(argv[2]);
		
		NUM = atoi(argv[3]);
	}
	
	/********************
	********************/
	srand((unsigned int)time(NULL));
	
	/********************
	********************/
	int counter = 0;
	FILE* fp;
	
	fp = fopen("Log.txt", "w");
	for(int i = 0; i < NUM; i++){
		switch(mode){
			case MODE_DOUBLE:
				fprintf(fp, "%20.5f", ((double)rand() / ((double)RAND_MAX + 1)) * N);
				break;
				
			case MODE_INT:
				fprintf(fp, "%10d", (int)( ((double)rand() / ((double)RAND_MAX + 1)) * N ));
				break;
				
			case MODE_INT_INT:
				fprintf(fp, "%10d", rand() / (RAND_MAX / N + 1));
				break;
		}
		
		counter++;
		if(9 < counter){
			counter = 0;
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
	
	printf("Finish\n");
	
	return 0;
}
