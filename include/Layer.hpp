#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include <cstring> 
#include <future>

template <typename T,  T (*func)(const std::vector<T>&, const std::vector<T>&, T, int), T (*der)(const std::vector<T>&, const std::vector<T>&, T, int)>
class Layer
{
    std::vector<Neuron<T>> neurons;
    int type; //made for function detection (if is a purelin or tansig)
    std::string fbiases, fweights;
    size_t nmNeurons, prvNeurons;

public:

    Layer(size_t prevNeurons, size_t numNeurons, std::string fbias, std::string fweight, int tp )
    {
        type = tp; 
        fbiases = fbias;
        fweights = fweight; 
        nmNeurons = numNeurons;
        prvNeurons = prevNeurons;

        std::ifstream fbs(fbias, std::ios::binary), fwght(fweight, std::ios::binary);

        if (!fbs.is_open() || !fwght.is_open()) { std::cerr << "Failed to open files" << std::endl; }
        std::vector<T> bias(numNeurons);

        for (size_t b = 0; b<numNeurons; b++)
            fbs.read(reinterpret_cast<char*>(&bias[b]), sizeof(T));
        fbs.close();

        std::vector<std::vector<T>> weights(numNeurons, std::vector<T>(prevNeurons));
        for (size_t k = 0; k<prevNeurons; k++)
        {
            for (size_t i = 0; i<numNeurons; i++)
            {
                
                fwght.read(reinterpret_cast<char*>(&weights[i][k]), sizeof(T));
            }
        }
        for (size_t n = 0; n < numNeurons; n++) // placing biases and weights to neurons
        {
            neurons.emplace_back(bias[n], weights[n]);
        }
        
        std::cout << "The end" << std::endl;
        fwght.close();
    }

    /*Layer(vnumNeurons[i], vprevNeurons[i], types[i])
    {
        
    }*/


    std::vector<T> process(std::vector<T> &values) // counting value for neuron, using async
    {
        std::vector<T> temp(neurons.size());
        std::vector<std::future<T>> futures;
        for (size_t i = 0; i < neurons.size(); i++) 
        {
            futures.push_back(std::async(std::launch::async, [i, &values, this]() -> T 
                {
                    return func(values, neurons[i].giveWeights(), neurons[i].giveBias(), type);
                })
            );
        }
        for (size_t i = 0; i< neurons.size(); i++)// i < futures.size(); i++) 
            temp[i] = futures[i].get();
            //temp[i] = func(values, neurons[i].giveWeights(), neurons[i].giveBias(), type);//futures[i].get();
            
        return temp;

    }

    std::vector<T> back_process(std::vector<T> &deltas, const std::vector<T> res, double learn_speed) // counting value for neuron, using async
    {
        for (size_t i = 0; i < neurons.size(); i++) 
        {
            neurons[i].d_wghts.clear();
            for (size_t j = 0; j < res.size(); j++)
            {
                //std::cout << "\033[31m Alive \033[0m\n";
                //std::cout << "\033[33m d_w = \033[0m" << learn_speed << " * " << deltas[i] << " * " <<  res[j] << " = " << learn_speed * deltas[i] * res[j] << "\n";
                neurons[i].d_wghts.emplace_back(learn_speed * deltas[i] * res[j]); //! наверное, коэффы могут быть не ок

                /*std::cout << "RES WHILE BACK PROCESS\n";
                for ( T r :res)
                    std::cout << r << " ";
                std::cout << "\n";*/



                //std::cout << "values " << learn_speed << " " <<  deltas[j]  << " " <<  res[i] << "\n";
            }

        } 

        //*counting deltas
        std::vector<T> new_deltas(res.size());
        T max_del = 0;
        for (size_t j = 0; j < res.size(); j++)
        {
            T del_val = 0;
            for (size_t i = 0; i < neurons.size(); i++) 
            {   
                //std::cout << "\033[31m" <<neurons[i].giveWeight(j) << " " << deltas[i] << " \033[0m\n";
                //del_val += der(res, neurons[i].giveWeights(), neurons[i].giveBias(), 1)*deltas[i];//neurons[i].giveWeight(j)*deltas[i];
                del_val += neurons[i].giveWeight(j)*deltas[i];
            }
            //std::cout << "\033[34mTHIS IS DELTA\033[0m\n " << del_val << " " << new_deltas.size() << " \n ";
            new_deltas[j] = del_val;
            
        }
        return new_deltas;

    }



    void print_weights()
    {
        for (size_t i = 0; i<neurons.size(); i++)
        {
            std::vector<T> temp_weights = neurons[i].giveWeights();
            std::cout << "\033[32m Neuron " << i+1 << "\033[0m\n";
            for (T wght :  temp_weights)
            {
                std::cout << wght << " ";
            }
            std::cout << std::endl;
        }
            
    }

    void print_dweights()
    {
        for (size_t i = 0; i<neurons.size(); i++)
        {
            std::vector<T> temp_dweights = neurons[i].give_dWeights();
            std::cout << "\033[32m Neuron " << i+1 << "\033[0m\n";
            for (T dwght :  temp_dweights)
            {
                std::cout << dwght << " ";
            }
            std::cout << std::endl;
        }
            
    }

    void change_weights()
    {
        std::ofstream fwght(fweights, std::ios::binary);
        std::vector<T> dw;
        for (size_t i = 0; i<neurons.size(); i++)
        {
            std::vector<T> temp_w = neurons[i].giveWeights(), temp_dw = neurons[i].give_dWeights();
            for (size_t j = 0; j < temp_w.size(); j++)
            {
                double temp_result = temp_w[j] + temp_dw[j];
                //std::cout << "file: " << fweights <<" temp res " << temp_result << "\n";
                dw.emplace_back(temp_result);
                //fwght.write(reinterpret_cast<const char*>(&temp_result), sizeof(double));
            }
            
                
        }
        
        /*std::cout << "***NEW WEIGHTS\n";
        for (size_t i = 0; i < dw.size(); i++)
        {
            std::cout << dw[i] << " ";
            
        }*/
        std::vector<T> truedw(dw.size(), 0);
        for(size_t h = 0; h<nmNeurons; h++) //defenitely not good sizes
        {
            for(size_t w = 0; w<prvNeurons; w++)
            {
                truedw[h*2+w] = dw[w*2+h];
            }
                
        }
        for (size_t i = 0; i < truedw.size(); i++)
        {
            fwght.write(reinterpret_cast<const char*>(&truedw[i]), sizeof(double));
            
        }
        fwght.close();
            
        


    }



    ~Layer() = default;  


};
