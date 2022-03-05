#include <iostream>
#include <ctime>
#include <cmath>
#include <exception>
#include <fstream>

using namespace std;

typedef unsigned long long ULL;
const ULL MOD = 1000000007;

inline ULL safeAdd(const ULL& m, const ULL& n) {
    ULL res = m + n;
    if (res >= MOD) {
        res -= MOD;
    }
    return res;
}

inline ULL& safeBeAdded(ULL& m, const ULL& n) {
    m += n;
    if (m >= MOD) {
        m -= MOD;
    }
    return m;
}

inline ULL safeTime(const ULL& m, const ULL& n) {
    ULL res = m * n;
    res %= MOD;
    return res;
}

inline ULL& safeBeTimed(ULL& m, const ULL& n) {
    m *= n;
    m %= MOD;
    return m;
}

class Matrix {
     private:
        ULL nums[2][2] = {1, 1, 1, 0};
     public:
        const ULL& fib;
        
        Matrix() : fib(nums[0][0]) {
        
        }
        
        Matrix(const ULL& a11, const ULL& a12, const ULL& a21, const ULL& a22) : fib(nums[0][0]){
            nums[0][0] = a11;
            nums[0][1] = a12;
            nums[1][0] = a21;
            nums[1][1] = a22;
        }
        
        Matrix operator=(const Matrix& matA){
            if (this != &matA) {
                nums[0][0] = matA.nums[0][0];
                nums[0][1] = matA.nums[0][1];
                nums[1][0] = matA.nums[1][0];
                nums[1][1] = matA.nums[1][1];
            }
            return *this;
        }
        
        friend Matrix operator*(const Matrix& matA, const Matrix& matB) {
            Matrix mat(safeAdd(safeTime(matA.nums[0][0], matB.nums[0][0]), safeTime(matA.nums[0][1], matB.nums[1][0])), 
                       safeAdd(safeTime(matA.nums[0][0], matB.nums[0][1]), safeTime(matA.nums[0][1], matB.nums[1][1])), 
                       safeAdd(safeTime(matA.nums[1][0], matB.nums[0][0]), safeTime(matA.nums[1][1], matB.nums[1][0])), 
                       safeAdd(safeTime(matA.nums[1][0], matB.nums[0][1]), safeTime(matA.nums[1][1], matB.nums[1][1])));
            return mat;
        }
        Matrix& operator*=(const Matrix& matB) {
            *this = *this * matB;
            return *this;
        }
        Matrix operator^(const ULL& n) {
            Matrix mat(1, 0, 0, 1);
            for (ULL i = 0; i < n - 1; i++) {
                mat *= *this;
            }
            *this = mat;
            return mat;
        }
};

class wrong{};

ULL matrixSquaring(const ULL& n) {
    Matrix mat(1, 0, 0, 1), expo;
    for (ULL i = n - 1; i != 0; i = i >> 1) {
        if (i % 2 == 1) {
            mat *= expo;
        }
        expo *= expo;
    }
    return mat.fib;
}

ULL loopingFib(const ULL& n) {
    ULL numPair[2];
    numPair[0] = 0;
    numPair[1] = 1;
    bool status = 0;
    for (ULL i = 0; i < n; i++) {
        status = !status;
        safeBeAdded(numPair[status], numPair[!status]);
    }
    return numPair[status];
}

ULL correctiveMultiply(const ULL& n) {
    const double& base = (1 + sqrt(5)) / 2;
    double res = 1 / sqrt(5);
    for (ULL i = 0; i < n - 1; i++) {
        res *= base;
        res = round(res);
        if (res <= 0) {
            return 0;
        }
    }
    return ULL(res) % MOD;
}

ULL matrixMultiply(const ULL& n) {
    Matrix mat;
    return (mat^n).fib;
}

ULL directSquaring(const ULL& n) {
    double expo = (1 + sqrt(5)) / 2;
    double res = 1 / sqrt(5);
    for (ULL i = n; i != 0; i = i >> 1) {
        if (i % 2 == 1) {
            res *= expo;
        }
        expo *= expo;
        if (expo <= 0) {
            return 0;
        }
    }
    return (ULL)round(res) % MOD;
}


ULL recurse(const ULL& n, ULL* array) {
    try {
        if (array[n] == 0) {
            array[n] = safeAdd(recurse(n - 2, array), recurse(n - 1, array));
        }
    } catch (exception) {
        cout << "Stack Overflow in Method" << 6 << "! Discarding\n";
    }
    return array[n];
}

ULL memoryRecursion(const ULL& n) {
    ULL* array = new ULL[n]();
    array[0] = 1;
    array[1] = 1;
    recurse(n - 1, array);
    ULL res = array[n - 1];
    delete [] array;
    return res %= MOD;
}

ULL directRecursion(const ULL& n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return safeAdd(directRecursion(n - 2), directRecursion(n - 1));
    }
}

void testRecursion(ULL (**Func)(const ULL&), const ULL& n) {
    ULL len = 7;
    ofstream fout1("src/directRecursion.csv"), fout2("src/numerical.csv"), fout3("src/OnMethods.csv"), fout4("src/squaring.csv");
    fout1 << "n,time\n";
    fout2 << "n,truthValue,corApprox,sqrApprox\n";
    fout3 << "n,matSqrTime,corApproxTime,loopingTime,matMulTime\n";
    fout4 << "n,matSqrTime\n";
    for (ULL i = 1; ; i++) {
        if (len == 7) {
            cout << "result and time cost for n = " << i << ": ";
            for (ULL j = 0; j < len; j++) {
                clock_t bgn = clock();
                cout << "M" << j + 1 << " " << Func[j](i) << " " << clock() - bgn << " ";
                if (j == 6) {
                    fout1 << i << "," <<  clock() - bgn << "\n";
                }
                if (clock() - bgn >= 10000) {
                    cout << "Time Limit Exceeded in Method" << j + 1 << "! Discarding... ";
                    len -= 1;
                    fout1.close();
                    break;
                }
            }
            cout << "\n";
        }
        else if (len == 6) {
            for (ULL i = 1; i < 100; i++) {
                cout << "result and time cost for n = " << i << ": ";
                for (ULL j = 0; j < len; j++) {
                    clock_t bgn = clock();
                    ULL func = Func[j](i);
                    cout << "M" << j + 1 << " " << func << " " << clock() - bgn << " ";
                    if (j == 0) {
                        fout2 << i << "," << func << ",";
                    }
                    if (j == 2) {
                        fout2 << func << ",";
                    }
                    else if (j == 4) {
                        fout2 << func << "\n";
                    }
                }
                cout << "\n";
            }
            fout2.close();
            len -= 2;
        }
        else if (len != 1){
            bool flag = false;
            for (ULL i = 1; i < ULLONG_MAX; i = round(i * 1.1 + 1)) {
                cout << "result and time cost for n = " << i << ": ";
                fout3 << i << ",";
                for (ULL j = 0; j < len; j++) {
                    clock_t bgn = clock();
                    cout << "M" << j + 1 << " " << Func[j](i) << " " << clock() - bgn << " ";
                    fout3 << clock() - bgn << ",";
                    if (clock() - bgn >= 10000) {
                        cout << "Time Limit Exceeded in Method" << j + 1 << "! Discarding... ";
                        len = j;
                        if (len == 1) {
                            flag = true;
                        }
                        break;
                    }
                }
                cout << "\n";
                fout3 << "\n";
                if (flag) {
                    break;
                }
            }
        }
        else {
            bool flag = false;
            for (ULL i = 1; ; i = round(1.1 * i + 1)) {
                if (i == 0) {
                    i--;
                    flag = true;
                }
                clock_t bgn = clock();
                for (ULL j = 1; j < 100000; j++) {
                    Func[0](i);
                }
                cout << "result and time cost for n = " << i << " " << Func[0](i) << " " << clock() - bgn << "\n";
                fout4 << i << "," << clock() - bgn << "\n";
                if (flag) {
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
}

int main() {
    ULL n = 40000;
    ULL numOfMethods = 7;
    ULL (* p[7])(const ULL& n) = {matrixSquaring, correctiveMultiply, loopingFib, matrixMultiply, directSquaring, memoryRecursion, directRecursion};
    testRecursion(p, n);
    return 0;
}