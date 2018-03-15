#include "sm/main_sm.c"
#include "sm/write_sm.c"
#include "sm/read_sm.c"
#include "sm/display_sm.c"
#include "drivers/keyboard.c"
#include "drivers/display.c"

#include "lib/scheduler.h"
#include "lib/timer.h"

int main() {
    DDRA = 0xFF; PORTA = 0x00; // Display control lines.
    DDRC = 0xFF; PORTC = 0x00; // Display data lines.
    DDRD = 0x00; PORTD = 0xFF; // Keyboard and button overrides.
    
    DDRB = 0xFF; PORTB = 0x00;

    // Synchronous state machine setup:
    unsigned long main_tick_length = 100;
    unsigned long write_tick_length = 25;
    unsigned long read_tick_length = 25;
    unsigned long display_tick_length = 200;

    // Get GCD:
    unsigned long tmp_GCD = 1;
    tmp_GCD = findGCD(tmp_GCD, main_tick_length);
    tmp_GCD = findGCD(tmp_GCD, write_tick_length);
    tmp_GCD = findGCD(tmp_GCD, read_tick_length);
    tmp_GCD = findGCD(tmp_GCD, display_tick_length);
    unsigned long GCD = tmp_GCD;

    // Calculate period:
    unsigned long main_period = main_tick_length / GCD;
    unsigned long write_period = write_tick_length / GCD;
    unsigned long read_period = read_tick_length / GCD;
    unsigned long display_period = display_tick_length / GCD;

    // Setup list of tasks.
    static task m_task, w_task, r_task, d_task;
    task *tasks[] = { &m_task, &w_task, &r_task, &d_task };
    const unsigned char num_tasks = sizeof(tasks) / sizeof(task*);

    // Main tick
    m_task.state = main_start;
    m_task.period = main_period;
    m_task.elapsedTime = main_period;
    m_task.TickFct = &main_tick;

    // Write tick
    w_task.state = write_start;
    w_task.period = write_period;
    w_task.elapsedTime = write_period;
    w_task.TickFct = &write_tick;

    // Read tick
    r_task.state = read_start;
    r_task.period = read_period;
    r_task.elapsedTime = read_period;
    r_task.TickFct = &read_tick;

    // Display tick
    d_task.state = display_start;
    d_task.period = display_period;
    d_task.elapsedTime = display_period;
    d_task.TickFct = &display_tick;

    LCD_init();
    KB_init();
    
    TimerSet(GCD);
    TimerOn();

    while(1) {
        for (unsigned char i = 0; i < num_tasks; i++ ) {
            // Task is ready to tick
            if ( tasks[i]->elapsedTime == tasks[i]->period ) {
                // Setting next state for task
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                // Reset the elapsed time for next tick.
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        
        PORTB = command_flag;

        while(!TimerFlag);
        TimerFlag = 0;
    }

    return 0;
}