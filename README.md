# CIRCULAR_BUF

Module to create and control uint8_t circular buffers.

## Installation

Copy git folder into required mplab source folder.

## Documentation

To build documentation, call doxygen from project folder.

## Usage

### Testing

To test module, ceedling and gcc need to install.

```
ceedling test:all
```

All tests should pass before adding to project.

### Code usage

This function is unable to dynamically create the array and circular buffer.
Therefore it is necessary for these to already be created and their pointers
to be passed in this function.

The function will then add the address of the array into the circular
buffer's struct for later use.

Example:
```
const uint8_t buf_size = 8;
circular_buf_t circular_buf;
circular_buf_t * p__circular_buf = &circular_buf;
uint8_t p_buf_array[buf_size];

p_circular_buf = circular_buf_create(buf_size, p_buf_array, p_circular_buf);
```
