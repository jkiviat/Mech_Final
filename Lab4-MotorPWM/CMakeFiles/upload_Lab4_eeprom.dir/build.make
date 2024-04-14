# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/megn540/Desktop/MEGN540

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/megn540/Desktop/MEGN540

# Utility rule file for upload_Lab4_eeprom.

# Include the progress variables for this target.
include Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/progress.make

Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom: Lab4-MotorPWM/Lab4-atmega32u4-eeprom.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/megn540/Desktop/MEGN540/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Uploading Lab4-atmega32u4-eeprom.hex to atmega32u4 using avr109"
	cd /home/megn540/Desktop/MEGN540/Lab4-MotorPWM && avrdude -p atmega32u4 -c avr109 -U eeprom:w:Lab4-atmega32u4-eeprom.hex -P /dev/ttyZumoCarAVR

Lab4-MotorPWM/Lab4-atmega32u4-eeprom.hex: Lab4-MotorPWM/Lab4-atmega32u4.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/megn540/Desktop/MEGN540/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating Lab4-atmega32u4-eeprom.hex"
	cd /home/megn540/Desktop/MEGN540/Lab4-MotorPWM && /usr/bin/avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex Lab4-atmega32u4.elf Lab4-atmega32u4-eeprom.hex

upload_Lab4_eeprom: Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom
upload_Lab4_eeprom: Lab4-MotorPWM/Lab4-atmega32u4-eeprom.hex
upload_Lab4_eeprom: Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/build.make

.PHONY : upload_Lab4_eeprom

# Rule to build all files generated by this target.
Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/build: upload_Lab4_eeprom

.PHONY : Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/build

Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/clean:
	cd /home/megn540/Desktop/MEGN540/Lab4-MotorPWM && $(CMAKE_COMMAND) -P CMakeFiles/upload_Lab4_eeprom.dir/cmake_clean.cmake
.PHONY : Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/clean

Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/depend:
	cd /home/megn540/Desktop/MEGN540 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540/Lab4-MotorPWM /home/megn540/Desktop/MEGN540 /home/megn540/Desktop/MEGN540/Lab4-MotorPWM /home/megn540/Desktop/MEGN540/Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Lab4-MotorPWM/CMakeFiles/upload_Lab4_eeprom.dir/depend

