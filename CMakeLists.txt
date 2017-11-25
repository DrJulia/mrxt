cmake_minimum_required(VERSION 2.6)
PROJECT(mrxt)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

FIND_PACKAGE(OpenCV 2.4.8 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/basics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/planner
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/planner/auxiliar
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/reactive
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/slam
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/slam/mapbuilders
    ${CMAKE_CURRENT_SOURCE_DIR}/include/architecture/slam/mapdata
    ${CMAKE_CURRENT_SOURCE_DIR}/include/model
    ${CMAKE_CURRENT_SOURCE_DIR}/include/model/sensors
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mylib
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OpenCV_INCLUDE_DIRS}
)


SET (MYLIB_SRCS
   src/mylib/ClMutex.cpp 
   src/mylib/ClThread.cpp 
   src/mylib/ComThread.cpp 
   src/mylib/ConfigFile.cpp 
   src/mylib/matFuns.cpp 
   src/mylib/stepEvent.cpp 
   src/mylib/StringTokenizer.cpp 
)
SET (MODEL_SRCS
   src/model/sensors/landmarksData.cpp 
   src/model/sensors/rangeSensorData.cpp 
   src/model/robotBase.cpp 
   src/model/simulatedModel.cpp 
)

SET (ARCH_SRCS
   src/architecture/basics/explorer.cpp 
   src/architecture/basics/robot.cpp 
   src/architecture/basics/team.cpp 
   src/architecture/planner/CoordinatedPlanner.cpp 
   src/architecture/planner/FrontierGreedyPlanner.cpp 
   src/architecture/planner/FSAPlanner.cpp 
   src/architecture/planner/HybridPlanner.cpp 
   src/architecture/planner/IGPlanner.cpp 
   src/architecture/planner/IntegratedIGPlanner.cpp 
   src/architecture/planner/MarketPlanner.cpp 
   src/architecture/planner/planner.cpp 
   src/architecture/reactive/localPotentialField.cpp 
   src/architecture/reactive/reactive.cpp 
   src/architecture/reactive/reactiveGauss.cpp 
   src/architecture/planner/auxiliar/pathPlanning.cpp 
   src/architecture/planner/auxiliar/treeNode.cpp
   src/architecture/slam/mapbuilders/EKFilter.cpp 
   src/architecture/slam/mapbuilders/EKFilterVel.cpp 
   src/architecture/slam/mapbuilders/particle.cpp 
   src/architecture/slam/mapbuilders/RBPFilter.cpp 
   src/architecture/slam/mapbuilders/vslamFilter.cpp 
   src/architecture/slam/mapdata/binMap.cpp 
   src/architecture/slam/mapdata/occupancyGridMap.cpp 
   src/architecture/slam/mapdata/OGMReflectProb.cpp 
   src/architecture/slam/mapdata/visualMap.cpp 
   src/architecture/slam/mapdata/vMapArray.cpp 
)

SET (GUI_SRCS
    src/ui/mainwindow.cpp
)

QT4_WRAP_UI(UISrcs 
    ui/mainWindow.ui
    ui/RobotSettingsDialog.ui 
    ui/scenePropertiesDialog.ui 
    ui/slamOptionsDialog.ui 
    ui/strategyOptionsDialog.ui 
    ui/About.ui 
    ui/appConfigDialog.ui
)

# all the headers that have the Q_OBJECT macro
QT4_WRAP_CPP(MOCSrcs 
    include/ui/mainwindow.h
    include/architecture/slam/mapbuilders/vslamFilter.h
    include/model/simulatedModel.h
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
ADD_EXECUTABLE(mrxt src/mrxt.cpp ${MOCSrcs} ${GUI_SRCS} ${UISrcs} ${ARCH_SRCS} ${MODEL_SRCS} ${MYLIB_SRCS})
TARGET_LINK_LIBRARIES(mrxt 
    ${QT_LIBRARIES}
    ${OpenCV_LIBS}
    pthread
    loki
)


add_custom_command(TARGET mrxt PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/config ${CMAKE_CURRENT_SOURCE_DIR}/bin/config)

add_custom_command(TARGET mrxt PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/maps ${CMAKE_CURRENT_SOURCE_DIR}/bin/maps)

add_custom_command(TARGET mrxt PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                        ${CMAKE_SOURCE_DIR}/arvc.png ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_custom_command(TARGET mrxt PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/bin/outfiles)

