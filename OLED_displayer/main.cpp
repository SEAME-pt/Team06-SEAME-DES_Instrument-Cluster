#include "Display.hpp"

int	main(void)
{
    try
    {
        Display	dp;
        dp.putText("AAAA", 1, 1);
        dp.updateDisplay();
    }
    
    catch (const std::exception& e)
    {std::cerr << "Exception cought" << std::endl;}

}
