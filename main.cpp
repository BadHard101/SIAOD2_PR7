#include <iostream>
#include <vector>
#define MAX_INT 9999
using namespace std;

int linear_itters_counter = 0;
int dynamic_itters_counter = 0;

int ceilIndex(int subsequence[],
              int startLeft,
              int startRight,
              int key){

    int mid = 0;
    int left = startLeft;
    int right = startRight;
    int ceilIndex = 0;
    bool ceilIndexFound = false;

    for (mid = (left + right) / 2; left <= right && !ceilIndexFound; mid = (left + right) / 2) {
        dynamic_itters_counter++;

        if (subsequence[mid] > key) {
            right = mid - 1;
        }
        else if (subsequence[mid] == key) {
            ceilIndex = mid;
            ceilIndexFound = true;
        }
        else if (mid + 1 <= right && subsequence[mid + 1] >= key) {
            subsequence[mid + 1] = key;
            ceilIndex = mid + 1;
            ceilIndexFound = true;
        } else {
            left = mid + 1;
        }
    }

    if (!ceilIndexFound) {
        if (mid == left) {
            subsequence[mid] = key;
            ceilIndex = mid;
        }
        else {
            subsequence[mid + 1] = key;
            ceilIndex = mid + 1;
        }
    }

    return ceilIndex;
}

void makingResultSubsequence(vector<int> numbers, int subsequence[], int indexes[]) {

    int subsequence_index = -1;
    for (int i = 0; i < numbers.size(); ++i) {
        if (subsequence[i]!=MAX_INT)
            subsequence_index++;
        else
            break;
    }

    bool flag = false;
    vector<int> result_subsequence;
    for (int i = numbers.size() - 1; i >= 0; i--) {

        if (flag) {
            if ((indexes[i] == subsequence_index) &&
                (numbers.at(i) < result_subsequence.back()) ){
                result_subsequence.push_back(numbers.at(i));
                subsequence_index--;
            }
        } else { // первый раз
            if (indexes[i] == subsequence_index) {
                result_subsequence.push_back(numbers.at(i));
                subsequence_index--;
                flag = true;
            }
        }
        if (subsequence_index == -1)
            break;
    }

    cout << "The found increasing sequence with DYNAMIC operations: ";
    for (int i = result_subsequence.size() - 1; i >= 0; i--) {
        cout << result_subsequence.at(i) << " ";
    }
    cout << endl;

}

int longestIncreasingSubsequenceLength(vector<int> numbers) {

    if (numbers.size() <= 1) {
        return 1;
    }

    int lis_length = -1;

    int subsequence[numbers.size()];
    int indexes[numbers.size()];

    for (int i = 0; i < numbers.size(); ++i) {
        subsequence[i] = MAX_INT;
    }

    subsequence[0] = numbers.at(0);
    indexes[0] = 0;

    for (int i = 1; i < numbers.size(); ++i) {
        indexes[i] = ceilIndex(subsequence, 0, i, numbers.at(i));

        if (lis_length < indexes[i]) {
            lis_length = indexes[i];
        }
    }

    makingResultSubsequence(numbers, subsequence, indexes);

    return lis_length + 1;
}

int linear_LISL(vector<int> numbers) {
    int n = numbers.size();
    vector<int> ind(n, 0);
    vector<int> d(n, 0);
    int last_index = 0; // индекс последнего элемента подпоследовательности
    d[0] = 1;
    ind[0] = -1;
    int len = 0; // общая длина максимальной подпоследовательности
    for (int i = 1; i < n; ++i) {
        int maxlen = 1;
        ind[i] = -1;
        for (int j = 0; j < i; ++j) {
            linear_itters_counter++;

            if ((d[j] >= maxlen) && (numbers[j] < numbers[i])) { // подзадача:  ищем максимальную длину подпоследовательности для элемента
                maxlen = d[j]; // обновляем максимальное значнеие подпоследовательности
                ind[i] = j; // пишем предыдущее значние подпоследовательности для данного элемента
            }
        }
        d[i] = maxlen + 1; // пишем макс. длину подпоследовательности для данного элемента
        if (d[i] > len) {
            len = d[i]; // обновляем общее макс. значение
            last_index = i;
        }
    }
    vector<int> result;
    int index = last_index; // индекс элемента последовательности, который мы вставляем
    while (index != -1) { // пока последовательность не кончилась
        result.push_back(numbers[index]);
        index = ind[index];
    }

    cout << "The found increasing sequence with LINEAR operations: ";
    for (int i = result.size() - 1; i >= 0; i--) { // выводим результат
        cout << result[i] << " ";
    }
    cout << endl;
    return result.size();
}

int main() {
    vector<int> numbers = {5, 10, 6, 12, 3, 24, 7, 8};
    int n_linear, n_dynamic, num;

    /*cout << "Enter N:";
    cin >> n_dynamic_itters;

    for (int i = 0; i < n_dynamic_itters; ++i) {
        cout << "Enter a " << i << " num:";
        cin >> num;
        numbers.push_back(num);
    }*/

    n_linear = linear_LISL(numbers);
    n_dynamic = longestIncreasingSubsequenceLength(numbers);
    cout << endl;

    cout << "The maximum length of the ascending sequence with LINEAR: " << n_linear << endl;
    cout << "The maximum length of the ascending sequence with DYNAMIC: " << n_dynamic << endl;
    cout << endl;

    cout << "Number of iterations for a linear method: " << linear_itters_counter << endl;
    cout << "Number of iterations for a dynamic method: " << dynamic_itters_counter << endl;
}
