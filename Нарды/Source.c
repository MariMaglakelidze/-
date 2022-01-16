#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <Windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
// a seychas?
//���������� ����������, ������� �������� ��� �������


int W_or_B;

void end_cycle(struct Node* lst); //����������� ������
void add_New_element(struct Node* lst, int number); //��������� �������
void out_put(); //����� �����
void double_chain(start); // ��� end_cycle �� ����� ��� 2 ���������� �������
void plus_black(struct Node* start); //���������� ������ ���� �� ������ ������
int out_rule(int l, int r, struct Node* start, int difference, int from); //��������� �� ��������� 6 ������(��� �� ��� �����)
struct Node  //������ ������
{
	int data;
	int position;
	struct Node* link_next;
	struct Node* link_before;
	char color;
	int position_b;
	int importance;
	int importance_w;
};

struct Element
{
	int importance;
	int importance_w;
	int element_number;
	struct Leafs* left;
	struct Leafs* right;
	struct Leafs* sum;
};

struct Leafs
{
	int importance;
	int importance_w;
	int element_number;
	struct Leafs* back;
};
struct Node* create_cycle(int a);
struct Node* start;

void numberin_element(struct Node* start); // ������������� ������� 
void numberin_element_b(struct Node* start); //��� ������
char find_color(struct Node* start, int from); //�������� ����� ������
void step_by_step(struct Node* start); //�������� ������� �� ����� �����
int find_data(struct Node* start, int from); //���-�� ����� � ������
void minus(struct Node* start, int from); // ��������� �����
void plus(struct Node* start, int to, char color); // ������� �����
char truth_of_the_move(); // �������� �� ��� ������� ��������
int consecutive_chip(struct Node* start); //�������� �� ���� �� 6 ������
int first_element_touch(int fet, int l, int r, char color, int position); //�������� �� ��, ����� �� � ������ ������� 2 ����
int end_game(struct Node* start); // �������� �� ��������� 6
int find_position(struct Node* start, int from); // ����� �������
int find_position_b(struct Node* start, int from);
int win(struct Node* start); // �������� ������
struct Element* create_tree(void); // ������� ������ ��� AI
void find_more_important(struct Element* root); // ������� ����� ������ ��������
int find_impotance(struct Node* start, int position); // ��������������� ��� �����������
void push_element(struct Element* root, int l, int r, int to[], int mas[3], struct Element* start); // �������� �������, ������� ���������� ���
void AI(struct Node* start); //���� AI
int washing_chip(int to); // ��������� ������)
void start_important(struct Node* start); // ������������ ��� ������ AI
void re_important(struct Node* start); // ��������� ��������
void zero_imp(struct Node* start, int to); // ��������� ������ �� imp
void move_el(int l, int r, struct Node* start, int mas[]); // ����� ������� ��� ������ ��� ����
void end_minus(struct Node* start, int from); // ������� ����� ���� �������� ����� ����
void AI_W(struct Node* start); //�� �����
void start_important_w(struct Node* start);
void re_important_w(struct Node* start);
void move_el_w(int l, int r, struct Node* start, int mas[], int left_dif, int right_dif);
int out_rule_w(int l, int r, struct Node* start, int difference, int from, int double_difference_r, int double_difference_l);
void zero_imp_w(struct Node* start, int to);

int main(void) {
	W_or_B = 0;
	//������ - �����
	srand(time(NULL));
	start = (struct Node*)malloc(sizeof(struct Node));
	struct Node* temp_start;
	temp_start = (struct Node*)malloc(sizeof(struct Node));
	start->data = 15;//����� ������ �������
	start->color = 'w';
	start->link_next = NULL;
	//�������� �������� 
	for (int i = 0; i < 11; i++) {
		add_New_element(start, 0);
	}
	add_New_element(start, 15);

	plus_black(start);

	for (int i = 0; i < 11; i++) {
		add_New_element(start, 0);
	}
	end_cycle(start);
	numberin_element(start);
	//����� ���������� ��������� ������
	double_chain(start);
	printf("//////// If you haven't available to move your chips, enter from: 0, to: 0 \\\\\\\\\\\\\\\\\n");
	printf("Change game mode: \n1.AI vs AI\n2.Human vs AI\n");
	int change_mode = 0;
	scanf("%d", &change_mode);
	out_put();
	start_important(start); // ����������� ����
	start_important_w(start);
	if (change_mode == 2)
	{
		while (1) {
			if (W_or_B % 2 == 0)
				step_by_step(start);
			else
				AI(start);
			if (win(start) > 0)
				return 0;
			W_or_B++;
		}
	}
	else
	{
		while (1) {
			if (W_or_B % 2 == 0)
				AI_W(start);
			else
				AI(start);
			if (win(start) > 0)
				return 0;
			W_or_B++;
		}
	}

	return 0;
}

struct Node* create_cycle(int a)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = a;
	temp->link_next = NULL;
	return temp;
}

// ���������� ��������  // 1 -> 2 -> 3 -> 1
void add_New_element(struct Node* lst, int number)
{
	struct Node* temp;
	temp = (struct Node*)malloc(sizeof(struct Node));
	while (lst->link_next != NULL) {
		lst = lst->link_next;
	}
	lst->link_next = temp;
	temp->data = number;
	temp->link_next = NULL;
	temp->color = 'u';
}

void end_cycle(struct Node* lst) //��������� ������� �������� ��������� ������
{
	struct Node* end = lst;
	while (lst->link_next != NULL) {
		lst = lst->link_next;
	}
	lst->data = 0;
	lst->link_next = end;
}
void out_put() { //����� ������ (��� ������ �� ����� ����, ������ �������� �������)
	struct Node* temp_next_out, * temp_next_before;
	//��� ��������� �� ����� ������  ������
	temp_next_out = temp_next_before = start;
	temp_next_before = temp_next_before->link_before;
	//������ �������
	if (temp_next_before->color == 'b') {
		printf("*");
		printf("%d\t", temp_next_before->data);
	}
	else printf("%d\t", temp_next_before->data);
	//���� 11 ���������
	for (int i = 0; i < 11; i++) {
		temp_next_before = temp_next_before->link_before;
		if (temp_next_before->color == 'b') {
			printf("*");
			printf("%d\t", temp_next_before->data);
		}
		else printf("%d\t", temp_next_before->data);

	}
	printf("\n\n\n\n\n");
	///������ ����� �����
	if (temp_next_out->color == 'b') {
		printf("*");
		printf("%d\t", temp_next_out->data);
	}
	else printf("%d\t", temp_next_out->data);

	for (int i = 0; i < 11; i++) {
		temp_next_out = temp_next_out->link_next;
		if (temp_next_out->color == 'b') {
			printf("*");
			printf("%d\t", temp_next_out->data);
		}
		else printf("%d\t", temp_next_out->data);
	}
}
//���������� ������ �� ������������
void double_chain(struct Node* start)
{
	struct Node* temper, * end;
	temper = end = start;
	start = start->link_next;
	start->link_before = temper;
	while (start != end) {
		temper = temper->link_next;
		start = start->link_next;
		start->link_before = temper;
	}
}

void step_by_step(struct Node* start)
{
	int white;
	//����� � ������ �����
	int r, l;
	//�������� ������
	r = rand() % 6 + 1;
	l = rand() % 6 + 1;
	printf("R: %d, L: %d\n", r, l);

	if (W_or_B % 2 == 0)
		printf("White turn\n");
	else printf("Black turn\n");

	// ������ � ���� ������
	int from, to, step;
	// ����� ��� ��������� �������
	int double_difference_l;
	int double_difference_r;
	//�������� �� ��, ����� �� � ������� �������� 2 ����
	int fet;
	if (W_or_B > 1)
		fet = 1;
	else fet = 0;
	//�������� �� ��������� ������, ����� 4 ���� � �������� �� ������� ���
	if (l == r) {
		step = 4;
		double_difference_l = 0;
		double_difference_r = 0;
	}
	else
	{
		step = 2;
		double_difference_l = 1;
		double_difference_r = 1;
	}

	for (int i = 0; i < step; i++) {
	repeat://���������� �������� ������������ ���� �����
		printf("Choose number from:\n");
		scanf("%d", &from);
		from--;
		printf("Where to:\n");
		scanf("%d", &to);
		to--;
		if (from == to && from == -1)
			return 0;
		int difference;
		difference = to - from;// ������� ����� ������
		if (difference < 1) {// ���� ������ ������
			printf("Wrong, choose correct number\n");
			goto repeat;
		}
		int check_condition = 0;
		white = find_data(start, from);
		char color = find_color(start, from);

		//�������� ����� �� 2 ���� � 1 �������
		if (first_element_touch(fet, l, r, color, from) == 0)
			;
		else if (first_element_touch(fet, l, r, color, from) == 1)
			fet++;
		else
		{
			printf("Wrong, choose correct number\n");
			goto repeat;
		}
		//�������� ��������
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move() || out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1) {
			printf("Wrong, choose correct number\n");
			goto repeat;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))
		{
			;
		}
		else
		{
			printf("Wrong, choose correct number\n");
			goto repeat;
		}

		//����� �� ����� ����� ������ 2 ���� ��� 3 ��� ���������� �������
		if (l != r) {
			if (white != 0 && difference == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_l++;
			}
			if (white != 0 && difference == r && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_r++;
			}
		}
		if (l == r) {
			if (double_difference_l < 2) {
				if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
					double_difference_l++;
				}
			}
			else {
				if (double_difference_r < 2) {
					if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
						double_difference_r++;
					}
				}
			}
		}
		//�������� ������������ ����
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move()) {
			printf("Wrong, choose correct number\n");
			if (double_difference_l > 2) //�� ������ �� ������� ������ ��� ��� ����� ����� ������
				double_difference_l = 2;
			if (double_difference_r > 2)
				double_difference_r = 2;
			goto repeat;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from)) {

			//�������� �� 6 � �����
			if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 0)
				;
			else if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1)
			{
				printf("Wrong, choose correct number\n");
				goto repeat;
			}
			else
			{
				minus(start, from);
				out_put();
				printf("\n\n\n");
				continue;
			}
			minus(start, from);
			plus(start, to, color);
			//�������� �� 6 ������, ����� ����� � ��������� ������
			if (consecutive_chip(start) == 1)
			{
				printf("Wrong, choose correct number\n");
				double_difference_r--;
				minus(start, to);
				plus(start, from, color);
				goto repeat;
			}
			out_put();
			printf("\n\n\n");
		}
		else
		{
			printf("Wrong, choose correct number\n");
			goto repeat;
		}
	}
}

char truth_of_the_move()
{
	if (W_or_B % 2 == 0)
		return 'w';
	else
		return 'b';
}

//����� �������� � ���������� ��� data
int find_data(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	return temp->data;
}

void minus(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	temp->data = temp->data - 1;
	if (temp->data == 0)
		temp->color = 'u';

	return temp->data;
}

void end_minus(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	temp->data = temp->data - 1;
	if (temp->data == 0)
		temp->color = 'u';
}

void plus(struct Node* start, int from, char color)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	temp->data = temp->data + 1;
	temp->color = color;

	return temp->data;
}

char find_color(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	return temp->color;
}


void plus_black(struct Node* start)
{
	struct Node* temp = start;
	temp = temp->link_next;
	while (temp->data != 15)
		temp = temp->link_next;
	temp->color = 'b';
}

void numberin_element(struct Node* start)
{
	int i = 1;
	struct Node* temp = start;
	temp->position = 1;
	temp = temp->link_next;
	i++;
	while (i != 25)
	{
		temp->position = i;
		temp = temp->link_next;
		i++;
	}
}
void numberin_element_b(struct Node* start)
{
	for (int i = 0; i < 12; i++)
	{
		start = start->link_next;
	}
	int i = 1;
	struct Node* temp = start;
	temp->position = 1;
	temp = temp->link_next;
	i++;
	while (i != 25)
	{
		temp->position = i;
		temp = temp->link_next;
		i++;
	}
}

int consecutive_chip(struct Node* start)
{
	struct Node* temp = start;
	int cost = 1;
	int color = 'u';
	for (int i = 0; i < 30; i++)
	{
		color = temp->color;
		temp = temp->link_next;
		if (color == temp->color && color != 'u')
			cost++;
		else
		{
			color = 'u';
			cost = 1;
		}
		if (cost >= 6)
			return 1;
	}
	return 0;
}

int first_element_touch(int fet, int l, int r, char color, int position)
{
	if (color == 'w') {
		if ((position != 0)) // ��������� �� �� 1 ����� � ����� �� ���� ���
			return 0;
		else if (l != r && fet < 2)
			return 1;
		else if (l == r && fet < 2 && W_or_B == 0) // ���� ��, �� �������� ��������� �� ����� ��� ������ ����
			return 1;
		else if (W_or_B > 1 && fet < 2)
			return 1;
		else return 2;
	}
	if (color == 'b') {
		if ((position != 12)) // ��������� �� �� 13 ����� � ����� �� ���� ���(for black)
			return 0;
		else if (l != r && fet < 2)
			return 1;
		else if (l == r && fet < 2 && W_or_B == 1) // ���� ��, �� �������� ��������� �� ����� ��� ������ ����
			return 1;
		else if (W_or_B > 1 && fet < 2)
			return 1;
		else return 2;
	}
	return 0;
}

int out_rule(int l, int r, struct Node* start, int difference, int from, int double_difference_r, int double_difference_l) // 0 - ��� ����, �� ��������� ���� �� ��� � ����, 1 - ������, 2 - ����� �����, ����� ��� ����
{
	if (W_or_B % 2 == 0)
	{
		if (end_game(start) == 0)
		{
			if (difference + find_position(start, from) > 24)
				return 1; //������
			else return 0; // ��� ����
		}
		else
		{
			if (difference + find_position(start, from) > 24)
				return 2; // �����
			else return 0; // ��� ����
		}
	}
	if (W_or_B % 2 == 1)
	{
		if (end_game(start) == 0) //���� ������ �� ������� // ��������
		{
			if (difference + find_position_b(start, from) > 24)
				return 1; //������
			else return 0; // ��� ����
		}
		else // �������� ��� ������ �����, ���� ��������(2 �������, 1 - ���� �����, ������� ������� �����, 2 - ����� ���)
		{
			if (double_difference_r < 2) //��������
			{
				int i = 12 - r;
				for (i; i++; i < 13)
				{
					if (find_color(start, i - 1) == 'b')
					{
						double_difference_r++;
						end_minus(start, i - 1);
						return 2; //��������� ���������� �����, ����� ������� ������ �� ��������
					}
				}
				return 0;
			}

			else if (find_color(start, 12 - l) == 'b' && double_difference_l < 2)
			{
				int i = 13 - l;
				for (i; i++; i < 13)
				{
					if (find_color(start, i - 1) == 'b')
					{
						double_difference_l++;
						end_minus(start, i - 1);
						return 2; //��������� ���������� �����, ����� ������� ������ �� ��������
					}
				}
				return 0;
			}
			else return 0; // ��� ����
		}
	}

}

int out_rule_w(int l, int r, struct Node* start, int difference, int from, int double_difference_r, int double_difference_l) // 0 - ��� ����, �� ��������� ���� �� ��� � ����, 1 - ������, 2 - ����� �����, ����� ��� ����
{
	if (W_or_B % 2 == 0)
	{
		if (end_game(start) == 0) //���� ����� �� ������� // ��������
		{
			if (difference + find_position(start, from) > 24)
				return 1; //������
			else return 0; // ��� ����
		}
		else // �������� ��� ����� �����, ���� ��������(2 �������, 1 - ���� �����, ������� ������� �����, 2 - ����� ���)
		{
			if (double_difference_r < 2) //��������
			{
				int i = 24 - r;
				for (i; i++; i < 25)
				{
					if (find_color(start, i - 1) == 'w')
					{
						double_difference_r++;
						end_minus(start, i - 1);
						return 2; //��������� ���������� �����, ����� ������� ������ �� ��������
					}
				}
				return 0;
			}

			else if (find_color(start, 24 - l) == 'w' && double_difference_l < 2)
			{
				int i = 25 - l;
				for (i; i++; i < 25)
				{
					if (find_color(start, i - 1) == 'b')
					{
						double_difference_l++;
						end_minus(start, i - 1);
						return 2; //��������� ���������� �����, ����� ������� ������ �� ��������
					}
				}
				return 0;
			}
			else return 0; // ��� ����
		}
	}

}

int end_game(struct Node* start)
{
	struct Node* temp = start;
	if (W_or_B % 2 == 0)
	{
		for (int i = 0; i < 18; i++)
		{
			if (temp->color == 'w')
				return 0; // �� ������ 18�� ���� �����
			if (i == 18)
				return 1;// �� ������ 18�� ��� �����
			temp = temp->link_next;
		}
	}
	if (W_or_B % 2 == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			temp = temp->link_next;
		}
		for (int i = 0; i < 18; i++)
		{
			if (temp->color == 'b')
				return 0;
			if (i == 18)
				return 1;
			temp = temp->link_next;
		}
	}
	return 1;
}

int find_position(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	return temp->position;
}

int find_position_b(struct Node* start, int from)
{
	struct Node* temp = start;
	for (int i = 0; i < from; i++) {
		temp = temp->link_next;
	}
	return temp->position_b;
}

int win(struct Node* start)
{
	char win_w = 'u';
	char win_b = 'u';
	for (int i = 0; i < 24; i++)
	{
		if (start->color == 'b')
			win_b = 'b';
		if (start->color == 'w')
			win_w = 'w';
		start = start->link_next;
	}
	if (win_b == 'u') // ������ ������
	{
		printf("BLACK WIN");
		return 2;
	}
	if (win_w == 'u') // �����
	{
		printf("WHITE WIN");
		return 1;
	}
	else return 0; // ����������
}


// Unready tasks
// �������� �������� 
/*
Desk
15 ���� <- 0 <- 0 <- 0 <- 0 <- 0	|	<- 0 <- 0 <- 0 <- 0 <- 0 <- 0
Black chip							|								^
	|								|								|
	v								|								^
									|								|
	|								|
	v								|								^
15 ����-> 0 -> 0 -> 0 -> 0 -> 0 ->  |   0 -> 0 -> 0 -> 0 -> 0 -> 0  |
White chip
(Strat)
*/

struct Element* create_tree(void)
{
	struct Element* root = (struct Element*)malloc(sizeof(struct Element));
	struct Leafs* Left_leaf = (struct Leafs*)malloc(sizeof(struct Leafs));
	struct Leafs* Right_leaf = (struct Leafs*)malloc(sizeof(struct Leafs));
	struct Leafs* sum_leaf = (struct Leafs*)malloc(sizeof(struct Leafs));
	root->left = Left_leaf;
	root->right = Right_leaf;
	root->sum = sum_leaf;
	Left_leaf->back = root;
	Right_leaf->back = root;
	sum_leaf->back = root;
	return root;
}

void find_more_important(struct Element* root)
{
	if (root->left->importance > root->right->importance)
	{
		root->importance = root->left->importance;
		root->element_number = root->left->element_number;
	}
	else
	{
		root->importance = root->right->importance;
		root->element_number = root->right->element_number;
	}
	if (root->importance < root->sum->importance)
	{
		root->importance = root->sum->importance;
		root->element_number = root->sum->element_number;
	}
}


int find_impotance(struct Node* start, int position)
{
	struct Node* temp = start;
	for (int i = 0; i < position - 1; i++) {
		temp = temp->link_next;
	}
	return temp->importance;
}

//// �������� �������, ������� ������� ����� ������������ ���������� ��� � ������� ���� ������
//void push_element(struct Element* root, int l, int r, int to[4][15], int mas[3], struct Element* start)
//{
//	root->left->importance = find_impotance(start, to[0]);
//	root->right->importance = find_impotance(start, to[1]);
//	root->sum->importance = find_impotance(start, to[2]);
//	find_more_important(root);
//	mas[1] = root->importance; //������ � ������ �������� ������
//	mas[2] = root->element_number; // ������ ����� ������ ������
//	mas[3] = to[3];
//}

//����� ���� ��������� ����� ���� ��, ���� ������ ������, ������� ���-�� �����, ������� ����� ��������
int find_true_move_ai(struct Node* start)
{
	int j = 0;
	struct Node* temp = start;
	for (int i = 0; i < 23; i++)
	{
		if (temp->color == 'b')
		{
			j++;
		}
		temp = temp->link_next;
	}
	return j;
}

void AI(struct Node* start)
{
	struct Element* root = (struct Element*)malloc(sizeof(struct Element));
	root = create_tree();
	int white;
	//����� � ������ �����
	int r, l;
	//�������� ������
	r = rand() % 6 + 1;
	l = rand() % 6 + 1;
	printf("R: %d, L: %d\n", r, l);

	if (W_or_B % 2 == 0)
		printf("White turn\n");
	else printf("Black turn\n");

	// ������ � ���� ������
	int from, to, step;
	// ����� ��� ��������� �������
	int double_difference_l;
	int double_difference_r;
	//�������� �� ��, ����� �� � ������� �������� 2 ����
	int fet;
	if (W_or_B > 1)
		fet = 1;
	else fet = 0;
	//�������� �� ��������� ������, ����� 4 ���� � �������� �� ������� ���
	if (l == r) {
		step = 4;
		double_difference_l = 0;
		double_difference_r = 0;
	}
	else
	{
		step = 2;
		double_difference_l = 1;
		double_difference_r = 1;
	}

	for (int i = 0; i < step; i++) {

		start_important(start);
		re_important(start);
	repeatt:;

		int important = 0;
		//���-�� �����, ������� ����� ��������
		int possible_move = 0;
		//������ � ���������� ������
		int mas[3] = { 0 };

		move_el(l, r, start, mas, double_difference_l, double_difference_r);// ��������� ��� ������ �� ��������� ������ �����, ������� ����������� ���
		// �������� ������ � ����� ������

		from = mas[0];
		to = mas[1];
		important = mas[2];

		////������ � to � from �������� position_b, ���� ��������� ��� � ����� �������, ��� ������� ������ �����)))
		//to = washing_chip(to);
		//from = washing_chip(from);
		to--;
		from--;
		int difference;
		if (to < 13 && from > 13)
			difference = 24 - from + to;
		else difference = to - from;
		if (from == to && to == -1)
			return 0;
		int check_road = 0; // �������� - ���� ������
		int check_road_to, check_road_from;
		check_road_to = washing_chip(to);
		check_road_from = washing_chip(from);
		check_road = check_road_to - check_road_from;
		if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 2)
		{
			out_put();
			printf("\n\n\n");
			continue;
		}
		else if (check_road < 1) {// ���� ������ ������   !!!!!!!!!!���������, ����� �� ��� �������
			zero_imp(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		int check_condition = 0;
		white = find_data(start, from);
		char color = find_color(start, from);

		//�������� ����� �� 2 ���� � 1 �������
		if (first_element_touch(fet, l, r, color, from) == 0)
			;
		else if (first_element_touch(fet, l, r, color, from) == 1)
			fet++;
		else
		{
			zero_imp(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		//�������� ��������
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move() || out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1) {
			zero_imp(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))
		{
			;
		}
		else
		{
			zero_imp(start, to);
			printf("AI render\n");
			goto repeatt;
		}

		//����� �� ����� ����� ������ 2 ���� ��� 3 ��� ���������� �������
		if (l != r) {
			if (white != 0 && difference == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_l++;
			}
			if (white != 0 && difference == r && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_r++;
			}
		}
		if (l == r) {
			if (double_difference_l < 2) {
				if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
					double_difference_l++;
				}
			}
			else {
				if (double_difference_r < 2) {
					if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
						double_difference_r++;
					}
				}
			}
		}
		//�������� ������������ ����
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move()) {
			zero_imp(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from)) {

			//�������� �� 6 � �����
			if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 0)
				;
			else if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1)
			{
				zero_imp(start, to);
				printf("AI render\n");
				goto repeatt;
			}
			else
			{
				minus(start, from);
				out_put();
				printf("\n\n\n");
				continue;
			}
			minus(start, from);
			plus(start, to, color);
			//�������� �� 6 ������, ����� ����� � ��������� ������
			if (consecutive_chip(start) == 1)
			{
				double_difference_r--;
				minus(start, to);
				plus(start, from, color);
				zero_imp(start, to);
				goto repeatt;
			}
			out_put();
			printf("\n\n\n");
		}
		else
		{
			printf("AI render\n");
			break;
		}
	}
}

void AI_W(struct Node* start)
{
	struct Element* root = (struct Element*)malloc(sizeof(struct Element));
	root = create_tree();
	int white;
	//����� � ������ �����
	int r, l;
	//�������� ������
	r = rand() % 6 + 1;
	l = rand() % 6 + 1;
	printf("R: %d, L: %d\n", r, l);

	if (W_or_B % 2 == 0)
		printf("White turn\n");
	else printf("Black turn\n");

	// ������ � ���� ������
	int from, to, step;
	// ����� ��� ��������� �������
	int double_difference_l;
	int double_difference_r;
	//�������� �� ��, ����� �� � ������� �������� 2 ����
	int fet;
	if (W_or_B > 1)
		fet = 1;
	else fet = 0;
	//�������� �� ��������� ������, ����� 4 ���� � �������� �� ������� ���
	if (l == r) {
		step = 4;
		double_difference_l = 0;
		double_difference_r = 0;
	}
	else
	{
		step = 2;
		double_difference_l = 1;
		double_difference_r = 1;
	}

	for (int i = 0; i < step; i++) {

		start_important_w(start);
		re_important_w(start);
	repeatt:;

		int important_w = 0;
		//���-�� �����, ������� ����� ��������
		int possible_move = 0;
		//������ � ���������� ������
		int mas[3] = { 0 };

		move_el_w(l, r, start, mas, double_difference_l, double_difference_r);// ��������� ��� ������ �� ��������� ������ �����, ������� ����������� ���
		// �������� ������ � ����� ������

		from = mas[0];
		to = mas[1];
		important_w = mas[2];

		////������ � to � from �������� position_b, ���� ��������� ��� � ����� �������, ��� ������� ������ �����)))
		//to = washing_chip(to);
		//from = washing_chip(from);
		to--;
		from--;
		int difference;
		difference = to - from;
		if (from == to && to == -1)
			return 0;
		int check_road = 0; // �������� - ���� ������
		int check_road_to, check_road_from;
		check_road_to = to;
		check_road_from = from;
		check_road = check_road_to - check_road_from;
		if (out_rule_w(l, r, start, difference, from, double_difference_r, double_difference_l) == 2)
		{
			out_put();
			printf("\n\n\n");
			continue;
		}
		else if (check_road < 1) {// ���� ������ ������   !!!!!!!!!!���������, ����� �� ��� �������
			zero_imp_w(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		int check_condition = 0;
		white = find_data(start, from);
		char color = find_color(start, from);

		//�������� ����� �� 2 ���� � 1 �������
		if (first_element_touch(fet, l, r, color, from) == 0)
			;
		else if (first_element_touch(fet, l, r, color, from) == 1)
			fet++;
		else
		{
			zero_imp_w(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		//�������� ��������
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move() || out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1) {
			zero_imp_w(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))
		{
			;
		}
		else
		{
			zero_imp_w(start, to);
			printf("AI render\n");
			goto repeatt;
		}

		//����� �� ����� ����� ������ 2 ���� ��� 3 ��� ���������� �������
		if (l != r) {
			if (white != 0 && difference == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_l++;
			}
			if (white != 0 && difference == r && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
				double_difference_r++;
			}
		}
		if (l == r) {
			if (double_difference_l < 2) {
				if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
					double_difference_l++;
				}
			}
			else {
				if (double_difference_r < 2) {
					if (white != 0 && difference == l && r == l && (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from))) {
						double_difference_r++;
					}
				}
			}
		}
		//�������� ������������ ����
		if (white == 0 || !(difference == l || difference == r) || double_difference_l > 2 || double_difference_r > 2 || find_color(start, from) != truth_of_the_move()) {
			zero_imp_w(start, to);
			printf("AI render\n");
			goto repeatt;
		}
		if (find_color(start, to) == 'u' || find_color(start, to) == find_color(start, from)) {

			//�������� �� 6 � �����
			if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 0)
				;
			else if (out_rule(l, r, start, difference, from, double_difference_r, double_difference_l) == 1)
			{
				zero_imp_w(start, to);
				printf("AI render\n");
				goto repeatt;
			}
			else
			{
				minus(start, from);
				out_put();
				printf("\n\n\n");
				continue;
			}
			minus(start, from);
			plus(start, to, color);
			//�������� �� 6 ������, ����� ����� � ��������� ������
			if (consecutive_chip(start) == 1)
			{
				double_difference_r--;
				minus(start, to);
				plus(start, from, color);
				zero_imp_w(start, to);
				goto repeatt;
			}
			out_put();
			printf("\n\n\n");
		}
		else
		{
			printf("AI render\n");
			break;
		}
	}
}

void zero_imp(struct Node* start, int to)
{
	struct Node* temp = start;
	for (int i = 0; i < to; i++)
		temp = temp->link_next;
	temp->importance = 0;
}

void zero_imp_w(struct Node* start, int to)
{
	struct Node* temp = start;
	for (int i = 0; i < to; i++)
		temp = temp->link_next;
	temp->importance_w = 0;
}

int washing_chip(int to)
{
	int temp = 0;
	if (to <= 11)
		temp = 12 + to;
	else temp = to - 12;
	return temp;
}

void start_important_w(struct Node* start)
{
	struct Node* temp = start;
	start = start->link_next;
	start->importance_w = 0;
	for (int i = 0; i < 3; i++)
	{
		start->importance_w = 128;
		start = start->link_next;
	}
	start->importance_w = 96;
	start = start->link_next;
	for (int i = 0; i < 2; i++)
	{
		start->importance_w = 64;
		start = start->link_next;
	}
	for (int i = 0; i < 6; i++)
	{
		start->importance_w = 96;
		start = start->link_next;
	}
	for (int i = 0; i < 2; i++)
	{
		start->importance_w = 128;
		start = start->link_next;
	}
	start->importance_w = 64;
	start = start->link_next;
	for (int i = 0; i < 4; i++)
	{
		start->importance_w = 64;
		start = start->link_next;
	}
	start->importance_w = 128;
	start = start->link_next;
	for (int i = 0; i < 3; i++)
	{
		start->importance_w = 256;
		start = start->link_next;
	}
}

void start_important(struct Node* start)
{
	struct Node* temp = start;
	for (int i = 0; i < 3; i++)
	{
		start->importance = 64;
		start = start->link_next;
	}
	start->importance = 96;
	start = start->link_next;
	for (int i = 0; i < 2; i++)
	{
		start->importance = 128;
		start = start->link_next;
	}
	for (int i = 0; i < 6; i++)
	{
		start->importance = 256;
		start = start->link_next;
	}
	start->importance = 0;
	start = start->link_next;
	for (int i = 0; i < 2; i++)
	{
		start->importance = 32;
		start = start->link_next;
	}
	start->importance = 64;
	start = start->link_next;
	for (int i = 0; i < 4; i++)
	{
		start->importance = 128;
		start = start->link_next;
	}
	start->importance = 64;
	start = start->link_next;
	for (int i = 0; i < 3; i++)
	{
		start->importance = 64;
		start = start->link_next;
	}
}

void re_important(struct Node* start)
{
	struct Node* temp = start;
	for (int i = 0; i < 24; i++)
	{
		if (temp->color == 'w')
			temp->importance = 0;
		if (temp->color == 'b')
		{
			int up = temp->data;
			temp->importance = 64 - pow(2, up);
		}
		temp = temp->link_next;
	}
}

void re_important_w(struct Node* start)
{
	struct Node* temp = start;
	for (int i = 0; i < 24; i++)
	{
		if (temp->color == 'b')
			temp->importance_w = 0;
		if (temp->color == 'w')
		{
			int up = temp->data;
			temp->importance_w = 64 - pow(2, up);
		}
		temp = temp->link_next;
	}
}

void house_out(struct Node* start)
{
	struct Node* temp = start;
	temp->importance = 0;
	temp = temp->link_next;
	for (int i = 0; i < 5; i++)
	{
		temp->importance = 0;
		temp = temp->link_next;
	}
	for (int i = 0; i < 5; i++)
	{
		temp->importance = 128;
		temp = temp->link_next;
	}
	for (int i = 0; i < 12; i++)
	{
		temp->importance = 300;
		temp = temp->link_next;
	}
}

void move_el(int l, int r, struct Node* start, int mas[], int left_dif, int right_dif)
{
	int from, to, imp, from_tmp;
	from = to = imp = 0;
	struct Node* temp = start;
	struct Node* temp_last;
	for (int i = 0; i < 24; i++)
	{
		if (temp->color == 'b')
		{
			if (left_dif < 2 && right_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < l; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance;
				}
				temp_last = temp;
				for (int i = 0; i < r; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance;
				}
			}
			else if (left_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < l; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance;
				}
			}
			else if (right_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < r; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance;
				}
			}
		}
		temp = temp->link_next;
	}
	mas[0] = from;
	mas[1] = to;
	mas[2] = imp;
}

void move_el_w(int l, int r, struct Node* start, int mas[], int left_dif, int right_dif)
{
	int from, to, imp, from_tmp;
	from = to = imp = 0;
	struct Node* temp = start;
	struct Node* temp_last;
	for (int i = 0; i < 24; i++)
	{
		if (temp->color == 'w')
		{
			if (left_dif < 2 && right_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < l; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance_w > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance_w;
				}
				temp_last = temp;
				for (int i = 0; i < r; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance_w > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance_w;
				}
			}
			else if (left_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < l; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance_w > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance_w;
				}
			}
			else if (right_dif < 2)
			{
				temp_last = temp;
				from_tmp = temp_last->position;
				for (int i = 0; i < r; i++)
				{
					temp_last = temp_last->link_next;
				}
				if (temp_last->importance_w > imp)
				{
					from = from_tmp;
					to = temp_last->position;
					imp = temp_last->importance_w;
				}
			}
		}
		temp = temp->link_next;
	}
	mas[0] = from;
	mas[1] = to;
	mas[2] = imp;
}
// ������ ������ ������� ���������


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////               //////////////////////////////////////////
///////////////////////////////////////                     ///////////////////////////////////////
////////////////////////////////////                           ////////////////////////////////////
/////////////////////                                                         /////////////////////
/////////////////////                CREATED BY LARTAIN & MARI                /////////////////////
/////////////////////                CREATED BY LARTAIN & MARI                /////////////////////
/////////////////////                CREATED BY LARTAIN & MARI                /////////////////////
/////////////////////                                                         /////////////////////
////////////////////////////////////                           ////////////////////////////////////
///////////////////////////////////////                     ///////////////////////////////////////
//////////////////////////////////////////               //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

