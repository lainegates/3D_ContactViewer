INCLUDE_DIRECTORIES($ENV{OSG_ROOT}/include)

LINK_DIRECTORIES($ENV{OSG_ROOT}/lib)

SET(VIEWER_SRC 
	main.cpp
	BaseShape.h
	BaseShape.cpp
	AnimationManager.h
	AnimationManager.cpp
	)


ADD_EXECUTABLE(3D_ContactViewer ${VIEWER_SRC} )

TARGET_LINK_LIBRARIES( 3D_ContactViewer osgViewerd.lib osgd.lib osgDBd.lib osgAnimationd.lib osgUtild.lib osgGAd.lib)

		

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


