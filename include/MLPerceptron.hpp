#include <iostream>
#include <fstream>
#include <vector>

#include "Layer.hpp"
#include "functions.hpp"


template <typename T>
class MLPerceptron
{
    std::vector<Layer<T, activation_func, der_activation_func>> layers; //vector of layers. It's possible because of activation function
    std::vector<std::vector<T>> res;
    int action = 0;
    

public:
    MLPerceptron(const std::vector<std::string>& fbiases, std::vector<std::string>& fweights, const std::vector<int>& types)
    {

        for (size_t i = 0; i < fbiases.size(); i++)
        {
            std::ifstream file(fbiases[i], std::ios::binary | std::ios::ate);
            int numNeurons = file.tellg()/sizeof(T);
            //std::cout << numNeurons << " numNeurons \n";
            file.close();

            std::ifstream file2(fweights[i], std::ios::binary | std::ios::ate);
            int prevNeurons = file2.tellg()/(sizeof(T)*numNeurons);
            file2.close();
            //std::cout << prevNeurons << " prevNeurons \n";
            layers.emplace_back(prevNeurons, numNeurons, fbiases[i], fweights[i], types[i]);  
        }
    }



    /*MLPerceptron(const std::vector<int>& types, const std::vector<int>& vprevNeurons, const std::vector<int>& vnumNeurons)
    {

        for (size_t i = 0; i < types.size(); i++)
        {
            layers.emplace_back(vnumNeurons[i], vprevNeurons[i], types[i]); // наверное фигня
        }
    }*/

    //void addLayer(size_t prevNeurons, size_t numNeurons){}

    void process(std::vector<T> &values)
    {
        res.clear(); //!
        for (size_t layer_num=0; layer_num<layers.size(); layer_num++)
        {
            //std::cout << "\033[31m Layer " << layer_num+1 << "\033[0m\n";
            res.emplace_back(values);
            values = layers[layer_num].process(values);
            
            /*for (size_t i = 0; i < values.size(); i++)
            {
                //std::cout << "\033[31mpurelin result: \033[0m" << result << "\n";
                std::cout << "\033[33m " << values[i] << "\033[0m\n";
            }*/
            //std::cout << "\n";
        }
    }

    void back_process(std::vector<T> &deltas, double learn_speed)
    {
        for (size_t layer_num=layers.size(); layer_num >0; layer_num--)
        {
            std::cout << "\033[31m Layer " << layer_num << "\033[0m\n";
            deltas = layers[layer_num-1].back_process(deltas, res[layer_num-1], learn_speed);
            
            /*for (size_t i = 0; i < values.size(); i++)
            {
                //std::cout << "\033[31mpurelin result: \033[0m" << result << "\n";
                std::cout << "\033[33m " << values[i] << "\033[0m\n";
            }*/
            //std::cout << "\n";
        }
    }


    void print_weights()
    {
        std::cout << "\033[33mWeights:\033[0m\n";
        for (size_t layer_num=0; layer_num<layers.size(); layer_num++)
        {
            std::cout << "\033[31m Layer " << layer_num+1 << "\033[0m\n";
            layers[layer_num].print_weights();
            
        }
    }

    void print_dweights()
    {
        std::cout << "\033[33mdeltaWeights:\033[0m\n";
        for (size_t layer_num=0; layer_num<layers.size(); layer_num++)
        {
            std::cout << "\033[32m Layer " << layer_num+1 << "\033[0m\n";
            layers[layer_num].print_dweights();
            
        }
    }


    void results()
    {
        std::cout << "\033[33mResults:\033[0m\n";
        for (size_t i=0; i<res.size(); i++)
        {
            std::cout << "\033[31m Layer " << i+1 << "\033[0m\n";
            for (T r : res[i])
                std::cout << r << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void change_weights()
    {
        std::cout << "\033[31mDOING SOME DANGEROUS STUFF...\033[0m\n";
        for (size_t layer_num=0; layer_num<layers.size(); layer_num++)
        {
            std::cout << "\033[31m Layer " << layer_num+1 << "\033[0m\n";
            layers[layer_num].change_weights();
            
        }
    }





    ~MLPerceptron() = default;
};

