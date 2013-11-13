FIND_PACKAGE(Qt)

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})	

INCLUDE_DIRECTORIES($ENV{OSG_ROOT}/include)

LINK_DIRECTORIES($ENV{OSG_ROOT}/lib)


SET(VIEWER_SRC 
	main.cpp
	BaseShape.h
	BaseShape.cpp
	AnimationManager.h
	AnimationManager.cpp
	ViewerWidget.h
	ViewerWidget.cpp
	GraphicsWindowQt.h
	GraphicsWindowQt.cpp
	)


ADD_EXECUTABLE(3D_ContactViewer ${VIEWER_SRC} )

TARGET_LINK_LIBRARIES( 3D_ContactViewer osgViewerd.lib osgd.lib osgDBd.lib osgAnimationd.lib osgUtild.lib osgGAd.lib OpenThreadsd.lib)

TARGET_LINK_LIBRARIES( 3D_ContactViewer ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} $ENV{QTDIR}/lib/QtOpenGLd4.lib )
		


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


