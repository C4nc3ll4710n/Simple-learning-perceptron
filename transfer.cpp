#include <iostream>
#include <iomanip>
#include <vector>
#include <format>
#include <fstream>



int main()
{
    std::vector<double> bias_1 = {0.35, 0.35}, bias_2 = {0.60, 0.60};
    std::vector<std::vector<double>> biases = {bias_1, bias_2};
    std::vector<std::vector<double>> weights_1 = {{0.15, 0.25}, {0.20, 0.30}}, weights_2 = {{0.40, 0.50}, {0.45, 0.55}};
    std::vector<std::vector<std::vector<double>>> weights = {weights_1, weights_2}; 
    std::vector<double> input = {0.05, 0.10};
    std::vector<double> expected = {0.01, 0.99};

    // Открываем файловый поток для записи в бинарном режиме

    for (int i = 0; i < biases.size(); i++)
    {
        std::string biasfn = std::format("bias_{}.bin", i+1), wghtfn = std::format("weights_{}.bin", i+1);
        std::ofstream out_file(biasfn, std::ios::binary);
        for (double num : biases[i]) {
            out_file.write(reinterpret_cast<const char*>(&num), sizeof(double));
        }
        out_file.close();
        std::ofstream out_file2(wghtfn, std::ios::binary);
        for (const auto& weight_vec : weights[i]) {
            for (const double& num2 : weight_vec) {
                out_file2.write(reinterpret_cast<const char*>(&num2), sizeof(num2));
            }
        }
        out_file2.close();

    }
    std::ofstream out_file("input.bin", std::ios::binary);
    for (double num : input) {
            out_file.write(reinterpret_cast<const char*>(&num), sizeof(double));
        }
    out_file.close();
     std::ofstream out_file2("expected.bin", std::ios::binary);
    for (double num : expected) {
            out_file2.write(reinterpret_cast<const char*>(&num), sizeof(double));
        }
    out_file2.close();





    return 0;
}