# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(HARDWARE_DEVICES HardwareDevices)
file(GLOB_RECURSE HARDWARE_DEVICES_SOURCES ${HARDWARE_DEVICES}/*.c)

idf_component_register(
	# list the source files of this component
    SRCS "main.c" 
    	${HARDWARE_DEVICES_SOURCES}
    # optional, add here public include directories
    INCLUDE_DIRS "." ${HARDWARE_DEVICES}
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES            # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)
