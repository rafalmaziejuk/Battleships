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

    void decode_action(PlayerAction action)
    {
        switch (action)
        {
            case PlayerAction::NUL: std::cout << "NUL\n";                   break;
            case PlayerAction::DISCONNECT: std::cout << "DISCONNECT\n";     break;
            case PlayerAction::MISSILE: std::cout << "MISSILE\n";           break;
            case PlayerAction::READY: std::cout << "READY\n";               break;
            case PlayerAction::MISS: std::cout << "MISS\n";                 break;
            case PlayerAction::HIT_PART: std::cout << "HIT_PART\n";         break;
            case PlayerAction::HIT_ONE: std::cout << "HIT_ONE\n";           break;
            case PlayerAction::HIT_AND_SANK: std::cout << "HIT_AND_SANK\n"; break;
        }
    }

}