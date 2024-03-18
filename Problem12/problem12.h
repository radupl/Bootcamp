#define NUM_PORTS 3

#define NUM_INTERATIONS 5

typedef enum States {
    STATE_NORMAL,
    STATE_SHORT_NULL,
    STATE_SHORT_BATT
}STATES;

typedef struct Ports {
    int in;
    int out;
    STATES current_state;
}PORTS;

extern void print_states(STATES state);

extern STATES handle_states(PORTS *port);

extern void simulate_ports(PORTS *port);