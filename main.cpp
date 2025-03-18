#include "include/template.tpp"
#include <iostream>
#include <map>
#include <sstream>

void help() {
    std::cout << "USAGE:\ndifferentiator --eval “x * y“ x=10 y=12\n120\n";
    std::cout << "differentiator --diff “x * sin(x)“ --by x\nx * cos(x) + sin(x)\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        help();
        return 1;
    }
    if (std::string(argv[1]) == "--eval") {
        std::string exp_string = argv[2];
        Expression<long double> exp = Expression<long double>::from_string(exp_string.substr(0, std::string::npos - 1));
        std::map<std::string, long double> context;
        for (int i = 3; i < argc; i++) {
            std::stringstream s;
            std::string cur_s = std::string(argv[i]);
            int pos_eq = cur_s.find('=');
            if (pos_eq == std::string::npos) {
                return 1;
            }
            s << cur_s.substr(pos_eq + 1, std::string::npos);
            long double number;
            s >> number;
            context[cur_s.substr(0, pos_eq)] = number;
        }
        std::cout << exp.eval(context) << std::endl;
    } else if (std::string(argv[1]) == "--diff") {
        if (argc != 5) {
            help();
            return 1;
        }
        std::string var = argv[4];
        std::string exp_string = argv[2];
        Expression<long double> exp = Expression<long double>::from_string(exp_string.substr(0, std::string::npos - 1));
        std::cout << exp.derivative(var).to_string() << std::endl;
    } else {
        std::cout << "Unknown format:" << argv[1] << std::endl;
        return 1;
    }
    return 0;
}