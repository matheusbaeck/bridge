# Bridge

The `bridge` library provides a flexible mechanism for coordinating and managing concurrent processes through pipes. It is designed to simplify inter-process communication and execution in a modular and extensible way.

## Usage

### Basic Example

```c
#include "bridge.h"

int main() {
    // Define your bridge configuration
    t_bridge bridge = {
        .fd_infile = STDIN_FILENO,
        .fd_outfile = STDOUT_FILENO,
        .size = 2, // Number of processes in the bridge
        .init = NULL, // Optional initialization function
        .param = NULL // Optional parameter for initialization function
    };

    // Define your block task
    t_block block = {
        .task = your_task_function, // Replace with your task function
        .error_handler = NULL, // Optional error handler function
        .param = your_task_parameter // Replace with your task parameter
    };

    // Launch the bridge
    bridge(bridge, block);

    return 0;
}
