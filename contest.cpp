#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

const int cEight = 8;
const int cH = 256;

void LSD(std::vector<uint64_t> &ans, int n) {
  uint64_t shift = 0;

  for (uint64_t mask = 256 - 1; mask > 0 ; mask <<= 8) {

    std::vector<uint64_t> arr(ans.begin(), ans.end());

    std::vector<uint64_t> cnt(cH, 0);

    for (size_t i = 0; i < n; i++) {
    //   std::cout << (arr[i] & mask) << shift << "- first for" << '\n';
      ++cnt[(arr[i] & mask) >> shift];
    }

    for (int i = 1; i < cH; i++) {
    //   std::cout << i << "- i" << '\n';
      cnt[i] += cnt[i - 1];
    }

    std::cout << n << " - n" << "\n";
    std::cout << arr.size() << " - arr size" << "\n";
    std::cout << ans.size() << " - ans size" << "\n";
    for (int i = n - 1; i >= 0; i--) {
      std::cout << i << '\n';
      std::cout << ((arr[i] & mask) >> shift) << " " << "third for" << '\n';
      std::cout << cnt[(arr[i] & mask) >> shift] - 1 << '\n';
      ans[cnt[(arr[i] & mask) >> shift] - 1] = arr[i];
      --cnt[(arr[i] & mask) >> shift];
    }
    shift += 8;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> ans(n);
  for (int i = 0; i < n; i++) {
    std::cin >> ans[i];
  }
  std::cout << n << " - n input" << "\n";
  LSD(ans, n);
  for (size_t i = 0; i < n; i++) {
    std::cout << ans[i] << ' ';
  }
}
