#include "BookingAgent.hpp"


class AgentMode {
    public:
        void startAgentMode();  // Function to start the admin mode
    
    private:
        void bookFlight(BookingAgent & agent);
        void searchFlight(BookingAgent & agent);
    };