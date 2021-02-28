#include "Remote.h"

namespace Net
{
    void decode_status(sf::Socket::Status status)
    {
        switch (status)
        {
        case sf::Socket::Done:          std::cout << "\nDONE";            break;
        case sf::Socket::NotReady:      std::cout << "\nNOTREADY";        break;
        case sf::Socket::Partial:       std::cout << "\nPARTIAL";         break;
        case sf::Socket::Disconnected:  std::cout << "\nDISCONNECTED";    break;
        case sf::Socket::Error:         std::cout << "\nERROR";           break;
        }
    }

}