
set ( VIEWER_BASE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ViewerBase" )
set ( WORLDMANAGER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/WorldManager" )
set ( REPLAY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Replayer" )
set ( ROADMANAGER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RoadManager" )
set ( SCENARIOENGINE_DLL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ScenarioEngineDLL" )
set ( SCENARIOENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ScenarioEngine/SourceFiles")
set ( SCENARIOENGINE_INCLUDE_DIRS
 "${SCENARIOENGINE_INCLUDE_DIR}"
 "${CMAKE_CURRENT_SOURCE_DIR}/ScenarioEngine/Actions"
 "${CMAKE_CURRENT_SOURCE_DIR}/ScenarioEngine/Conditions"
 "${CMAKE_CURRENT_SOURCE_DIR}/ScenarioEngine/OSCTypeDefs"
 )
set ( COMMON_MINI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CommonMini")

set ( OSG_VERSION "osg160" )

if (WINSDK7_1)
  set ( TIME_LIB winmm.lib )
  set ( OSG_PACKAGE_URL https://drive.google.com/uc?export=download&id=1aN88B1_7MnT0OwHt_LOc8FtD7rFEP0Jq )
  set(osg_dir ${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/winsdk71)
  set ( OSG_INCLUDE_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/winsdk71/build/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/winsdk71/include"
  )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4482\"")
  set ( OSG_LIBRARIES_PATH 
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/winsdk71/lib" 
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/winsdk71/lib/osgPlugins-3.7.0"
  )
elseif ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
  set ( TIME_LIB "" )  
  set ( OSG_PACKAGE_URL https://drive.google.com/uc?export=download&id=14Xqe_bWGuZQAr69mit4melmnMfmNFOO6 )
  set(osg_dir ${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/win32)
  set ( OSG_INCLUDE_DIR   
    "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/win32/build/include"  
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/win32/include"  
  )  
  set ( OSG_LIBRARIES_PATH   
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/win32/lib"   
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/win32/lib/osgPlugins-3.7.0"  
  )  
else()  # v10
  set ( TIME_LIB "" )
  set ( OSG_PACKAGE_URL https://drive.google.com/uc?export=download&id=1a0HxilPJq2bZrat2le2x-Cscs5JeVAXP )
  set(osg_dir ${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10)
  set ( OSG_INCLUDE_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/build/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/include"
  )
  set ( OSG_LIBRARIES_PATH 
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/lib" 
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/lib/osgPlugins-3.7.0"
  )
endif (WINSDK7_1)

if(UNIX)
   SET(CMAKE_CXX_FLAGS "-std=c++14 -pthread -fPIC")
  
  add_library( db_serializers_osgsim UNKNOWN IMPORTED)
  set_property(TARGET db_serializers_osgsim PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/lib/osgPlugins-3.6.3/osgdb_serializers_osgsim.so")

  add_library( db_serializers_osg UNKNOWN IMPORTED)
  set_property(TARGET db_serializers_osg  PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/lib/osgPlugins-3.6.3/osgdb_serializers_osg.so")

  add_library( db_osg UNKNOWN IMPORTED)
  set_property(TARGET db_osg PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../externals/OpenSceneGraph/v10/lib/osgPlugins-3.6.3/osgdb_osg.so")

  set ( OSG_LIBRARIES
	GL
	optimized z debug z
	optimized osg debug osgd

	optimized osgAnimation debug osgAnimationd
	optimized osgDB debug osgDBd
	optimized osgGA debug osgGAd
	optimized osgViewer debug osgViewerd

	optimized osgText debug osgTextd
	optimized osgUtil debug osgUtild
	optimized osgSim debug osgSimd

	optimized OpenThreads debug OpenThreadsd

	db_serializers_osgsim
	db_serializers_osg
	db_osg
	db_fbx
  )
else() #not UNIX

set ( OSG_LIBRARIES 
	opengl32.lib
	optimized zlibstatic.lib debug zlibstaticd.lib 
	optimized ${OSG_VERSION}-osg.lib debug ${OSG_VERSION}-osgd.lib
	optimized ${OSG_VERSION}-osgAnimation.lib debug ${OSG_VERSION}-osgAnimationd.lib
	optimized ${OSG_VERSION}-osgDB.lib debug ${OSG_VERSION}-osgDBd.lib
	optimized ${OSG_VERSION}-osgGA.lib debug ${OSG_VERSION}-osgGAd.lib
	optimized ${OSG_VERSION}-osgViewer.lib debug ${OSG_VERSION}-osgViewerd.lib
	optimized ${OSG_VERSION}-osgText.lib debug ${OSG_VERSION}-osgTextd.lib
	optimized ${OSG_VERSION}-osgUtil.lib debug ${OSG_VERSION}-osgUtild.lib
	optimized ${OSG_VERSION}-osgSim.lib debug ${OSG_VERSION}-osgSimd.lib
	optimized ot21-OpenThreads.lib debug ot21-OpenThreadsd.lib
	optimized osgdb_serializers_osgsim.lib debug osgdb_serializers_osgsimd.lib
	optimized osgdb_serializers_osg.lib debug osgdb_serializers_osgd.lib
	optimized osgdb_osg.lib debug osgdb_osgd.lib 	
	optimized osgdb_fbx.lib debug osgdb_fbxd.lib 	
)
if (NOT WINSDK7_1)  # FBX not supporting winsdk 7.1
  list ( APPEND OSG_LIBRARIES optimized libfbxsdk-md.lib debug libfbxsdk-mdd.lib )
endif()

endif() #Endif UNIX

set ( ADAPT_COMMON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../EnvironmentModule/Adapt.Native.Common" )
set ( ADAPT_ENVIRONMENT_MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../EnvironmentModule/EnvironmentModule" )

add_subdirectory(RoadManager)
add_subdirectory(CommonMini)
add_subdirectory(ScenarioEngine)
add_subdirectory(ScenarioEngineDLL)

if (USE_ENVSIM_ADAPT)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../EnvironmentModule ${CMAKE_CURRENT_BINARY_DIR}/EnvironmentModule)
endif (USE_ENVSIM_ADAPT)

set ( ModulesFolder Modules )
set ( ApplicationsFolder Applications )  

set_target_properties (RoadManager PROPERTIES FOLDER ${ModulesFolder} )
set_target_properties (CommonMini PROPERTIES FOLDER ${ModulesFolder} )
set_target_properties (ScenarioEngine PROPERTIES FOLDER ${ModulesFolder} )
set_target_properties (ScenarioEngineDLL PROPERTIES FOLDER ${ModulesFolder} )

#
# Download library and content binary packets
#

if(${CMAKE_VERSION} VERSION_LESS "3.11.4") 
    message(WARNING "Important! CMake couldn't download external dependencies and 3D models. Please upgrade to CMake version 3.11.4 or above. Or  download file packages manually - see README.md")
else()
	include(FetchContent)

	# OpenSceneGraph package adapted for this project
	FetchContent_Declare(
	  osg_package
	  URL ${OSG_PACKAGE_URL} 
	  SOURCE_DIR ${osg_dir}
	)

	set(models_dir ${CMAKE_CURRENT_SOURCE_DIR}/../resources/models)
	FetchContent_Declare(
	  models_package
	  URL https://drive.google.com/uc?export=download&id=1RSbyFJoVahX1nGWAsdepsPsznAiNspUc # models	
	  SOURCE_DIR ${models_dir}
	)

	if(FORCE_DOWNLOAD_BINARIES OR NOT EXISTS ${models_dir} OR (USE_OSG AND NOT EXISTS ${osg_dir}))
	  
	  message(STATUS "Downloading binary packages - might take a few minutes..." )
	  file(REMOVE_RECURSE ${FETCHCONTENT_BASE_DIR}) 
	  
	  message(STATUS "  models")
	  FetchContent_MakeAvailable(models_package)
	  
	  if (USE_OSG)
		message(STATUS "  OpenSceneGraph")
		FetchContent_MakeAvailable(osg_package)
	  endif()

	endif()
endif()

if (USE_OSG)
  add_subdirectory(EnvironmentSimulator)
  add_subdirectory(ScenarioViewer)
  add_subdirectory(EgoSimulator)
  add_subdirectory(Replayer)
  if (USE_ENVSIM_ADAPT)
    add_subdirectory(EgoSimulator)
  endif (USE_ENVSIM_ADAPT)  
  add_subdirectory(ViewerBase)
  add_subdirectory(OpenDriveViewer)
  add_subdirectory(OdrPlot)

  
  set_target_properties (EnvironmentSimulator PROPERTIES FOLDER ${ApplicationsFolder} )  
  set_target_properties (ScenarioViewer PROPERTIES FOLDER ${ApplicationsFolder} )  
  set_target_properties (EgoSimulator PROPERTIES FOLDER ${ApplicationsFolder} )  
  set_target_properties (Replayer PROPERTIES FOLDER ${ApplicationsFolder} )  
  set_target_properties (ViewerBase PROPERTIES FOLDER ${ModulesFolder} )  
  set_target_properties (OpenDriveViewer PROPERTIES FOLDER ${ApplicationsFolder} )  
  set_target_properties (OdrPlot PROPERTIES FOLDER ${ApplicationsFolder} )  
  
endif (USE_OSG)