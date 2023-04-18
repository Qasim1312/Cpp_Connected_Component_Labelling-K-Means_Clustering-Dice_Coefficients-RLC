#include<iostream>
#include"task2.h"
#include"task1.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

unsigned char** imageread1(int& rows, int& cols) {
	string fil;
	cout << "Enter file name please for task 3 (ground truth) dont need to add _lesion with it" << endl;
	cin >> fil;
	fil = fil + "_lesion";
	
	fil = "C://Users//HP//Desktop//assign1//Ground Truths//" + fil + ".bmp";
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

void copy2Darray2(int**& ptr1, unsigned char** ptr, int r, int c) {
	ptr1 = new int* [r];
	for (int i = 0; i < r; i++) {
		ptr1[i] = new int[c];
		for (int j = 0; j < c; j++) {
			ptr1[i][j] = ptr[i][j];
		}
	}

	//return ptr1;
}
// using a while loop for comparing all 49 dice coefficients

int main() {
	int i = 0;
	cout << "The function will run 49 until you press 5 to exit, this is to compare the dice coefficients of both Task 1 and Task 2 against the ground truths" << endl;
	while (i !=5) {
		int falsepositive = 0;
		int falsenegative = 0;
		int truepositive = 0;
		int r = 0;
		int c = 0;
		int** ptrtask1 = Question11();
		int** ptrtask2 = Question2();
		unsigned char** ptrimage = imageread1(r, c);
		int** ptri = NULL;
		copy2Darray2(ptri, ptrimage, r, c);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (ptrtask1[i][j] == 255 && ptri[i][j] == 255) {
					truepositive++;
				}
				if (ptrtask1[i][j] == 0 && ptri[i][j] == 255) {
					falsepositive++;
				}
				if (ptrtask1[i][j] == 255 && ptri[i][j] == 0) {
					falsenegative++;

				}

			}
		}
		float dice1 = (float)((2.0 * truepositive) / (falsenegative + ((2.0 * truepositive) + falsepositive)));
		falsepositive = 0;
		falsenegative = 0;
		truepositive = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (ptrtask2[i][j] == 255 && ptri[i][j] == 255) {
					truepositive++;
				}
				else if (ptrtask2[i][j] == 0 && ptri[i][j] == 255) {
					falsepositive++;
				}
				else if (ptrtask2[i][j] == 255 && ptri[i][j] == 0) {
					falsenegative++;

				}

			}
		}
		float dice2 = (float)((2.0 * truepositive) / (float)(falsenegative + ((2.0 * truepositive) + falsepositive)));
		cout << "Dice coefficient of question 1 is " << dice1 << endl;
		cout << "Dice coefficient of question 2 is " << dice2 << endl;
		cout << "Do you want to continue? Press 1 to conitine and 5 to exit" << endl;
		cin >> i;
	}



}
