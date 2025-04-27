#include <QLibrary/MyArray.h>
#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::min_element, std::max_element

// Function to print MyArray
void PrintMyArray(const MyArray& arr, const std::string& msg = "") {
    if (!msg.empty()) {
        std::cout << msg << ": ";
    }
    for (unsigned long i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Function to compare MyArray with a vector
bool CompareWithVector(const MyArray& arr, const std::vector<double>& vec) {
    if (arr.size() != vec.size()) {
        return false;
    }
    for (unsigned long i = 0; i < arr.size(); ++i) {
        if (arr[i] != vec[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // 1. Constructor Tests
    std::cout << "1. Constructor Tests\n";
    MyArray arr1(5);
    PrintMyArray(arr1, "arr1 (size 5)"); // Check default constructor
    std::vector<double> expected1(5, 0.0);
    if (CompareWithVector(arr1, expected1)) {
        std::cout << "  PASS: Default constructor\n";
    } else {
        std::cout << "  FAIL: Default constructor\n";
    }

    MyArray arr2(arr1); // Copy constructor
    PrintMyArray(arr2, "arr2 (copy of arr1)");
    if (CompareWithVector(arr2, expected1)) {
        std::cout << "  PASS: Copy constructor\n";
    } else {
        std::cout << "  FAIL: Copy constructor\n";
    }

    MyArray arr3;  //test empty constructor
    PrintMyArray(arr3, "arr3 (empty)");
    if(arr3.size() == 0){
        std::cout << "  PASS: Empty constructor\n";
    }
    else{
        std::cout << "  FAIL: Empty constructor\n";
    }
    

    // 2. Assignment Operator Tests
    std::cout << "\n2. Assignment Operator Tests\n";
    MyArray arr4(3);
    arr4 = 5.0; // Assign a scalar value
    PrintMyArray(arr4, "arr4 (= 5.0)");
    std::vector<double> expected4(3, 5.0);
    if (CompareWithVector(arr4, expected4)) {
        std::cout << "  PASS: Scalar assignment\n";
    } else {
        std::cout << "  FAIL: Scalar assignment\n";
    }

    MyArray arr5(4);
    arr5 = arr1; // Assign one MyArray to another
    PrintMyArray(arr5, "arr5 (= arr1)");
    if (CompareWithVector(arr5, expected1)) {
        std::cout << "  PASS: MyArray assignment\n";
    } else {
        std::cout << "  FAIL: MyArray assignment\n";
    }

     MyArray arr6(10);
    arr6 = arr5; // Assign a smaller array to a larger one
    PrintMyArray(arr6, "arr6 (= arr5)");
    if (CompareWithVector(arr6, expected1)) {
        std::cout << "  PASS: Smaller to larger assignment\n";
    } else {
        std::cout << "  FAIL: Smaller to larger assignment\n";
    }

    // 3. Arithmetic Operator Tests
    std::cout << "\n3. Arithmetic Operator Tests\n";
    MyArray a(2);
    a = 2.0;
    MyArray b(2);
    b = 3.0;

    MyArray c = a;
    c += b;
    PrintMyArray(c, "c (a += b)");
    std::vector<double> expected_add(2, 5.0);
     if (CompareWithVector(c, expected_add)) {
        std::cout << "  PASS: operator+=\n";
    } else {
        std::cout << "  FAIL: operator+=\n";
    }

    MyArray d = a;
    d += 1.0;
    PrintMyArray(d, "d (a += 1.0)");
    std::vector<double> expected_add_scalar(2, 3.0);
    if (CompareWithVector(d, expected_add_scalar))
    {
        std::cout << "  PASS: operator+= scalar\n";
    }
    else{
        std::cout << "  FAIL: operator+= scalar\n";
    }

    MyArray e = a;
    e -= b;
    PrintMyArray(e, "e (a -= b)");
    std::vector<double> expected_sub(2, -1.0);
    if (CompareWithVector(e, expected_sub)) {
        std::cout << "  PASS: operator-=\n";
    } else {
        std::cout << "  FAIL: operator-=\n";
    }

    MyArray f = a;
    f -= 1.0;
    PrintMyArray(f, "f (a -= 1.0)");
     std::vector<double> expected_sub_scalar(2, 1.0);
    if (CompareWithVector(f, expected_sub_scalar))
    {
        std::cout << "  PASS: operator-= scalar\n";
    }
    else{
        std::cout << "  FAIL: operator-= scalar\n";
    }

    MyArray g = a;
    g *= b;
    PrintMyArray(g, "g (a *= b)");
    std::vector<double> expected_mul(2, 6.0);
    if (CompareWithVector(g, expected_mul)) {
        std::cout << "  PASS: operator*=\n";
    } else {
        std::cout << "  FAIL: operator*=\n";
    }

    MyArray h = a;
    h *= 2.0;
    PrintMyArray(h, "h (a *= 2.0)");
    std::vector<double> expected_mul_scalar(2, 4.0);
     if (CompareWithVector(h, expected_mul_scalar))
    {
        std::cout << "  PASS: operator*= scalar\n";
    }
    else{
        std::cout << "  FAIL: operator*= scalar\n";
    }

    MyArray j = a;
    j /= b;
    PrintMyArray(j, "j (a /= b)");
    std::vector<double> expected_div(2, 2.0/3.0);
    if (CompareWithVector(j, expected_div)) {
        std::cout << "  PASS: operator/=\n";
    } else {
        std::cout << "  FAIL: operator/=\n";
    }

    MyArray k = a;
    k /= 2.0;
    PrintMyArray(k, "k (a /= 2.0)");
    std::vector<double> expected_div_scalar(2, 1.0);
    if (CompareWithVector(k, expected_div_scalar))
    {
        std::cout << "  PASS: operator/= scalar\n";
    }
    else{
        std::cout << "  FAIL: operator/= scalar\n";
    }

    // 4. apply() test
    std::cout << "\n4. apply() test\n";
    MyArray arr7(3);
    arr7 = 1.0;
    MyArray arr8 = arr7.apply([](double x) { return x * 2; });
    PrintMyArray(arr8, "arr8 (arr7.apply(*2))");
    std::vector<double> expected8(3, 2.0);
    if (CompareWithVector(arr8, expected8)) {
        std::cout << "  PASS: apply()\n";
    } else {
        std::cout << "  FAIL: apply()\n";
    }

    // 5. resize() test
    std::cout << "\n5. resize() test\n";
    MyArray arr9(2);
    arr9 = 1.0;
    arr9.resize(5);
    PrintMyArray(arr9, "arr9.resize(5)");
    std::vector<double> expected9(5, 0.0);  // resize does not preserve data
    if(arr9.size() == 5)
    {
         std::cout << "  PASS: resize() size check\n";
    }
    else{
        std::cout << "  FAIL: resize() size check\n";
    }
   
    arr9.resize(1);
    PrintMyArray(arr9, "arr9.resize(1)");
     if(arr9.size() == 1)
    {
         std::cout << "  PASS: resize() size check 2\n";
    }
    else{
        std::cout << "  FAIL: resize() size check 2\n";
    }

    // 6. sum() test
     std::cout << "\n6. sum() test\n";
    MyArray arr10(3);
    arr10 = 1.0;
    arr10[1] = 2.0;
    arr10[2] = 3.0;
    double sum_result = arr10.sum();
    std::cout << "Sum of arr10: " << sum_result << std::endl;
    if (sum_result == 6.0) {
        std::cout << "  PASS: sum()\n";
    } else {
        std::cout << "  FAIL: sum()\n";
    }

    // 7. min() and max() tests
    std::cout << "\n7. min() and max() tests\n";
    MyArray arr11(5);
    arr11[0] = 3.0;
    arr11[1] = 1.0;
    arr11[2] = 4.0;
    arr11[3] = 1.0;
    arr11[4] = 5.0;
    double min_val = arr11.min();
    double max_val = arr11.max();
    std::cout << "Min of arr11: " << min_val << ", Max of arr11: " << max_val << std::endl;
    if (min_val == 1.0 && max_val == 5.0) {
        std::cout << "  PASS: min() and max()\n";
    } else {
        std::cout << "  FAIL: min() and max()\n";
    }

    MyArray empty_arr;
    try {
        empty_arr.min(); // Should throw an exception
        std::cout << "  FAIL: min() on empty array\n";
    } catch (const std::exception& e) {
        std::cout << "  PASS: min() on empty array: Threw exception: " << e.what() << "\n";
    }

     try {
        empty_arr.max(); // Should throw an exception
        std::cout << "  FAIL: max() on empty array\n";
    } catch (const std::exception& e) {
        std::cout << "  PASS: max() on empty array: Threw exception: " << e.what() << "\n";
    }

    // 8. out of bounds access
    std::cout << "\n8. out of bounds access\n";
     MyArray arr12(1);
    try {
        arr12[10];
        std::cout << "  FAIL: Out of bounds access\n";
    } catch (const std::out_of_range& e) {
        std::cout << "  PASS: Out of bounds access const: Threw exception: " << e.what() << "\n";
    }

    try {
        arr12[10] = 5.0;
        std::cout << "  FAIL: Out of bounds write\n";
    } catch (const std::out_of_range& e) {
        std::cout << "  PASS: Out of bounds write non-const: Threw exception: " << e.what() << "\n";
    }

    return 0;
}

