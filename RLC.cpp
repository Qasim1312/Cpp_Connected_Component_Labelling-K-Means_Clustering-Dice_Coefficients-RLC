#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

unsigned char** imageread(int& rows, int& cols) {
	string fil;
	cout << "Enter file name please" << endl;
	cin >> fil;
	fil = "C://Users//HP//Desktop//assign1//Segmented Outputs//" + fil + ".bmp";
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
// create node
struct node {
	int data;
	node* right;
	node* down;
};
node* newnode(int c) {
	node* temp = new node();
	temp->data = c;
	temp->right = NULL;
	temp->down = NULL;
	return temp;

}
// making a two dimensional linked list and copying the two dimensional array of picture int it in a way as instructed by the question 
void create(int** arr, const int m, int n) {
	node* head = newnode(0);
	//node* hadrow = NULL;
	node* downtemp = head;
	node* righttemp = downtemp;
	node* temp;
	bool whi_bla = false; //black.... Using black and white boolean expression to enter the values of position of whites into the array while the blacks remain -1's
	for (int i = 0; i < m; i++) {
		whi_bla = true;
		for (int j = 0; j < n; j++) {
			if (bool(arr[i][j]) == whi_bla) {
				righttemp->data = j;
				righttemp->right = newnode(0);
				righttemp = righttemp->right;

				whi_bla = !whi_bla;
			}
		}
		righttemp->data = -1;
		downtemp->down = newnode(0);
		downtemp = downtemp->down;
		righttemp = downtemp;
	}
	downtemp = head;
	righttemp = downtemp;
	// Printing the Two Dimensional Linked List
	cout << m << " " << n << endl;
	while (downtemp != NULL) {

		while (righttemp != NULL) {

			cout << righttemp->data << " ";
			righttemp = righttemp->right;
		}
		cout << endl;
		
		downtemp=downtemp->down;
		righttemp = downtemp;

	}

}


void copy2Darray(int**& ptr1, unsigned char** ptr, int r, int c) {
	ptr1 = new int* [r];
	for (int i = 0; i < r; i++) {
		ptr1[i] = new int[c];
		for (int j = 0; j < c; j++) {
			ptr1[i][j] = ptr[i][j];
		}
	}
	create(ptr1, r, c);
	
	//return ptr1;
}


	

int main() {
	int r = 0;
	int c = 0;
	unsigned char** ptr = imageread(r, c);
	int** ptr1 = NULL;
	copy2Darray(ptr1, ptr, r, c);
	
	
}

