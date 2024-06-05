#include <iostream>
#include <vector>

template <typename T>
class Neuron
{
    T bias;
    T delta;
    std::vector<T> weights;
    
public:
    std::vector<T> d_wghts; //! ужас
    
    Neuron(T input_bias, std::vector<T> input_weights)
        : bias(input_bias), weights(std::move(input_weights)) {}

    T giveWeight(size_t pos) const
    {
        return weights[pos];
    }

    std::vector<T>& giveWeights()
    {
        return weights;
    }

    std::vector<T>& give_dWeights()
    {
        return d_wghts;
    }

    T giveBias() const
    {
        return bias;
    }

    T giveDelta() const
    {
        return delta;
    }

    void SetDelta(T val_delta)
    {
        delta = val_delta;
    }




    ~Neuron(){};

};