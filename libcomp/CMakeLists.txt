# This file is part of COMP_hack.
#
# Copyright (C) 2010-2016 COMP_hack Team <compomega@tutanota.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(libcomp)

FIND_PACKAGE(Threads REQUIRED)

MESSAGE("** Configuring ${PROJECT_NAME} **")

# Add a target to generate API documentation.
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/api/libcomp)
GENERATE_DOCS(doc/Doxyfile.in)

# Add a directory to put the objgen output into.
FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/objgen)

SET(SYSTEM_LIBRARIES "")

IF(BSD)
FIND_PACKAGE(ExecInfo REQUIRED)

SET(SYSTEM_LIBRARIES ${SYSTEM_LIBRARIES} ${EXECINFO_LIBRARY})
ENDIF(BSD)

SET(${PROJECT_NAME}_SRCS
    src/ArgumentParser.cpp
    src/BaseServer.cpp
    src/ChannelConnection.cpp
    src/Compress.cpp
    src/Convert.cpp
    src/CString.cpp
    src/Database.cpp
    src/DatabaseBind.cpp
    src/DatabaseChangeSet.cpp
    src/DatabaseMariaDB.cpp
    src/DatabaseQuery.cpp
    src/DatabaseQueryMariaDB.cpp
    src/DatabaseQuerySQLite3.cpp
    src/DatabaseSQLite3.cpp
    src/DataFile.cpp
    src/DataStore.cpp
    src/Decrypt.cpp
    src/DefinitionManager.cpp
    src/DynamicObject.cpp
    src/DynamicVariable.cpp
    src/DynamicVariableFactory.cpp
    src/EncryptedConnection.cpp
    src/Exception.cpp
    src/InternalConnection.cpp
    src/LobbyConnection.cpp
    src/Log.cpp
    src/ManagerPacket.cpp
    #src/MemoryFile.cpp
    src/MessageConnectionClosed.cpp
    src/MessageEncrypted.cpp
    src/MessageInit.cpp
    src/MessagePacket.cpp
    src/MessagePong.cpp
    src/MessageShutdown.cpp
    src/MessageTimeout.cpp
    src/MessageWorldNotification.cpp
    src/Object.cpp
    src/Packet.cpp
    src/PacketException.cpp
    #src/PacketScript.cpp
    src/PlatformWindows.cpp
    src/PEFile.cpp
    src/PersistentObject.cpp
    src/Randomizer.cpp
    src/ReadOnlyPacket.cpp
    src/RingBuffer.cpp
    src/ScriptEngine.cpp
    src/ServerCommandLineParser.cpp
    src/ServerConstants.cpp
    src/ServerDataManager.cpp
    src/Shutdown.cpp
    #src/Structgen.cpp
    src/TcpConnection.cpp
    src/TcpServer.cpp
    #src/ThreadManager.cpp
    src/Worker.cpp
)

IF(NOT WIN32)
    SET(${PROJECT_NAME}_SRCS
        ${${PROJECT_NAME}_SRCS}
        # for comp_manager and testing.
        src/Child.cpp
        src/DayCare.cpp
        src/SpawnThread.cpp
        src/WatchThread.cpp
    )
ENDIF(NOT WIN32)

IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigCustom.cpp)
    SET(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} src/ConfigCustom.cpp)
ELSE()
    SET(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} src/Config.cpp)
ENDIF()

# This is a list of all header files. Adding the header files here ensures they
# are listed in the source files for IDE projects.
SET(${PROJECT_NAME}_HDRS
    src/ArgumentParser.h
    src/BaseServer.h
    src/ChannelConnection.h
    src/Compress.h
    src/ConnectionMessage.h
    src/Constants.h
    src/Convert.h
    src/CString.h
    src/Database.h
    src/DatabaseBind.h
    src/DatabaseChangeSet.h
    src/DatabaseMariaDB.h
    src/DatabaseQuery.h
    src/DatabaseQueryMariaDB.h
    src/DatabaseQuerySQLite3.h
    src/DatabaseSQLite3.h
    src/DataFile.h
    src/DataStore.h
    src/Decrypt.h
    src/DefinitionManager.h
    src/DynamicObject.h
    src/DynamicVariable.h
    src/DynamicVariableFactory.h
    src/DynamicVariableInt.h
    src/EncryptedConnection.h
    src/Endian.h
    src/EnumMap.h
    src/ErrorCodes.h
    src/Exception.h
    src/InternalConnection.h
    src/LobbyConnection.h
    src/Log.h
    src/Manager.h
    src/ManagerPacket.h
    #src/MemoryFile.h
    src/Message.h
    src/MessageConnectionClosed.h
    src/MessageEncrypted.h
    src/MessageExecute.h
    src/MessageInit.h
    src/MessagePacket.h
    src/MessagePong.h
    src/MessageQueue.h
    src/MessageShutdown.h
    src/MessageTick.h
    src/MessageTimeout.h
    src/MessageWorldNotification.h
    src/Object.h
    src/ObjectReference.h
    src/Packet.h
    src/PacketCodes.h
    src/PacketException.h
    src/PacketParser.h
    #src/PacketScript.h
    src/PacketStream.h
    src/PEFile.h
    src/PEFormat.h
    src/PersistentObject.h
    #src/Platform.h
    #src/PlatformLinux.h
    #src/PlatformWindows.h
    src/Randomizer.h
    src/ReadOnlyPacket.h
    src/RingBuffer.h
    src/ScriptEngine.h
    src/ServerCommandLineParser.h
    src/ServerConstants.h
    src/ServerDataManager.h
    src/Shutdown.h
    src/TcpConnection.h
    src/TcpServer.h
    #src/ThreadManager.h
    src/Worker.h

    # These were generated and are not worth reading.
    src/LookupTableCP1252.h
    src/LookupTableCP932.h

    # Macros to temporarily disable warnings (wrapped around 3rd party libs).
    src/PushIgnore.h
    src/PopIgnore.h
)

IF(NOT WIN32)
    SET(${PROJECT_NAME}_HDRS
        ${${PROJECT_NAME}_HDRS}
        # for comp_manager and testing.
        src/Child.h
        src/DayCare.h
        src/SpawnThread.h
        src/WatchThread.h
    )
ENDIF(NOT WIN32)

SET(${PROJECT_NAME}_SCHEMA
    schema/account.xml
    schema/accountlogin.xml
    schema/action.xml
    schema/action_createloot.xml
    schema/action_setnpcstate.xml
    schema/action_startevent.xml
    schema/action_updateflag.xml
    schema/action_updatelnc.xml
    schema/action_updatequest.xml
    schema/action_zonechange.xml
    schema/character.xml
    schema/clan.xml
    schema/databaseconfig.xml
    schema/databaseconfig_mariadb.xml
    schema/databaseconfig_sqlite3.xml
    schema/demon.xml
    schema/enemy.xml
    schema/event.xml
    schema/event_direction.xml
    schema/event_getitem.xml
    schema/event_homepoint.xml
    schema/event_message.xml
    schema/event_openmenu.xml
    schema/event_performactions.xml
    schema/event_playbgm.xml
    schema/event_playscene.xml
    schema/event_playsoundeffect.xml
    schema/event_prompt.xml
    schema/event_stageeffect.xml
    schema/item.xml
    schema/packet_login.xml
    schema/packet_login_reply.xml
    schema/packet_response_code.xml
    schema/party.xml
    schema/qmp_file.xml
    schema/registeredchannel.xml
    schema/registeredworld.xml
    schema/server_command_line.xml
    schema/server_npc.xml
    schema/server_object.xml
    schema/server_shop.xml
    schema/server_zone.xml
    schema/serverconfig.xml
    schema/spawn.xml
    schema/test.xml

    # BinaryData Files
    schema/binarydata/ceventmessagedata.xml
    schema/binarydata/citemdata.xml
    schema/binarydata/cmessagedata.xml
    schema/binarydata/cmultitalkdata.xml
    schema/binarydata/cpolygonmoviedata.xml
    schema/binarydata/cquest.xml
    schema/binarydata/ctalkmessagedata.xml
    schema/binarydata/czonerelationdata.xml
    schema/binarydata/devildata.xml
    schema/binarydata/devillvupratedata.xml
    schema/binarydata/dynamicmapdata.xml
    schema/binarydata/expertdata.xml
    schema/binarydata/hnpcdata.xml
    schema/binarydata/itemdata.xml
    schema/binarydata/onpcdata.xml
    schema/binarydata/questdata.xml
    schema/binarydata/shared.xml
    schema/binarydata/shopproductdata.xml
    schema/binarydata/skilldata.xml
    schema/binarydata/spotdata.xml
    schema/binarydata/statusdata.xml
    schema/binarydata/triunionspecialdata.xml
    schema/binarydata/zonedata.xml
)

SOURCE_GROUP("objgen" ${CMAKE_CURRENT_BINARY_DIR}/objgen/*)

OBJGEN_XML(${PROJECT_NAME}_STRUCTS
    # Main schema
    schema/master.xml

    # Included schemas
    ${${PROJECT_NAME}_SCHEMA}

    # Include paths
    schema

    # Output files
    Account.h
    Account.cpp
    AccountLogin.h
    AccountLogin.cpp
    AccountWorldData.h
    AccountWorldData.cpp
    Action.h
    Action.cpp
    ActionCreateLoot.h
    ActionCreateLoot.cpp
    ActionSetNPCState.h
    ActionSetNPCState.cpp
    ActionStartEvent.h
    ActionStartEvent.cpp
    ActionUpdateFlag.h
    ActionUpdateFlag.cpp
    ActionUpdateLNC.h
    ActionUpdateLNC.cpp
    ActionUpdateQuest.h
    ActionUpdateQuest.cpp
    ActionZoneChange.h
    ActionZoneChange.cpp
    Clan.h
    Clan.cpp
    ClanInfo.h
    ClanInfo.cpp
    ClanMember.h
    ClanMember.cpp
    Character.h
    Character.cpp
    CharacterLogin.h
    CharacterLogin.cpp
    CharacterProgress.h
    CharacterProgress.cpp
    DatabaseConfig.h
    DatabaseConfig.cpp
    DatabaseConfigMariaDB.h
    DatabaseConfigMariaDB.cpp
    DatabaseConfigSQLite3.h
    DatabaseConfigSQLite3.cpp
    Demon.h
    Demon.cpp
    DemonBox.h
    DemonBox.cpp
    Enemy.h
    Enemy.cpp
    EntityStats.h
    EntityStats.cpp
    Event.h
    Event.cpp
    EventBase.h
    EventBase.cpp
    EventChoice.h
    EventChoice.cpp
    EventCondition.h
    EventCondition.cpp
    EventDirection.h
    EventDirection.cpp
    EventExNPCMessage.h
    EventExNPCMessage.cpp
    EventGetItem.h
    EventGetItem.cpp
    EventHomepoint.h
    EventHomepoint.cpp
    EventMessage.h
    EventMessage.cpp
    EventMultitalk.h
    EventMultitalk.cpp
    EventNPCMessage.h
    EventNPCMessage.cpp
    EventOpenMenu.h
    EventOpenMenu.cpp
    EventPerformActions.h
    EventPerformActions.cpp
    EventPlayBGM.h
    EventPlayBGM.cpp
    EventPlayScene.h
    EventPlayScene.cpp
    EventPlaySoundEffect.h
    EventPlaySoundEffect.cpp
    EventPrompt.h
    EventPrompt.cpp
    EventSequence.h
    EventSequence.cpp
    EventSpecialDirection.h
    EventSpecialDirection.cpp
    EventStageEffect.h
    EventStageEffect.cpp
    EventStopBGM.h
    EventStopBGM.cpp
    Expertise.h
    Expertise.cpp
    FriendSettings.h
    FriendSettings.cpp
    Hotbar.h
    Hotbar.cpp
    InheritedSkill.h
    InheritedSkill.cpp
    Item.h
    Item.cpp
    ItemBox.h
    ItemBox.cpp
    ItemDrop.h
    ItemDrop.cpp
    ObjectPosition.h
    ObjectPosition.cpp
    PacketLogin.h
    PacketLogin.cpp
    PacketLoginReply.h
    PacketLoginReply.cpp
    PacketResponseCode.h
    PacketResponseCode.cpp
    Party.h
    Party.cpp
    PartyCharacter.h
    PartyCharacter.cpp
    PartyMember.h
    PartyMember.cpp
    PostItem.h
    PostItem.cpp
    QmpFile.h
    QmpFile.cpp
    QmpElement.h
    QmpElement.cpp
    QmpBoundary.h
    QmpBoundary.cpp
    QmpBoundaryLine.h
    QmpBoundaryLine.cpp
    QmpUnknown1.h
    QmpUnknown1.cpp
    QmpUnknown2.h
    QmpUnknown2.cpp
    Quest.h
    Quest.cpp
    RegisteredChannel.h
    RegisteredChannel.cpp
    RegisteredWorld.h
    RegisteredWorld.cpp
    ServerBazaar.h
    ServerBazaar.cpp
    ServerCommandLine.h
    ServerCommandLine.cpp
    ServerConfig.h
    ServerConfig.cpp
    ServerNPC.h
    ServerNPC.cpp
    ServerObject.h
    ServerObject.cpp
    ServerObjectBase.h
    ServerObjectBase.cpp
    ServerShop.h
    ServerShop.cpp
    ServerShopProduct.h
    ServerShopProduct.cpp
    ServerShopTab.h
    ServerShopTab.cpp
    ServerZone.h
    ServerZone.cpp
    ServerZoneSpot.h
    ServerZoneSpot.cpp
    StatusEffect.h
    StatusEffect.cpp
    Spawn.h
    Spawn.cpp
    SpawnGroup.h
    SpawnGroup.cpp
    SpawnLocation.h
    SpawnLocation.cpp
    SpawnLocationGroup.h
    SpawnLocationGroup.cpp
    TestObject.h
    TestObject.cpp

    # BinaryData Files
    MiAcquisitionData.cpp
    MiAcquisitionData.h
    MiAcquisitionSkillData.cpp
    MiAcquisitionSkillData.h
    MiAddStatusTbl.cpp
    MiAddStatusTbl.h
    MiAIRelationData.cpp
    MiAIRelationData.h
    MiBattleDamageData.cpp
    MiBattleDamageData.h
    MiBreakData.cpp
    MiBreakData.h
    MiCancelData.cpp
    MiCancelData.h
    MiCastBasicData.cpp
    MiCastBasicData.h
    MiCastCancelData.cpp
    MiCastCancelData.h
    MiCastData.cpp
    MiCastData.h
    MiCategoryData.h
    MiCategoryData.cpp
    MiCEventMessageData.cpp
    MiCEventMessageData.h
    MiCItemBaseData.cpp
    MiCItemBaseData.h
    MiCItemData.cpp
    MiCItemData.h
    MiCItemMotionData.cpp
    MiCItemMotionData.h
    MiCItemSPEffectData.cpp
    MiCItemSPEffectData.h
    MiMultiTalkCmdTbl.cpp
    MiMultiTalkCmdTbl.h
    MiCMultiTalkData.cpp
    MiCMultiTalkData.h
    MiCMessageData.cpp
    MiCMessageData.h
    MiCPolygonMovieData.cpp
    MiCPolygonMovieData.h
    MiPMBaseInfo.cpp
    MiPMBaseInfo.h
    MiPMCameraKeyTbl.cpp
    MiPMCameraKeyTbl.h
    MiPMMsgKeyTbl.cpp
    MiPMMsgKeyTbl.h
    MiPMBGMKeyTbl.cpp
    MiPMBGMKeyTbl.h
    MiPMSEKeyTbl.cpp
    MiPMSEKeyTbl.h
    MiPMEffectKeyTbl.cpp
    MiPMEffectKeyTbl.h
    MiPMFadeKeyTbl.cpp
    MiPMFadeKeyTbl.h
    MiPMGouraudKeyTbl.cpp
    MiPMGouraudKeyTbl.h
    MiPMFogKeyTbl.cpp
    MiPMFogKeyTbl.h
    MiPMScalingHelperTbl.cpp
    MiPMScalingHelperTbl.h
    MiPMAttachCharacterTbl.cpp
    MiPMAttachCharacterTbl.h
    MiPMMotionKeyTbl.cpp
    MiPMMotionKeyTbl.h
    MiConditionData.cpp
    MiConditionData.h
    MiCorrectTbl.h
    MiCorrectTbl.cpp
    MiCostTbl.cpp
    MiCostTbl.h
    MiCQuestData.cpp
    MiCQuestData.h
    MiDamageData.cpp
    MiDamageData.h
    MiDCategoryData.cpp
    MiDCategoryData.h
    MiDevilBattleData.cpp
    MiDevilBattleData.h
    MiDevilData.cpp
    MiDevilData.h
    MiDevilFamiliarityData.cpp
    MiDevilFamiliarityData.h
    MiDevilLVUpData.cpp
    MiDevilLVUpData.h
    MiDevilLVUpRateData.cpp
    MiDevilLVUpRateData.h
    MiDevilReunionConditionData.cpp
    MiDevilReunionConditionData.h
    MiDischargeData.cpp
    MiDischargeData.h
    MiDoTDamageData.cpp
    MiDoTDamageData.h
    MiDynamicMapData.h
    MiDynamicMapData.cpp
    MiEffectData.cpp
    MiEffectData.h
    MiEffectiveRangeData.cpp
    MiEffectiveRangeData.h
    EventConditionData.cpp
    EventConditionData.h
    MiExpertClassData.cpp
    MiExpertClassData.h
    MiExpertData.cpp
    MiExpertData.h
    MiExpertGrowthTbl.cpp
    MiExpertGrowthTbl.h
    MiExpertRankData.cpp
    MiExpertRankData.h
    MiExpertUnkData.cpp
    MiExpertUnkData.h
    MiGrowthData.cpp
    MiGrowthData.h
    MiHNPCAppearanceData.cpp
    MiHNPCAppearanceData.h
    MiHNPCBasicData.cpp
    MiHNPCBasicData.h
    MiHNPCData.cpp
    MiHNPCData.h
    MiItemBasicData.h
    MiItemBasicData.cpp
    MiItemData.h
    MiItemData.cpp
    MiItemPvPData.h
    MiItemPvPData.cpp
    MiKnockBackData.cpp
    MiKnockBackData.h
    MiNegotiationDamageData.cpp
    MiNegotiationDamageData.h
    MiNegotiationData.cpp
    MiNegotiationData.h
    MiNextEpisodeInfo.cpp
    MiNextEpisodeInfo.h
    MiNPCBasicData.cpp
    MiNPCBasicData.h
    MiONPCData.cpp
    MiONPCData.h
    MiPossessionData.h
    MiPossessionData.cpp
    MiQuestData.h
    MiQuestData.cpp
    MiQuestPhaseData.h
    MiQuestPhaseData.cpp
    QuestPhaseRequirement.h
    QuestPhaseRequirement.cpp
    MiQuestUpperCondition.h
    MiQuestUpperCondition.cpp
    MiRentalData.h
    MiRentalData.cpp
    MiRestrictionData.cpp
    MiRestrictionData.h
    MiCZoneRelationData.h
    MiCZoneRelationData.cpp
    MiRelationZoneIDData.h
    MiRelationZoneIDData.cpp
    MiShopProductData.cpp
    MiShopProductData.h
    MiSkillBasicData.cpp
    MiSkillBasicData.h
    MiSkillCharasticData.cpp
    MiSkillCharasticData.h
    MiSkillData.cpp
    MiSkillData.h
    MiSkillItemStatusCommonData.h
    MiSkillItemStatusCommonData.cpp
    MiSkillPvPData.cpp
    MiSkillPvPData.h
    MiSkillSpecialParams.cpp
    MiSkillSpecialParams.h
    MiSkillTbl.h
    MiSkillTbl.cpp
    MiStatusBasicData.cpp
    MiStatusBasicData.h
    MiStatusData.cpp
    MiStatusData.h
    MiSummonData.cpp
    MiSummonData.h
    MiCTalkMessageData.cpp
    MiCTalkMessageData.h
    MiTargetData.cpp
    MiTargetData.h
    MiTriUnionSpecialData.cpp
    MiTriUnionSpecialData.h
    MiUnionData.cpp
    MiUnionData.h
    MiUseRestrictionsData.h
    MiUseRestrictionsData.cpp
    MiSpotData.h
    MiSpotData.cpp
    MiZoneBasicData.h
    MiZoneBasicData.cpp
    MiZoneBGMData.h
    MiZoneBGMData.cpp
    MiZoneCameraData.h
    MiZoneCameraData.cpp
    MiZoneData.h
    MiZoneData.cpp
    MiZoneFileData.h
    MiZoneFileData.cpp
    MiZoneFogData.h
    MiZoneFogData.cpp
    MiZoneGouraudData.h
    MiZoneGouraudData.cpp
    MiZoneLensFlareData.h
    MiZoneLensFlareData.cpp
    MiZoneLensFlareLayerData.h
    MiZoneLensFlareLayerData.cpp
    MiZoneOtherData.h
    MiZoneOtherData.cpp
    MiZoneSkyData.h
    MiZoneSkyData.cpp
)

COVERALLS_SOURCES(${${PROJECT_NAME}_SRCS})

ADD_LIBRARY(comp STATIC ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS}
    ${${PROJECT_NAME}_MOC_SRCS} ${${PROJECT_NAME}_STRUCTS})

TARGET_COMPILE_DEFINITIONS(comp PUBLIC ${SQRAT_DEFINES})

SET_TARGET_PROPERTIES(comp PROPERTIES FOLDER "Libraries")

TARGET_INCLUDE_DIRECTORIES(comp PUBLIC
    ${LIBCOMP_INCLUDES}
    ${ASIO_INCLUDE_DIRS}
)

TARGET_INCLUDE_DIRECTORIES(comp PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

TARGET_LINK_LIBRARIES(comp mariadbclient ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES}
    ${SYSTEM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} objgen sqlite3
    squirrel sqstdlib ttvfs ttvfs_zip tinyxml2 physfs)

ADD_DEPENDENCIES(comp asio sqrat gsl)

IF(WIN32)
    TARGET_LINK_LIBRARIES(comp advapi32 iphlpapi psapi shell32 userenv
        ws2_32 dbghelp)
ENDIF(WIN32)

# List of unit tests to add to CTest.
SET(${PROJECT_NAME}_TEST_SRCS
    Convert
    Decrypt

    # This test can take too long so disable it for now.
    # DiffieHellman

    GeneratedObjects
    MariaDB
    Packet
    ScriptEngine
    String
    VectorStream
    #XmlUtils
)

IF(NOT BSD)
    # Add the unit tests.
    CREATE_GTESTS(LIBS comp SRCS ${${PROJECT_NAME}_TEST_SRCS})
ENDIF(NOT BSD)
