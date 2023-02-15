#include <gtest/gtest.h>
#include "priorityqueue.h"

TEST(priorityqueue, enqueueNoDuplicate) {
    priorityqueue<string> pq;
    pq.enqueue("Clayton", 5);
    pq.enqueue("Zain", 4);
    pq.enqueue("Alex", 3);
    pq.enqueue("Christian", 6);
    pq.enqueue("Steven", 7);
    pq.enqueue("Dalton", 8);
    pq.enqueue("Ian", 10);
    pq.enqueue("Nathaniel", 123);
    pq.enqueue("Mohammed", 54);
    pq.enqueue("Adam", 88);
    string pqStr = "3 value: Alex\n"
    			   "4 value: Zain\n"
    			   "5 value: Clayton\n"
    			   "6 value: Christian\n"
    			   "7 value: Steven\n"
    			   "8 value: Dalton\n"
    			   "10 value: Ian\n"
    			   "54 value: Mohammed\n"
    			   "88 value: Adam\n"
    			   "123 value: Nathaniel\n";
	ASSERT_EQ(pqStr, pq.toString());
    ASSERT_EQ(pq.Size(), 10);
    
    priorityqueue<string> pqT;
    pqT.enqueue("Hey", 5);
    pqT.enqueue("What", 4);
    pqT.enqueue("Do", 3);
    pqT.enqueue("You", 6);
    pqT.enqueue("Know", 7);
    pqT.enqueue("Fool", 8);
    ASSERT_EQ(pqT.Size(), 6);
    
    pqT = pq;
    pq.clear();
    ASSERT_EQ(pq.Size(), 0);
    
    ASSERT_EQ(pqStr, pqT.toString());
    ASSERT_EQ(pqT.Size(), 10);
    
    pqT.clear();
    ASSERT_EQ(pqT.Size(), 0);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<int> pq1;
    pq1.enqueue(1, 5);
    pq1.enqueue(2, 4);
    pq1.enqueue(3, 3);
    pq1.enqueue(4, 6);
    pq1.enqueue(5, 7);
    pq1.enqueue(6, 8);
    pq1.enqueue(7, 10);
    pq1.enqueue(8, 123);
    pq1.enqueue(9, 54);
    pq1.enqueue(10, 88);
    ASSERT_EQ(pq1.Size(), 10);
    string pq1Str = "3 value: 3\n"
					"4 value: 2\n"
					"5 value: 1\n"
					"6 value: 4\n"
					"7 value: 5\n"
					"8 value: 6\n"
					"10 value: 7\n"
					"54 value: 9\n"
					"88 value: 10\n"
					"123 value: 8\n";
    ASSERT_EQ(pq1Str, pq1.toString());
    pq1.clear();
    ASSERT_EQ(pq1.Size(), 0);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<double> pq2;
    pq2.enqueue(1.0, 5);
    pq2.enqueue(2.1, 4);
    pq2.enqueue(3.2, 3);
    pq2.enqueue(4.5, 6);
    pq2.enqueue(5.43, 7);
    pq2.enqueue(6.31, 8);
    pq2.enqueue(7.190, 10);
    pq2.enqueue(8.0, 123);
    pq2.enqueue(9.9, 54);
    pq2.enqueue(10.1293, 88);
    ASSERT_EQ(pq2.Size(), 10);
    string pq2Str = "3 value: 3.2\n"
					"4 value: 2.1\n"
					"5 value: 1\n"
					"6 value: 4.5\n"
					"7 value: 5.43\n"
					"8 value: 6.31\n"
					"10 value: 7.19\n"
					"54 value: 9.9\n"
					"88 value: 10.1293\n"
					"123 value: 8\n";
    ASSERT_EQ(pq2Str, pq2.toString());
    pq2.clear();
    ASSERT_EQ(pq2.Size(), 0);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<char> pq3;
    pq3.enqueue('Z', 5);
    pq3.enqueue('z', 4);
    pq3.enqueue('c', 3);
    pq3.enqueue('a', 6);
    pq3.enqueue('s', 7);
    pq3.enqueue('t', 8);
    pq3.enqueue('b', 10);
    pq3.enqueue('k', 123);
    pq3.enqueue('p', 54);
    pq3.enqueue('w', 88);
    ASSERT_EQ(pq3.Size(), 10);
    string pq3Str = "3 value: c\n"
					"4 value: z\n"
					"5 value: Z\n"
					"6 value: a\n"
					"7 value: s\n"
					"8 value: t\n"
					"10 value: b\n"
					"54 value: p\n"
					"88 value: w\n"
					"123 value: k\n";
    ASSERT_EQ(pq3Str, pq3.toString());
    pq3.clear();
}


TEST(priorityqueue, beginAndNext) {
	priorityqueue<string> pq;
    pq.enqueue("Clayton", 5);
    pq.enqueue("Zain", 4);
    pq.enqueue("Alex", 3);
    pq.enqueue("Christian", 5);
    pq.enqueue("Steven", 7);
    pq.enqueue("Dalton", 8);
    pq.enqueue("Ian", 10);
    pq.enqueue("Nathaniel", 123);
    pq.enqueue("Mohammed", 4);
    pq.enqueue("Adam", 4);
    ASSERT_EQ(pq.Size(), 10);
    string pqStr = "3 value: Alex\n"
				   "4 value: Zain\n"
				   "4 value: Mohammed\n"
				   "4 value: Adam\n"
				   "5 value: Clayton\n"
				   "5 value: Christian\n"
				   "7 value: Steven\n"
				   "8 value: Dalton\n"
				   "10 value: Ian\n"
				   "123 value: Nathaniel\n";
    
    pq.begin();
    
    string value;
    int priority;
    
    while (pq.next(value, priority)) {
    	cout << priority << " value: " << value << endl;
    }
    cout << priority << " value: " << value << endl;
    
    pq.clear();
    
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<int> pq1;
    pq1.enqueue(1, 5);
    pq1.enqueue(2, 4);
    pq1.enqueue(3, 3);
    pq1.enqueue(4, 6);
    pq1.enqueue(5, 6);
    pq1.enqueue(6, 8);
    pq1.enqueue(7, 10);
    pq1.enqueue(8, 123);
    pq1.enqueue(9, 54);
    pq1.enqueue(10, 5);
    ASSERT_EQ(pq1.Size(), 10);
    pq1.begin();
    int value1;
    while (pq1.next(value1, priority)) {
    	cout << priority << " value: " << value1 << endl;
    }
    cout << priority << " value: " << value1 << endl;
    pq1.clear();
    
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<double> pq2;
    pq2.enqueue(1.0, 6);
    pq2.enqueue(2.1, 4);
    pq2.enqueue(3.2, 3);
    pq2.enqueue(4.5, 6);
    pq2.enqueue(5.43, 7);
    pq2.enqueue(6.31, 8);
    pq2.enqueue(7.190, 10);
    pq2.enqueue(8.0, 6);
    pq2.enqueue(9.9, 54);
    pq2.enqueue(10.1293, 88);
    ASSERT_EQ(pq2.Size(), 10);
    pq2.begin();
    double value2;
    while (pq2.next(value2, priority)) {
    	cout << priority << " value: " << value2 << endl;
    }
    cout << priority << " value: " << value2 << endl;
    pq2.clear();
    
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<char> pq3;
    pq3.enqueue('Z', 3);
    pq3.enqueue('z', 3);
    pq3.enqueue('c', 3);
    pq3.enqueue('a', 3);
    pq3.enqueue('s', 3);
    pq3.enqueue('t', 3);
    pq3.enqueue('b', 3);
    pq3.enqueue('k', 3);
    pq3.enqueue('p', 3);
    pq3.enqueue('w', 3);
    ASSERT_EQ(pq3.Size(), 10);
    pq3.begin();
    
    char value3;
    while (pq3.next(value3, priority)) {
    	cout << priority << " value: " << value3 << endl;
    }
    cout << priority << " value: " << value3 << endl;
    pq3.clear();
}

TEST(priorityqueue, dequeueAndPeek) {
	priorityqueue<string> pq;
    pq.enqueue("Clayton", 6);
    pq.enqueue("Zain", 4);
    pq.enqueue("Alex", 3);
    pq.enqueue("Chris", 8);
    pq.enqueue("Bob", 7);
    pq.enqueue("Arcane", 10);
    pq.enqueue("Double", 10);
    
    cout << "Peek: " << pq.peek() << endl;
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    
    pq.dequeue();
    cout << "Peek: " << pq.peek() << endl;
    cout << "Peek: " << pq.peek() << endl;
    cout << "Peek: " << pq.peek() << endl;
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    
    pq.dequeue();
    cout << pq.toString();
    cout << pq.Size() << endl<< endl;
    ASSERT_EQ(pq.Size(), 0);
    
    pq.clear();
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<int> pq1;
    pq1.enqueue(1, 6);
    pq1.enqueue(2, 4);
    pq1.enqueue(3, 3);
    pq1.enqueue(4, 8);
    pq1.enqueue(5, 7);
    
    
    cout << "Peek: " << pq1.peek() << endl;
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    
    pq1.dequeue();
    cout << "Peek: " << pq1.peek() << endl;
    cout << "Peek: " << pq1.peek() << endl;
    cout << "Peek: " << pq1.peek() << endl;
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    pq1.dequeue();
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    pq1.dequeue();
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    pq1.dequeue();
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    pq1.dequeue();
    //cout << pq1.toString();
    cout << pq1.Size() << endl<< endl;
    
    ASSERT_EQ(pq1.Size(), 0);
    
    pq1.clear();
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<char> pq2;
    pq2.enqueue('a', 6);
    pq2.enqueue('b', 4);
    pq2.enqueue('c', 3);
    pq2.enqueue('d', 8);
    pq2.enqueue('e', 7);
    
    cout << "Peek: " << pq2.peek() << endl;
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    
    pq2.dequeue();
    cout << "Peek: " << pq2.peek() << endl;
    cout << "Peek: " << pq2.peek() << endl;
    cout << "Peek: " << pq2.peek() << endl;
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    pq2.dequeue();
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    pq2.dequeue();
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    pq2.dequeue();
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    pq2.dequeue();
    //cout << pq2.toString();
    cout << pq2.Size() << endl<< endl;
    
    ASSERT_EQ(pq2.Size(), 0);
    
    pq2.clear();
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<double> pq3;
    pq3.enqueue(1.1, 6);
    pq3.enqueue(2.3, 4);
    pq3.enqueue(4.3, 3);
    pq3.enqueue(8.67, 8);
    pq3.enqueue(34.2, 7);
    
    cout << "Peek: " << pq3.peek() << endl;
    //cout << pq3.toString();
    cout << pq3.Size() << endl<< endl;
    
    
    pq3.dequeue();
    cout << "Peek: " << pq3.peek() << endl;
    cout << "Peek: " << pq3.peek() << endl;
    cout << "Peek: " << pq3.peek() << endl;
    //cout << pq3.toString();
    cout << pq3.Size() << endl<< endl;
    
    pq3.dequeue();
    //cout << pq3Str.toString();
    cout << pq3.Size() << endl<< endl;
    
    pq3.dequeue();
    //cout << pq3.toString();
    cout << pq3.Size() << endl<< endl;
    
    pq3.dequeue();
    //cout << pq3.toString();
    cout << pq3.Size() << endl<< endl;
    
    pq3.dequeue();
    //cout << pq3.toString();
    cout << pq3.Size() << endl<< endl;
    
    ASSERT_EQ(pq3.Size(), 0);
    
    pq3.clear();
    
}

TEST(priorityqueue, equalityOperator) {
	priorityqueue<string> pq;
    pq.enqueue("Clayton", 6);
    pq.enqueue("Zain", 4);
    pq.enqueue("Alex", 3);
    pq.enqueue("Chris", 8);
    pq.enqueue("Bob", 7);
    pq.enqueue("Arcane", 10);
    pq.enqueue("Double", 10);
    
    priorityqueue<string> pq1;
    pq1.enqueue("Clayton", 6);
    pq1.enqueue("Zain", 4);
    pq1.enqueue("Alex", 3);
    pq1.enqueue("Chris", 8);
    pq1.enqueue("Bob", 7);
    pq1.enqueue("Arcane", 10);
    pq1.enqueue("Double", 10);
    
    ASSERT_EQ(pq, pq1);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<int> pq2;
    pq2.enqueue(1, 6);
    pq2.enqueue(2, 4);
    pq2.enqueue(3, 3);
    pq2.enqueue(4, 8);
    pq2.enqueue(5, 7);
    pq2.enqueue(6, 10);
    pq2.enqueue(7, 10);
    
    priorityqueue<int> pq3;
    pq3.enqueue(1, 6);
    pq3.enqueue(2, 4);
    pq3.enqueue(3, 3);
    pq3.enqueue(4, 8);
    pq3.enqueue(5, 7);
    pq3.enqueue(6, 10);
    pq3.enqueue(7, 10);
    
    ASSERT_EQ(pq2, pq3);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<char> pq4;
    pq4.enqueue('c', 6);
    pq4.enqueue('a', 4);
    pq4.enqueue('h', 3);
    pq4.enqueue('s', 8);
    pq4.enqueue('u', 7);
    pq4.enqueue('o', 10);
    pq4.enqueue('p', 10);
    
    priorityqueue<char> pq5;
    pq5.enqueue('c', 6);
    pq5.enqueue('a', 4);
    pq5.enqueue('h', 3);
    pq5.enqueue('s', 8);
    pq5.enqueue('u', 7);
    pq5.enqueue('o', 10);
    pq5.enqueue('p', 10);
    
    ASSERT_EQ(pq4, pq5);
    ///////////////////////////////////////////////////////////////////////////
    priorityqueue<double> pq6;
    pq6.enqueue(1.2, 6);
    pq6.enqueue(.43, 4);
    pq6.enqueue(6.3, 3);
    pq6.enqueue(.100, 8);
    pq6.enqueue(-1.1, 7);
    pq6.enqueue(593.2, 10);
    pq6.enqueue(48939.2, 10);
    
    priorityqueue<double> pq7;
    pq7.enqueue(1.2, 6);
    pq7.enqueue(.43, 4);
    pq7.enqueue(6.3, 3);
    pq7.enqueue(.100, 8);
    pq7.enqueue(-1.1, 7);
    pq7.enqueue(593.2, 10);
    pq7.enqueue(48939.2, 10);
    
    ASSERT_EQ(pq6, pq7);
}
// TO DO: write lots of tests here.
