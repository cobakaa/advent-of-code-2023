#include <iostream>
#include <vector>

std::vector<int> z_function(std::string s) {
    int n = (int)s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
        std::cout << "i=" << i << " "
                  << "L=" << l << " "
                  << "R=" << r << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << s[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << z[i] << " ";
    }
    std::cout << std::endl;
    return z;
}

int main() {

    std::string str = "aaaabaac";
    z_function(str);

    return 0;
}
