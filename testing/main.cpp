#include "./std_lib_facilities.h"

vector<int> numbers;
int num;
int temp_num;
int number_to_sum;
double result = 0;


int main(){
    cout << "Please enter the number of integers to sum.\n";
    cin >> number_to_sum;

    cout << "Please enter some integers (pres '|' to stop):\n";
    while(cin >> num) {
        numbers.push_back(num);
    }

    if (numbers.size() < number_to_sum) error("You did not write enothe numbers to sum.\n");

	std::cout << num << "\n";

    for (int i = 0; i < number_to_sum; i++) {
        result += numbers[i];
        cout << "Fuck";
    }
    cout << "The sum of the first " << number_to_sum << " numbers (";

	std::cout << num << "\n";
    
    for (int k = 0; k < number_to_sum; k++) {
        cout << ' ' << numbers[k] << k;
    }

    cout << "is " << result << '\n';



}