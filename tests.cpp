/*
    Author: Pedro Pardo
    IDE: VsCode on MacOS


    This is a test file to check my BST with all the functions written.
*/

#include <gtest/gtest.h>
#include "priorityqueue.h"

TEST(priorityqueue, basicConstruct) {
    //test given to us byt the professor
    map<int, vector<int> > map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    EXPECT_EQ(pq.Size(), 9); //check size
    stringstream ss;
    for (auto e: map) {
        int priority = e.first;
        vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
            ss << priority << " value: " << values[j] << endl;
        }
    }
    EXPECT_EQ(pq.toString(), ss.str()); //checks string
    pq.clear();

   priorityqueue<int> pq1; //this is a test that works with regulat int values
    EXPECT_EQ(pq1.Size(), 0);
    pq1.enqueue(1, 15);
    pq1.enqueue(3, 5);
    pq1.enqueue(7, 6);
    pq1.enqueue(9, 9);
    pq1.enqueue(5, 10);
    pq1.enqueue(2, 1);
    pq1.enqueue(4, 1);
    pq1.enqueue(8, 4);
    EXPECT_EQ(pq1.Size(), 8);
    EXPECT_EQ(pq1.peek(), 2);
    // string str = pq1.toString();
    // cout << str << endl;
    pq1.clear(); //tests clear to see if everything resets
    EXPECT_EQ(pq1.Size(), 0);
    EXPECT_EQ(pq1.toString(), "");
     
    priorityqueue<string> pq2; //this test is used to check for strings with the PQ
    EXPECT_EQ(pq2.Size(), 0);
    pq2.enqueue("Pedro", 2);
    pq2.enqueue("Alex", 10);
    pq2.enqueue("Martin", 30);
    pq2.enqueue("Basim", 1);
    pq2.enqueue("Pablo", 7);
    pq2.enqueue("Juan", 31);
    pq2.enqueue("Fernando", 5);
    pq2.enqueue("Brenda", 90);
    pq2.enqueue("Oli", 69);
    pq2.enqueue("Daniel", 37);
    pq2.enqueue("David", 58);
    pq2.enqueue("Kate", 10);
    EXPECT_EQ(pq2.Size(), 12); //check size
    EXPECT_EQ(pq2.peek(), "Basim");
    // string str = pq2.toString();
    // cout << str << endl;
    pq2.clear(); //tests clear with string
    EXPECT_EQ(pq2.Size(), 0);
    EXPECT_EQ(pq2.toString(), "");

    priorityqueue<char> pq3; //test case for char values instead
    EXPECT_EQ(pq3.Size(), 0);
    pq3.enqueue('a', 1);
    pq3.enqueue('b', 2);
    pq3.enqueue('c', 3);
    pq3.enqueue('d', 4);
    pq3.enqueue('e', 5);
    pq3.enqueue('n', 6);
    pq3.enqueue('f', 7);
    pq3.enqueue('g', 8);
    pq3.enqueue('h', 9);
    pq3.enqueue('i', 10);
    EXPECT_EQ(pq3.Size(), 10);
    EXPECT_EQ(pq3.peek(), 'a');
    // str = pq4.toString();
    // cout << str << endl;
    pq3.clear(); //check for clearing the PQ
    EXPECT_EQ(pq3.Size(), 0);
    EXPECT_EQ(pq3.toString(), "");
    
}

TEST(priorityqueue, identicalcheck) {

    //testing on strings variables    
    // enqueued the same
    priorityqueue<string> s1;
    EXPECT_EQ(s1.Size(), 0);
    s1.enqueue("Pedro", 2);
    s1.enqueue("Alex", 10);
    s1.enqueue("Martin", 30);
    s1.enqueue("Basim", 1);
    s1.enqueue("Pablo", 7);
    s1.enqueue("Juan", 31);
    s1.enqueue("Fernando", 5);
    s1.enqueue("Brenda", 90);
    s1.enqueue("Oli", 69);
    s1.enqueue("Daniel", 37);
    s1.enqueue("David", 58);
    s1.enqueue("Kate", 10);
    EXPECT_EQ(s1.Size(), 12);
    EXPECT_EQ(s1.peek(), "Basim");

    priorityqueue<string> s2;
    EXPECT_EQ(s2.Size(), 0);
    s2.enqueue("Pedro", 2);
    s2.enqueue("Alex", 10);
    s2.enqueue("Martin", 30);
    s2.enqueue("Basim", 1);
    s2.enqueue("Pablo", 7);
    s2.enqueue("Juan", 31);
    s2.enqueue("Fernando", 5);
    s2.enqueue("Brenda", 90);
    s2.enqueue("Oli", 69);
    s2.enqueue("Daniel", 37);
    s2.enqueue("David", 58);
    s2.enqueue("Kate", 10);
    EXPECT_EQ(s2.Size(), 12);
    EXPECT_EQ(s2.peek(), "Basim");
    ASSERT_EQ(s1 == s2, true);
    
    // enqueued differently
    priorityqueue<string> s3;
    EXPECT_EQ(s3.Size(), 0);
    s3.enqueue("Pedro", 2);
    s3.enqueue("Alex", 10);
    s3.enqueue("Martin", 30);
    s3.enqueue("Basim", 1);
    s3.enqueue("Juan", 31);
    s3.enqueue("Fernando", 5);
    s3.enqueue("Brenda", 90);
    s3.enqueue("Oli", 69);
    s3.enqueue("Daniel", 37);
    s3.enqueue("David", 58);
    s3.enqueue("Kate", 10);
    s3.enqueue("Pablo", 7);
    EXPECT_EQ(s3.Size(), 12);
    EXPECT_EQ(s3.peek(), "Basim");
    ASSERT_EQ(s1 == s3, false);
    
    // empty one
    priorityqueue<string> s4;
    EXPECT_EQ(s4.Size(), 0);
    ASSERT_EQ(s4 == s2, false);
    
    // different sizes
    priorityqueue<string> s5;
    EXPECT_EQ(s5.Size(), 0);
    s5.enqueue("Pedro", 2);
    s5.enqueue("Alex", 10);
    s5.enqueue("Martin", 30);
    EXPECT_EQ(s5.Size(), 3);
    EXPECT_EQ(s5.peek(), "Pedro");
    ASSERT_EQ(s5 == s2, false);
    
    s1.clear(); s2.clear(); s3.clear(); s4.clear(); s5.clear();
    EXPECT_EQ(s1.Size(), 0);
    EXPECT_EQ(s2.Size(), 0);
    EXPECT_EQ(s2.Size(), 0);
    EXPECT_EQ(s3.Size(), 0);
    EXPECT_EQ(s4.Size(), 0);

    //this is a test on integer 
    priorityqueue<int> i1;
    EXPECT_EQ(i1.Size(), 0);
    i1.enqueue(1, 5);
    i1.enqueue(2, 4);
    i1.enqueue(2, 3);
    i1.enqueue(3, 4);
    i1.enqueue(4, 3);
    i1.enqueue(3, 2);
    i1.enqueue(4, 2);
    i1.enqueue(5, 1);
    EXPECT_EQ(i1.Size(), 8);
    EXPECT_EQ(i1.peek(), 5);

    priorityqueue<int> i2;
    EXPECT_EQ(i2.Size(), 0);
    i2.enqueue(1, 5);
    i2.enqueue(2, 4);
    i2.enqueue(2, 3);
    i2.enqueue(3, 4);
    i2.enqueue(4, 3);
    i2.enqueue(3, 2);
    i2.enqueue(4, 2);
    i2.enqueue(5, 1);
    EXPECT_EQ(i2.Size(), 8);
    EXPECT_EQ(i2.peek(), 5);
    ASSERT_EQ(i1 == i2, true); //checks if both identical
    
    // enqueued differently by one leaf node
    priorityqueue<int> i3;
    EXPECT_EQ(i3.Size(), 0);
    i3.enqueue(1, 2);
    i3.enqueue(2, 3);
    i3.enqueue(3, 4);
    i3.enqueue(4, 5);
    i3.enqueue(5, 6);
    i3.enqueue(6, 7);
    i3.enqueue(7, 8);
    i3.enqueue(8, 9);
    EXPECT_EQ(i3.Size(), 8);
    EXPECT_EQ(i3.peek(), 1);
    
    priorityqueue<int> i4;
    EXPECT_EQ(i4.Size(), 0);
    i4.enqueue(1, 2);
    i4.enqueue(2, 3);
    i4.enqueue(3, 4);
    i4.enqueue(4, 5);
    i4.enqueue(5, 6);
    i4.enqueue(8, 9);
    i4.enqueue(7, 8);
    i4.enqueue(6, 7);
    EXPECT_EQ(i4.Size(), 8);
    EXPECT_EQ(i4.peek(), 1);
    ASSERT_EQ(i3 == i4, false); //checks that they arent identical because of that one leaf node

    // different sizes
    priorityqueue<int> i5;
    EXPECT_EQ(i5.Size(), 0);
    i5.enqueue(1, 5);
    i5.enqueue(3, 2);
    i5.enqueue(7, 6);
    EXPECT_EQ(i5.Size(), 3);
    EXPECT_EQ(i5.peek(), 3);
    ASSERT_EQ(i5 == i4, false); //checks for trees of different sizes
    
    // empty test 
    priorityqueue<int> i6;
    EXPECT_EQ(i6.Size(), 0);
    ASSERT_EQ(i6 == i4, false); //checks for one empty and one is full

    i1.clear();i2.clear(); i3.clear(); i4.clear(); i5.clear(); i6.clear();

    //checks for trees of char values
    // enqueued the same
    priorityqueue<char> c1;
    EXPECT_EQ(c1.Size(), 0);
    c1.enqueue('a', 1);
    c1.enqueue('b', 2);
    c1.enqueue('c', 3);
    c1.enqueue('d', 4);
    c1.enqueue('e', 5);
    c1.enqueue('f', 6);
    c1.enqueue('g', 7);
    EXPECT_EQ(c1.Size(), 7);
    EXPECT_EQ(c1.peek(),'a');
    
    priorityqueue<char> c2;
    EXPECT_EQ(c2.Size(), 0);
    c2.enqueue('a', 1);
    c2.enqueue('b', 2);
    c2.enqueue('c', 3);
    c2.enqueue('d', 4);
    c2.enqueue('e', 5);
    c2.enqueue('f', 6);
    c2.enqueue('g', 7);
    EXPECT_EQ(c2.Size(), 7);
    EXPECT_EQ(c2.peek(),'a');
    ASSERT_EQ(c1 == c2, true); //checks if both are identical
    
    // enqueued differently
    priorityqueue<char> c3;
    EXPECT_EQ(c3.Size(), 0);
    c3.enqueue('a', 1);
    c3.enqueue('b', 2);
    c3.enqueue('c', 3);
    c3.enqueue('d', 4);
    c3.enqueue('g', 7);
    c3.enqueue('e', 5);
    c3.enqueue('f', 6);
    EXPECT_EQ(c3.Size(), 7);
    EXPECT_EQ(c2.peek(),'a');
    ASSERT_EQ(c2 == c3, false);
    
    // empty one
    priorityqueue<char> c4;
    EXPECT_EQ(c4.Size(), 0);
    ASSERT_EQ(c4 == c3, false);
    
    // different sizes
    priorityqueue<char> c5;
    EXPECT_EQ(c5.Size(), 0);
    c5.enqueue('a', 1);
    c5.enqueue('b', 2);
    c5.enqueue('c', 3);
    c5.enqueue('d', 4);
    EXPECT_EQ(c5.Size(), 4);
    EXPECT_EQ(c5.peek(),'a');
    ASSERT_EQ(c5 == c3, false);
    
    c1.clear(); c2.clear(); c3.clear(); c4.clear(); c5.clear();
    EXPECT_EQ(c1.Size(), 0);
    EXPECT_EQ(c2.Size(), 0);
    EXPECT_EQ(c3.Size(), 0);
    EXPECT_EQ(c4.Size(), 0);
    EXPECT_EQ(c5.Size(), 0);
    
    //tests on bool types as values
    // enqueued the same
    priorityqueue<bool> b1;
    EXPECT_EQ(b1.Size(), 0);
    b1.enqueue(false, 1);
    b1.enqueue(true, 2);
    b1.enqueue(false, 3);
    b1.enqueue(true, 4);
    b1.enqueue(false, 5);
    b1.enqueue(true, 6);
    EXPECT_EQ(b1.Size(), 6);
    EXPECT_EQ(b1.peek(), false);
    
    priorityqueue<bool> b2;
    EXPECT_EQ(b2.Size(), 0);
    b2.enqueue(false, 1);
    b2.enqueue(true, 2);
    b2.enqueue(false, 3);
    b2.enqueue(true, 4);
    b2.enqueue(false, 5);
    b2.enqueue(true, 6);
    EXPECT_EQ(b2.Size(), 6);
    EXPECT_EQ(b2.peek(), false);
    ASSERT_EQ(b1 == b2, true);
    
    // enqueued differently
    priorityqueue<bool> b3;
    EXPECT_EQ(b3.Size(), 0);
    b3.enqueue(true, 3);
    b3.enqueue(true, 7);
    b3.enqueue(false, 5);
    b3.enqueue(true, 2);
    b3.enqueue(false, 2);
    b3.enqueue(false, 2);
    EXPECT_EQ(b3.Size(), 6);
    EXPECT_EQ(b3.peek(), true);
    ASSERT_EQ(b2 == b3, false);
    
    // empty one
    priorityqueue<bool> b4;
    EXPECT_EQ(b4.Size(), 0);
    ASSERT_EQ(b4 == b3, false);
    
    // different sizes
    priorityqueue<bool> b5;
    EXPECT_EQ(b5.Size(), 0);
    b5.enqueue(false, 3);
    b5.enqueue(true, 7);
    b5.enqueue(false, 5);
    b5.enqueue(true, 2);
    EXPECT_EQ(b5.Size(), 4);
    EXPECT_EQ(b5.peek(), true);
    ASSERT_EQ(b5 == b3, false);
    
    b1.clear(); b2.clear(); b3.clear(); b4.clear(); b5.clear();
    EXPECT_EQ(b1.Size(), 0);
    EXPECT_EQ(b2.Size(), 0);
    EXPECT_EQ(b3.Size(), 0);
    EXPECT_EQ(b4.Size(), 0);
    EXPECT_EQ(b5.Size(), 0);
}

TEST(priorityqueue, equalcheck) {
    //this tests all the equals operators we had to create
    priorityqueue<int> int1; //creates the first int PQ
    EXPECT_EQ(int1.Size(), 0);
    int1.enqueue(1, 2);
    int1.enqueue(2, 1);
    int1.enqueue(1, 2);
    int1.enqueue(2, 1);
    int1.enqueue(1, 2);
    int1.enqueue(2, 1);
    EXPECT_EQ(int1.Size(), 6);
    EXPECT_EQ(int1.peek(), 2);
    
    priorityqueue<int> int2; //creates the second int PQ 
    EXPECT_EQ(int2.Size(), 0);
    int2.enqueue(3, 4);
    int2.enqueue(4, 3);
    int2.enqueue(3, 4);
    int2.enqueue(4, 3);
    EXPECT_EQ(int2.Size(), 4);
    EXPECT_EQ(int2.peek(), 4);

    // string str = int2.toString();
    // cout << str << endl;

    int2 = int1;//copies over the first PQ to the second

    EXPECT_EQ(int2.Size(), 6);//tests to see if the size is correct after copying

    int1.clear();int2.clear();

    // string str2 = int2.toString();
    // cout << str2 << endl;

    //this is for testing with strings in the PQ
    priorityqueue<string> s1; //created the first string PQ
    EXPECT_EQ(s1.Size(), 0);
    s1.enqueue("Pedro", 2);
    s1.enqueue("Alex", 10);
    s1.enqueue("Martin", 30);
    s1.enqueue("Basim", 1);
    EXPECT_EQ(s1.Size(), 4);
    EXPECT_EQ(s1.peek(), "Basim");
    
    priorityqueue<string> s2; //created the second string PQ
    EXPECT_EQ(s2.Size(), 0);
    s2.enqueue("Pedro", 2);
    s2.enqueue("Alex", 10);
    s2.enqueue("Martin", 30);
    s2.enqueue("Basim", 1);
    s2.enqueue("Pablo", 7);
    s2.enqueue("Juan", 31);
    s2.enqueue("Fernando", 5);
    s2.enqueue("Brenda", 90);
    s2.enqueue("Oli", 69);
    s2.enqueue("Daniel", 37);
    s2.enqueue("David", 58);
    s2.enqueue("Kate", 10);
    EXPECT_EQ(s2.Size(), 12);
    EXPECT_EQ(s2.peek(), "Basim");

    // str = s2.toString();
    //cout << str << endl;

    s2 = s1; //copies over s1 to s2

    EXPECT_EQ(s2.Size(), 4); //checks if the size is correct after copying
    EXPECT_EQ(s2.peek(), "Basim");
    s1.clear(); s2.clear();

    //this is used to check for chars as the PQ value
    priorityqueue<char> c1; //created the first PQ of chars
    EXPECT_EQ(c1.Size(), 0);
    c1.enqueue('a', 1);
    c1.enqueue('b', 2);
    c1.enqueue('c', 3);
    c1.enqueue('d', 4);
    EXPECT_EQ(c1.Size(), 4);
    EXPECT_EQ(c1.peek(), 'a');
    
    priorityqueue<char> c2; //created the second PQ of chars
    EXPECT_EQ(c2.Size(), 0);
    c2.enqueue('e', 5);
    c2.enqueue('n', 6);
    c2.enqueue('f', 7);
    c2.enqueue('g', 8);
    c2.enqueue('h', 9);
    c2.enqueue('i', 10);
    EXPECT_EQ(c2.Size(), 6);
    EXPECT_EQ(c2.peek(), 'e');

    c2 = c1;//copies over c1 to c2

    EXPECT_EQ(c2.Size(), 4); //checks for new size
    EXPECT_EQ(c2.peek(), 'a');

    c1.clear();c2.clear();
}




