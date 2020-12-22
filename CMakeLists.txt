cmake_minimum_required(VERSION 3.8)

project("CheckLang")

#
# Include source roots from project
#
include_directories(${PROJECT_SOURCE_DIR})

#
# Check runtime executable; analogous to a Check VM
#
add_executable(CheckBox
	"check_box.cpp"
)

#
# Runtime intrinsic resources and standard libs
#
add_library(CheckCore STATIC
	# Intrinsic elements of object-oriented language
	"intrinsics/object_prototype.cpp"
	"intrinsics/object_method.cpp"
	"intrinsics/object_property.cpp"
	"intrinsics/object_instance.cpp"

	# Collection and sorting utilities
	
)

#
# Language compilation executable to intrinsic elements
#
add_executable(CheckCompile
	"check_compile.cpp"
)

#
# CheckBox (runtime) dependencies
#
target_link_libraries(CheckBox CheckCore)

#
# CheckComile (compiler) dependencies
#
target_link_libraries(CheckCompile CheckCore)