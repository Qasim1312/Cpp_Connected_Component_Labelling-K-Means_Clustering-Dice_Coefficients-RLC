#include<iostream>
#include<opencv2/opencv.hpp>
#include<ctime>
using namespace std;
using namespace cv;

unsigned char** imageread(int& rows, int& cols) {
	string fil;
	cout << "Enter file name please" << endl;
	cin >> fil;
	fil = "C://Users//HP//Desktop//assign1//Original Images//" + fil + ".bmp";
	Mat image = imread(fil, IMREAD_GRAYSCALE);
	rows = image.rows;
	cols = image.cols;
	unsigned char** ptr = new unsigned char* [rows];
	for (int i = 0; i < rows; i++)
	{
		ptr[i] = new unsigned char[cols];
		for (int j = 0; j < cols; j++)
		{
			ptr[i][j] = image.at<unsigned char>(i, j);
		}
	}
	return ptr;

}

int findmin(int x, int y) {
	if (x < y) {
		return x;
	}
	else {
		return y;
	}
}
void cluster(int **&ptr,int row,int cols) {
	int** ptr1 = new int* [row];

	for (int i = 0; i < row;  i++) {
		ptr1[i] = new int[cols];
      }
	srand((unsigned)time(NULL));
	int c1 = 75;  //rand() % 255;         // making two random clusters
	int c2 = 150;  //rand() % 255;
	int contc1 = c1;
	int contc2 = c2;
	int counter = 0;
	 do {
		 contc1 = c1;
		 contc2 = c2;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < cols; j++) {
				int cmp1 = abs(c1 - ptr[i][j]);
				int cmp2 = abs(c2 - ptr[i][j]);
				int temp = findmin(cmp1, cmp2);
				if (temp == cmp1) {
					ptr1[i][j] = 255; //1
				}
				else if (temp == cmp2) {
					ptr1[i][j] = 0;
				}

			}
		}

		// now the grouping

		int c1sum = 0;
		int c2sum = 0;
		int counter1 = 0;
		int counterz = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < cols; j++) {
				if (ptr1[i][j] == 255) { //1
					c1sum += ptr[i][j];
					counterz++;
				}
				else if (ptr1[i][j] == 0) {
					c2sum += ptr[i][j];
					counter1++;
				}

			}
		}
		if (counter1 == 0 || counterz == 0)
		{
			 c1 = rand() % 255;
			 c2 = rand() % 255;
		}


		c1 = c1sum / counterz;
		c2 = c2sum / counter1;
		//cout << ++counter << endl;
	}while (c1 != contc1 || c2 != contc2); //until the clusters dont have homogenkus k values underneath

	for (int i = 0; i < row; i++)
		for (int j = 0; j < cols; j++)
			ptr[i][j] = ptr1[i][j];       
}


void copy2Darray(int**& ptr1, unsigned char** ptr, int r, int c) {
	ptr1 = new int* [r];
	for (int i = 0; i < r; i++) {
		ptr1[i] = new int[c];
		for (int j = 0; j < c; j++) {
			ptr1[i][j] = ptr[i][j];
		}
	}
	
	
	cluster(ptr1, r, c);
	//return ptr1;
}


int main() {
	int r = 0;
	int c = 0;
	unsigned char** ptr = imageread(r, c);
	int** ptr1 = NULL;
	copy2Darray(ptr1, ptr, r, c);
	
	Mat A = cv::Mat(r, c, CV_8UC1);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			A.data[A.step[0] * i + A.step[1] * j + 0] = unsigned char(ptr1[i][j]);
	cv::namedWindow("title", cv::WINDOW_NORMAL);
	cv::imshow("title", A);
	cv::waitKey(); 
	
}



