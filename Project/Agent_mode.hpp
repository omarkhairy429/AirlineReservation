#include "BookingAgent.hpp"
#include "DatabaseUtils.hpp"

class AgentMode {
    public:
        void startAgentMode();  // Function to start the admin mode
    
    private:
        void bookFlight(BookingAgent & agent);
        void searchFlight(BookingAgent & agent);
        void cancelReservation(BookingAgent & agent);
        void modifyReservation(BookingAgent & agent);
    };