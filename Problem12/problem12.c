#include <stdlib.h>
#include <stdio.h>
#include "problem12.h"

// Function for printing the states
void print_states(STATES state) {
    switch (state) {
        case STATE_NORMAL:
            printf("STATE_NORMAL\n");
            break;
        case STATE_SHORT_BATT:
            printf("STATE_SHORT_BATT\n");
            break;
        case STATE_SHORT_NULL:
            printf("STATE_SHORT_NULL\n");
            break;
        default:
            break;
    }
}

// Handling states based on the current state
STATES handle_states(PORTS *port) {
    STATES result = port->current_state;

    switch (port->current_state) {
        case STATE_NORMAL:
            if (1 == port->in && 1 == port->out) result = STATE_NORMAL;
            if (0 == port->in && 0 == port->out) result = STATE_NORMAL;
            if (0 == port->in && 1 == port->out) result = STATE_SHORT_NULL;
            if (1 == port->in && 0 == port->out) result = STATE_SHORT_BATT;
            break;
        case STATE_SHORT_BATT:
            if (1 == port->in && 1 == port->out) result = STATE_SHORT_BATT;
            if (1 == port->in && 0 == port->out) result = STATE_SHORT_BATT;
            if (0 == port->in && 1 == port->out) result = STATE_SHORT_NULL;
            if (0 == port->in && 0 == port->out) result = STATE_NORMAL;
            break;
        case STATE_SHORT_NULL:
            if (1 == port->in && 1 == port->out) result = STATE_NORMAL;
            if (1 == port->in && 0 == port->out) result = STATE_SHORT_BATT;
            if (0 == port->in && 1 == port->out) result = STATE_SHORT_NULL;
            if (0 == port->in && 0 == port->out) result = STATE_SHORT_NULL;
            break;
        default:
            break;
    }

    port->current_state = result;
    return result;
}

// Simulating a random number [0, 1] for the ports
void simulate_ports(PORTS *port) {
    port->in = rand() % 2;
    port->out = rand() % 2;
}

int main() {

    PORTS ports[NUM_PORTS];

    for (int i = 0; i < NUM_PORTS; i++) {
        ports[i].in = 0;
        ports[i].out = 0;
        ports[i].current_state = STATE_NORMAL;
    }

    // For each port do NUM_ITERATIONS
    for (int i = 0; i < NUM_PORTS; i++) {
        printf("PORT %d: \n", i);
        for (int j = 0; j < NUM_INTERATIONS; j++) {
            simulate_ports(&ports[i]);

            printf("(Input, Output): (%d, %d)\n", ports[i].in, ports[i].out);

            printf("Current state: "); 
            print_states(ports[i].current_state);
            ports[i].current_state = handle_states(&ports[i]);

            printf("Output: "); 
            print_states(ports[i].current_state);
            printf("\n");
        }
    }
}