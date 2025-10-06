/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    int current_time = 0;
    int context_save_time = 10;//20, 20
    int isr_activity_time = 40;//40, 100, 200
    
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        if(activity == "CPU") {
                    execution += std::to_string(current_time) + ", " 
                            + std::to_string(duration_intr) + ", CPU burst\n";
                    current_time += duration_intr;

                } else if(activity == "SYSCALL" || activity == "END_IO") {
                    //switch to kernel mode, save context, find vector, load ISR
                    auto [intr_text, new_time] = intr_boilerplate(current_time, duration_intr, context_save_time, vectors);
                    execution += intr_text;

                    execution += std::to_string(new_time) + ", " 
                            + std::to_string(isr_activity_time) + ", ISR body executed for device " 
                            + std::to_string(duration_intr) + "\n";
                    new_time += isr_activity_time;

                    execution += std::to_string(new_time) + ", 1, IRET\n";
                    new_time++;
                    current_time = new_time;
                }
        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
