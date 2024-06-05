#include "MLPerceptron.hpp"
#include <iostream>
#include <iomanip>



int main(){

    //std::vector<std::string> fbiases = {"net_train_bias1.bin", "net_train_bias2.bin"}, fweights = {"net_train_weight1.bin", "net_train_weight2.bin"};
    //std::vector<std::string> fbiases = {"mnist_bias1.bin", "mnist_bias2.bin"}, fweights = {"mnist_weight1.bin", "mnist_weight2.bin"};
    //std::string expected_answer_file = "train-labels-idx1-ubyte";
    std::vector<int> types = {1, 1};
    std::vector<std::string> fbiases = {"bias_1.bin", "bias_2.bin"}, fweights = {"weights_1.bin", "weights_2.bin"};
    std::string expected_answer_file = "expected.bin";
     //saving old functional
    
    std::vector<int> numNeurons = {2, 2},
                    prevNeurons = {2, 2}; 
    std::cout << "\033[31m Alive \033[0m\n";
    //MLPerceptron<double> mlperc(types, prevNeurons, numNeurons);
    //std::string filename = "train-images-idx3-ubyte";
    //std::string filename = "t10k-images-idx3-ubyte";
    std::string filename = "input.bin";
    
    size_t test_files = 1;
    std::vector<int> ans(test_files, 0);

    


    std::ifstream f2(expected_answer_file, std::ios::binary);
    std::vector<double> answer(2, 0); //expected answers
    for (size_t i = 0; i<answer.size(); i++) f2.read(reinterpret_cast<char*>(&answer[i]), sizeof(double));
    f2.close();
    //f2.seekg(8);
    //std::cout << "\033[31mExpected:\033[0m\n";
    //for (size_t i = 0; i < test_img; i++)
    //    f2.read(reinterpret_cast<char*>(&ans[i]), 1);
    //f2.close();
    //for (size_t i = 0; i < test_img; i++) std::cout << ans[i] << "\n";



    //int num = 0, correct_answers= 0; //needed later
    size_t num_eph = 10; //* later change to 10

#ifdef DEBUG
    std::cout << "\033[32mThis is values from main:\033[0m\n";
    for (double val : values)
    {
        std::cout << val << " ";
        num++;
    }
    std::cout << std::endl;
#endif
    
    //!f.seekg(16);


    std::vector<double> errors(2, 0);
    double learn_speed = 1;
    
    for (size_t eph = 0; eph < num_eph+1; eph++)
    {
        double allerr = 0.0;
        MLPerceptron<double> mlperc(fbiases, fweights, types);

        std::ifstream f(filename, std::ios::binary);
        if (!f.is_open()) { std::cerr << "Failed to open files" << std::endl; return -1; }
        std::vector<double> values(2, 0); // input values
            for (size_t i = 0; i<values.size(); i++) f.read(reinterpret_cast<char*>(&values[i]), sizeof(double));
        f.close();
        
        std::cout << "\033[31m===== NEW PROCESS... =====\033[0m\n";
        mlperc.process(values); // проход туда 1 раз
        //mlperc.results();
        //num = 1;
        std::cout << "\033[33mOutput:\033[0m\n";
        for (size_t i = 0; i<values.size(); i++) std::cout << values[i] << " ";
        std::cout << "\n";

        std::cout << "\033[33mExpected:\033[0m";
        for (size_t i = 0; i<answer.size(); i++) std::cout << answer[i] << " ";
        std::cout << "\n";
        
        for (size_t i = 0; i<values.size(); i++) //final result
        {
            //std::cout <<   i+1 << " " << (values[i]-answer[i])*(values[i]-answer[i])  << " " << std::fixed << " \n";
            allerr+= (values[i]-answer[i])*(values[i]-answer[i]);
            errors[i] = (answer[i]-values[i]);
        }
        std::cout << "\033[33mErrors:\033[0m";
        for (size_t i = 0; i<errors.size(); i++) std::cout << errors[i] << " ";
        std::cout << std::endl;
        std::cout << "\033[33mSquare error:\033[0m" << allerr << "\n";
        std::cout << std::endl;

        if (eph != num_eph)
        {
            mlperc.back_process(errors, learn_speed);
            mlperc.print_weights();
            mlperc.print_dweights();
            mlperc.change_weights(); //!AHTUNG!
        }

    }



    std::cout << "\033[33mEnd result:\033[0m";
    std::ifstream fwght("weights_1.bin", std::ios::binary);
    std::vector<double> some(4);
    for (size_t b = 0; b<some.size(); b++)
        fwght.read(reinterpret_cast<char*>(&some[b]), sizeof(double));
    fwght.close();
    for (size_t b = 0; b<some.size(); b++) std::cout << some[b] << " ";
    std::cout << std::endl;
    
    //std::cout << std::defaultfloat << "\033[31mTOTAL: \033[0m"<< test_img << "\033[31m   Correct: \033[0m" << correct_answers << "\033[31m   Percent: \033[0m" << ((double)correct_answers/test_img)*100 << "%\n";



    return 0;
}