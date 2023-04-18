#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

unsigned char** imageread(int& rows, int& cols, Mat& image) {
	string fil;
	cout << "Enter file name please (segmented outputs)" << endl;
	cin >> fil;
	fil = "C://Users//HP//Desktop//assign1//Segmented Outputs//" + fil + ".bmp";
	image = imread(fil, IMREAD_GRAYSCALE);
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
void copy2Darray1(int**& ptr1, unsigned char** ptr, int r, int c) {
	ptr1 = new int* [r];
	for (int i = 0; i < r; i++) {
		ptr1[i] = new int[c];
		for (int j = 0; j < c; j++) {
			ptr1[i][j] = ptr[i][j];
		}
	}

	//return ptr1;
}
int validCheck(int** ptr, int i, int j, int rows, int cols)
{
	if (i < 0 || i == rows || j < 0 || j == cols)
		return 0;
	return ptr[i][j];
}
int findmin(int arr[], int b) {
	int min = INT16_MAX;
	for (int i = 0; i < b; i++) {

		if (arr[i] < min && arr[i] != 0) {
			min = arr[i];
		}

	}
	return min;

}
int findmax(int arr[], int b) {
	int max = 1;
	for (int i = 1; i < b; i++) {

		if (arr[i] > arr[max]) {
			max = i;
		}

	}
	return max;

}
void checksurroundingarray(int** ptr, int i, int j, int rows, int cols, int& counter, int* arr1) {
	bool flag = false;
	int c = 0;
	int temp = 0;
	int arr[] = { validCheck(ptr,i,j - 1,rows,cols),validCheck(ptr,i - 1,j - 1,rows,cols),validCheck(ptr,i - 1,j,rows,cols),validCheck(ptr,i - 1,j + 1,rows,cols) };
	for (int i = 0; i < 4; i++) {
		if (arr[i] != 0) {
			flag = true;
			temp = arr[i];
			c++;
		}
	}

	if (flag == false) {
		ptr[i][j] = counter;
		counter++;

	}
	else if (c == 1) {

		ptr[i][j] = temp;

	}
	else {
		int min = findmin(arr, 4);
		ptr[i][j] = min;
		for (int j = 0; j < 4; j++) {
			if (arr[j] != min && arr[j]) {
				arr1[arr[j]] = min;
			}
		}
	}
}
int** secondscan(int** ptr, int& row, int& col, int arr[]) {
	int count[2500] = {};

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (ptr[i][j] == 0 || arr[ptr[i][j]] == 0) {
				continue;
			}
			do
			{
				ptr[i][j] = arr[ptr[i][j]];
			} while (arr[ptr[i][j]] != 0);
		}
	}
	// for the frequency
	for (int i = 0; i < 2500; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (ptr[i][j] != 0) {
				count[ptr[i][j]]++;
			}

		}
	}


	int maximum = findmax(count, 2500);
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (ptr[i][j] == maximum) {
				ptr[i][j] = 255;
			}
			else {
				ptr[i][j] = 0;
			}
		}
	}

	return ptr;






}
int** scan(int** ptr, int& row, int& col) {
	int arr[2500];
	for (int i = 0; i < 2500; i++) {
		arr[i] = 0;
	}
	int counter = 1;
	//bool nonzero = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (ptr[i][j] != 0) {
				//nonzero = true;
				checksurroundingarray(ptr, i, j, row, col, counter, arr);

			}
		}
	}
	return secondscan(ptr, row, col, arr);


	/*for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (ptr[i][j])
				cout << "*";
			else
				cout << " ";

		}
		cout << endl;
	}*/





}

int **Question11() {
	Mat image;
	int r = 0;
	int c = 0;
	unsigned char** ptr = imageread(r, c, image);
	int** ptr1 = NULL;
	copy2Darray1(ptr1, ptr, r, c);
	return scan(ptr1, r, c);
	/*namedWindow("grayscale image", WINDOW_AUTOSIZE);
	//imshow("grayscale image", image);
	Mat A = cv::Mat(r, c, CV_8UC1);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			A.data[A.step[0] * i + A.step[1] * j + 0] = unsigned char(ptr1[i][j]);
	cv::namedWindow("title", cv::WINDOW_NORMAL);
	cv::imshow("title", A);
	cv::waitKey();*/




}
