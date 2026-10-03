#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include ""

/*

    Built to log keystrokes as keycodes to a queue that will be parsed by the input decoder
    Which will take the keycodes and turn them into characters or strings of characters 
    Whch will be sent to the input display, which will decide how to render the input.

    This class needs to setup for the task of grabbing hardware interrupts, reading and sending those
    "keycodes" to a queue to wait to get parsed.

    ** This is the largest priority event(s) since it is what defines the user interaction. **

    Issues:
            Since the hardware will be interrupting, we can NOT always ensure that the 
            queue will be available, but we need to ensure that the keystrokes get written
            to the queue.
            To fix this we can try storing the latest keystroke in the event of a queue acces failure,
            (Look into deferred interrupts which have a "fast" part and a "slow" part to them) That way, 
            we can grab the keystroke and then write it to the queue later. (maybe next tick)


*/
class 

#endif /* KEYLOGGER_H */
