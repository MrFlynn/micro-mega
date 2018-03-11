#include "sm/main_sm.c"
#include "sm/write_sm.c"

int main() {
    enum MAIN_STATES main_state = main_start;
    enum WRITE_STATES write_state = write_start;

    while(1) {
        main_state = main_tick(main_state);
        write_state = write_tick(write_state);
    }
}