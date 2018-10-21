class PrimeNumberGenerator {
 private:
  int start_;
 public:
  explicit PrimeNumberGenerator(int start) : start_(start) {}
  int GetNextPrime() {
    bool prime;
    for (int j = start_; j < INT32_MAX; j++) {
      prime = start_ != 1;
      for (int i = 2; i < sqrt(start_) + 1; i++)
        if (start_ % i == 0 && start_ != i) prime = false;
      if (prime) return start_++;
      start_++;
    }
  }
};
