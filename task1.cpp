#include <iostream>
#include <sstream>
#include <thread>

const int NMAX = 1000;

int A[NMAX][NMAX];
int B[NMAX][NMAX];
int C[NMAX][NMAX];

void fillmat(int r, int c, int M[][NMAX])
{
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			M[i][j] = rand() % 100;
		}
	}
}

void multVV(int i, int j, int s)
{
	C[i][j] = 0;
	for(int k = 0; k < s; k++){
		C[i][j] += A[i][k]*B[k][j];
	}
	std::stringstream sstm;
	sstm << "C["<< i << "," << j << "] = "<< C[i][j] <<"\n";
	std::cout << sstm.str();
}

int main(){
	srand(time(NULL));
	int n,m,k;

	std::cout << "n:" << std::endl;
	std::cin >> n;
	std::cout << "m:" << std::endl;
	std::cin >> m;
	std::cout << "k:" << std::endl;
	std::cin >> k;

	fillmat(n, m, A);
	fillmat(m, k, B);

	std:: thread*th[n][k];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < k; j++){
			th[i][j] = new std::thread(multVV, i, j, m);
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < k; j++){
			(*th[i][j]).join();
		}
	}

	return 0;
}
