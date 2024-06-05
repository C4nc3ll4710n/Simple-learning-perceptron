#include <cmath>
#include <iomanip>
#include <vector>
#include <iostream>

double purelin(const std::vector<double> &xs, const std::vector<double> &ws, double b) 
{
    double result = 0;
    for (size_t i = 0; i< xs.size(); i++)
    {
        result += xs[i]*ws[i]; // v_j
        //std::cout << "+ " << xs[i] << " * " << ws[i] <<" :\033[32m"  << result <<  "\033[0m\n";
            
    }
    result+=b;
    //std::cout << "\033[31mpurelin result: \033[0m" << result << "\n";
    return result;
}

double tansig(const std::vector<double> &xs, const std::vector<double> &ws, double b) 
{
    double result = 0;
    //std::cout << "\033[33m tansig \033[0m\n";
    for (size_t i = 0; i< xs.size(); i++)
    {
        
        result += xs[i]*ws[i];
        //std::cout << xs[i] << "   ";//" * " << ws[i] <<" :\033[32m"  << result <<  "\033[0m\n";
    }
    result+=b;
    //std::cout << "\033[31mtansig result: \033[0m" << result -1.0 << "\n";
    return 2.0/(1.0+exp(-2.0*result)) -1.0;
}



double activation_func(const std::vector<double> &xs, const std::vector<double> &ws, double b, int type)
{
    /*
    Функция-менеджер, в зависимости от type вызывает разные функции. Сделана ради того, чтобы было возможным
    создать вектор из слоёв в MLPerceptron
    */
    if (type == 1)
        return purelin(xs, ws, b);
    else if (type == 2)
        return tansig(xs, ws, b);
    else
        return 0;
    
}


double der_purelin(const std::vector<double> &xs, const std::vector<double> &ws, double b) 
{
    double result = 0;
    for (size_t i = 0; i< xs.size(); i++)
    {
        result += ws[i]; // v_j
        //std::cout << "+ " << xs[i] << " * " << ws[i] <<" :\033[32m"  << result <<  "\033[0m\n";
            
    }
    //!
    result+=b;
    //std::cout << "\033[31mpurelin result: \033[0m" << result << "\n";
    return result;
}

double der_tansig(const std::vector<double> &xs, const std::vector<double> &ws, double b) 
{
    double result = 0;
    //std::cout << "\033[33m tansig \033[0m\n";
    for (size_t i = 0; i< xs.size(); i++)
    {
        
        result += xs[i]*ws[i];
        //std::cout << xs[i] << "   ";//" * " << ws[i] <<" :\033[32m"  << result <<  "\033[0m\n";
    }
    //!
    result+=b;
    //std::cout << "\033[31mtansig result: \033[0m" << result -1.0 << "\n";
    return 1-result*result;
}


double der_activation_func(const std::vector<double> &xs, const std::vector<double> &ws, double b, int type)
{
    /*
    Функция-менеджер, в зависимости от type вызывает разные функции. Сделана ради того, чтобы было возможным
    создать вектор из слоёв в MLPerceptron
    */
    if (type == 1)
        return der_purelin(xs, ws, b);
    else if (type == 2)
        return der_tansig(xs, ws, b);
    else
        return 0;
    
}
