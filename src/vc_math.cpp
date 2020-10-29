#include <sstream>
#include <math.h>
#include <Varcmd.hpp>

std::string vc_math::main(Context *ctx, std::vector<std::string> args) {

    std::vector<double> stack;

    for (std::string bit : args) {
        if (bit == "+") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            stack.push_back(a + b);
        } else if (bit == "-") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            stack.push_back(a - b);
        } else if (bit == "/") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            stack.push_back(a / b);
        } else if (bit == "*") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            stack.push_back(a * b);
        } else if (bit == "max") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            if (a > b) {
                stack.push_back(a);
            } else {
                stack.push_back(b);
            }
        } else if (bit == "min") {
            double a = stack.back(); stack.pop_back();
            double b = stack.back(); stack.pop_back();
            if (a < b) {
                stack.push_back(a);
            } else {
                stack.push_back(b);
            }
        } else if (bit == "sin") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(sin(a));
        } else if (bit == "cos") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(cos(a));
        } else {
            try {
                double a = std::stod(bit);
                stack.push_back(a);
            } catch (int e) {
                
            }
        }
    }

    double res = stack.back(); stack.pop_back();

    std::string out = std::to_string(res);

    return out;
}

std::string vc_math::usage() {
    return "${math:rpn,rpn,rpn,rpn}";
}
