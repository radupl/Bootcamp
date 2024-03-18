#include <stdlib.h>
#include <stdio.h>

#define NUM_PORTS 3

#define NUM_INTERATIONS 10

typedef enum States {
    STATE_NORMAL,
    STATE_SHORT_NULL,
    STATE_SHORT_BATT
}STATES;

typedef struct Inputs {
    int in;
    int out;
}INPUTS;

typedef struct Ports {
    INPUTS inputs;
    STATES states;
}PORTS;

STATES handle_states(PORTS *ports) {
    STATES result;
    switch (ports->inputs.out) {
        case 0: 
            if (1 == ports->inputs.in) { 
                result = STATE_SHORT_BATT;
                break; 
            } else {
                if (ports->states == STATE_NORMAL || ports->states == STATE_SHORT_BATT) {
                    result = STATE_NORMAL;
                    break;
                } else {
                    result = STATE_SHORT_NULL;
                    break;
                }
            }
        case 1:
            if(0 == ports->inputs.in) {
                result = STATE_SHORT_NULL;
                break;
            } else {
                if (ports->states == STATE_NORMAL || ports->states == STATE_SHORT_NULL) {
                    result = STATE_NORMAL;
                    break;
                } else {
                    result = STATE_SHORT_BATT;
                    break;
                }
            }
        default:
            break;
    }
    return result;
}

void simulate_ports(PORTS *port) {
    port->inputs.in = rand() % 2;
    port->inputs.out = rand() % 2;
}

int main() {
    
    PORTS ports[NUM_INTERATIONS];

    for (int i = 0; i < NUM_INTERATIONS; i++) {
        ports->inputs.in = 0;
        ports->inputs.out = 0;
        ports->states = STATE_NORMAL;
    }

    for (int i = 0; i < NUM_INTERATIONS; i++) {
        simulate_ports(&ports[i]);
        printf("Input: %d \nOutput: %d\n", ports[i].inputs.in, ports[i].inputs.out);
        printf("Iteration %d: %d\n", i, (int)handle_states(&ports[i]));
        printf("\n");
    }
}