#include <iostream>
#include <vector>

void Input(std::vector<std::vector<int>>& nums, uint64_t num, size_t index, size_t divider, size_t number_digits) {
  for (int i = number_digits - 1; i >= 0; --i) {
    nums[index][i] = num & (divider - 1);
    num /= divider;
  }
}

void Output(std::vector<std::vector<int>> nums, size_t index, size_t divider, size_t number_digits) {
  uint64_t num = 0;
  for (int i = 0; i < number_digits; ++i) {
    num *= divider;
    num += nums[index][i];
  }
  std::cout << num << " ";
}

void CountSort(std::vector<std::vector<int>>& nums, size_t divider, size_t number_digits, int cur_number) {
  std::vector<int> count(divider);
  for (int i = 0; i < nums.size(); ++i) {
    ++count[nums[i][cur_number]];
  }
  --count[0];
  for (int i = 1; i < divider; ++i) {
    count[i] += count[i - 1];
  }
  std::vector<std::vector<int>> answer(nums.size(), std::vector<int>(number_digits));
  for (int i = nums.size() - 1; i >= 0; --i) {
    for (int j = 0; j < number_digits; ++j) {
      answer[count[nums[i][cur_number]]][j] = nums[i][j];
    }
    --count[nums[i][cur_number]];
  }
  nums = answer;
}

void LsdSort(std::vector<std::vector<int>>& nums, size_t divider, size_t number_digits) {
  for (int i = number_digits - 1; i >= 0; --i) {
    CountSort(nums, divider, number_digits, i);
  }
}


int main() {
  size_t divider = 1 << 16;
  size_t number_digits = 4;
  size_t n;
  std::cin >> n;
  std::vector<std::vector<int>> nums(n, std::vector<int>(number_digits));

  for (size_t i = 0; i < n; ++i) {
    uint64_t num;
    std::cin >> num;
    Input(nums, num, i, divider, number_digits);
  }

  LsdSort(nums, divider, number_digits);

  for (int i = 0; i < n; ++i) {
    Output(nums, i, divider, number_digits);
  }

  return 0;
}