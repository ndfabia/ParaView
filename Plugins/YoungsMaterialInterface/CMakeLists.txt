cmake_minimum_required(VERSION 2.6)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

SET(PLUGIN_NAME YoungsMaterialInterface)
SET(PLUGIN_VERSION "0.5")

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PARAVIEW_INCLUDE_DIRS}
  ${VTK_INCLUDE_DIR}
  )

SET(SM_XML
  YoungsMaterialInterfaceResources.xml
  )

SET(UI_FILES
  pqYoungsMaterialInterfacePanel.ui
  )

SET(MOC_HEADERS
  pqYoungsMaterialInterfacePanel.h
  )

SET(CLIENT_SRCS
  pqYoungsMaterialInterfacePanel.cxx
  )

IF (PARAVIEW_BUILD_QT_GUI)

  INCLUDE(${QT_USE_FILE})

  INCLUDE_DIRECTORIES(
    ${VTK_INCLUDE_DIR}
    ${PARAVIEW_INCLUDE_DIRS}
    ${ParaView_SOURCE_DIR}/VTK/GUISupport/Qt
    ${pqCore_SOURCE_DIR}
    ${pqCore_BINARY_DIR}
    ${pqComponents_SOURCE_DIR}
    ${pqComponents_BINARY_DIR}
    ${QtWidgets_SOURCE_DIR}
    ${QtWidgets_BINARY_DIR}
    )

  QT4_WRAP_CPP(MOC_SRCS ${MOC_HEADERS})
  QT4_WRAP_UI(UI_SRCS ${UI_FILES})

  ADD_PARAVIEW_OBJECT_PANEL(
    IFACES IFACE_SRCS
    CLASS_NAME pqYoungsMaterialInterfacePanel
    XML_NAME YoungsMaterialInterface
    XML_GROUP filters
    )

  ADD_PARAVIEW_PLUGIN(${PLUGIN_NAME} ${PLUGIN_VERSION}
    SERVER_MANAGER_XML ${SM_XML}
    GUI_INTERFACES ${IFACES}
    SOURCES ${MOC_SRCS} ${UI_SRCS} ${IFACE_SRCS} ${CLIENT_SRCS}
    )

ELSE (PARAVIEW_BUILD_QT_GUI)
  ADD_PARAVIEW_PLUGIN(${PLUGIN_NAME} ${PLUGIN_VERSION}
    SERVER_MANAGER_XML ${SM_XML}
    )
ENDIF (PARAVIEW_BUILD_QT_GUI)

TARGET_LINK_LIBRARIES(
  ${PLUGIN_NAME}
  vtkGraphics)
