# ADS129x Firmware

This repository contains a sample project for the STM32 microcontroller which includes a driver for the ADS1298 and ADS1299 chips. The driver implementation can also be used with other microcontrollers, not just STM32.

## Project Structure

The project is organized into the following directories:

- `LegacyIncSrc`: contains a simpler implementation of the driver
- `inc/ADS129x`: contains header files for the ADS129x driver implementation
- `src/ADS129x`: contains source files for the ADS129x driver implementation

The ADS129x driver implementation consists of the following pairs of `.c` and `.h` files:

- `ADS129xDevices.c` and `ADS129x_Devices.h`
- `ICommand.c` and `ICommand.h`
- `IPowerManager.c` and `IPowerManager.h`
- `IReadData.c` and `IReadData.h`
- `Utils.c` and `Utils.h`

## Usage

To use the ADS129x driver implementation in your own project, simply copy the contents of the `inc/ADS129x` and `src/ADS129x` directories into your own project's source tree.

In your project, include the relevant header files (`ADS129x_Devices.h`, `ICommand.h`, `IPowerManager.h`, `IReadData.h`, and `Utils.h`) and make sure to link against the source files (`ADS129xDevices.c`, `ICommand.c`, `IPowerManager.c`, `IReadData.c`, and `Utils.c`).

For an example of how to use the ADS129x driver implementation, please see the `main.c` file in the `LegacyIncSrc` directory.

## License

This code is provided under the MIT license. See the `LICENSE` file for more information.
