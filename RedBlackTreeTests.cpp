
#include <iostream>
#include <cassert>
#include <random>
#include <stdexcept>
#include <climits>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Left Right
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// Right Right: mirror of Left Left.
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(15);
	rbt->Insert(30);
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;

	// Right Left: mirror of Left Right.
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree leftTree;
	leftTree.Insert(30);
	leftTree.Insert(15);
	leftTree.Insert(45);
	leftTree.Insert(10);
	assert(leftTree.ToPrefixString() == " B30  B15  R10  B45 ");
	assert(leftTree.Size() == 4);

	RedBlackTree rightTree;
	rightTree.Insert(30);
	rightTree.Insert(15);
	rightTree.Insert(45);
	rightTree.Insert(50);
	assert(rightTree.ToPrefixString() == " B30  B15  B45  R50 ");
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	RedBlackTree rbt2;
	rbt2.Insert(30);
	rbt2.Insert(15);
	rbt2.Insert(45);
	rbt2.Insert(40);
	rbt2.Insert(50);
	assert(rbt2.ToPrefixString() == " B30  B15  B45  R40  R50 ");
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}






void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(rbt->Contains(12));
	assert(rbt->Contains(40));
	assert(!rbt->Contains(0));
	assert(!rbt->Contains(30));
	assert(!rbt->Contains(100));
	delete rbt;

	
	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree rbt;
	bool threw = false;
	try {
		rbt.GetMin();
	} catch (const invalid_argument&) {
		threw = true;
	}
	assert(threw);

	threw = false;
	try {
		rbt.GetMax();
	} catch (const invalid_argument&) {
		threw = true;
	}
	assert(threw);

	rbt.Insert(0);
	assert(rbt.GetMin() == 0);
	assert(rbt.GetMax() == 0);
	rbt.Insert(INT_MIN);
	rbt.Insert(INT_MAX);
	rbt.Insert(-10);
	assert(rbt.GetMin() == INT_MIN);
	assert(rbt.GetMax() == INT_MAX);
	assert(rbt.Size() == 4);

	cout << "PASSED!" << endl << endl;
}





// Additional tests for the assignment's edge cases.
// Test-writing assistance: OpenAI Codex, 2026-11-08.
void TestDuplicatesAndSize(){
	cout << "Testing Duplicates and Size..." << endl;
	RedBlackTree rbt;
	assert(rbt.Size() == 0);
	assert(rbt.ToPrefixString() == "");
	assert(rbt.ToPostfixString() == "");
	rbt.Insert(20);
	rbt.Insert(10);
	rbt.Insert(30);
	string before = rbt.ToPrefixString();
	int duplicates[] = {20, 10, 30};
	for (int value : duplicates) {
		bool threw = false;
		try {
			rbt.Insert(value);
		} catch (const invalid_argument&) {
			threw = true;
		}
		assert(threw);
		assert(rbt.Size() == 3);
		assert(rbt.ToPrefixString() == before);
	}
	cout << "PASSED!" << endl << endl;
}

void TestCopyIndependence(){
	cout << "Testing Empty Copy and Independent Copies..." << endl;
	RedBlackTree empty;
	RedBlackTree emptyCopy(empty);
	assert(emptyCopy.Size() == 0);
	assert(emptyCopy.ToPrefixString() == "");
	emptyCopy.Insert(1);
	assert(empty.Size() == 0);

	RedBlackTree original;
	original.Insert(20);
	original.Insert(10);
	original.Insert(30);
	RedBlackTree copy(original);
	assert(copy.Size() == original.Size());
	assert(copy.ToInfixString() == original.ToInfixString());
	assert(copy.ToPostfixString() == original.ToPostfixString());
	copy.Insert(5);
	original.Insert(40);
	assert(!original.Contains(5));
	assert(!copy.Contains(40));
	assert(copy.Size() == 4);
	assert(original.Size() == 4);
	cout << "PASSED!" << endl << endl;
}

void TestOralExamples(){
	cout << "Testing Oral Question Examples..." << endl;
	RedBlackTree rbt;
	rbt.Insert(18);
	rbt.Insert(12);
	assert(rbt.ToPrefixString() == " B18  R12 ");
	rbt.Insert(7);
	assert(rbt.ToPrefixString() == " B12  R7  R18 ");

	RedBlackTree sixNodes;
	int values[] = {20, 10, 30, 5, 15, 25};
	for (int value : values) {
		sixNodes.Insert(value);
	}
	assert(sixNodes.ToPrefixString() == " B20  B10  R5  R15  B30  R25 ");
	cout << "PASSED!" << endl << endl;
}

void TestLargeTrees(){
	cout << "Testing 1000 Ascending and Descending Inserts..." << endl;
	RedBlackTree ascending;
	RedBlackTree descending;
	for (int i = 0; i < 1000; i++) {
		ascending.Insert(i);
		descending.Insert(999 - i);
	}
	assert(ascending.Size() == 1000);
	assert(descending.Size() == 1000);
	assert(ascending.GetMin() == 0);
	assert(ascending.GetMax() == 999);
	assert(descending.GetMin() == 0);
	assert(descending.GetMax() == 999);
	for (int i = 0; i < 1000; i++) {
		assert(ascending.Contains(i));
		assert(descending.Contains(i));
	}
	assert(!ascending.Contains(1000));
	assert(!descending.Contains(-1));
	cout << "PASSED!" << endl << endl;
}

int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestDuplicatesAndSize();
	TestCopyIndependence();
	TestOralExamples();
	TestLargeTrees();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
