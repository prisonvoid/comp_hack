/**
 * @file server/channel/src/packets/game/FixObjectPosition.cpp
 * @ingroup channel
 *
 * @author HACKfrost
 *
 * @brief Request from the client to fix the position of a game object.
 *
 * This file is part of the Channel Server (channel).
 *
 * Copyright (C) 2012-2016 COMP_hack Team <compomega@tutanota.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Packets.h"

// libcomp Includes
#include <Log.h>
#include <ManagerPacket.h>
#include <PacketCodes.h>

// channel Includes
#include "ChannelClientConnection.h"
#include "ChannelServer.h"
#include "CharacterManager.h"

using namespace channel;

bool Parsers::FixObjectPosition::Parse(libcomp::ManagerPacket *pPacketManager,
    const std::shared_ptr<libcomp::TcpConnection>& connection,
    libcomp::ReadOnlyPacket& p) const
{
    if(p.Size() != 16)
    {
        return false;
    }

    auto server = std::dynamic_pointer_cast<ChannelServer>(pPacketManager->GetServer());
    auto client = std::dynamic_pointer_cast<ChannelClientConnection>(connection);
    auto state = client->GetClientState();

    int32_t entityID = p.ReadS32Little();

    auto eState = state->GetEntityState(entityID);
    if(nullptr == eState)
    {
        LOG_ERROR(libcomp::String("Invalid entity ID received from a fix object position"
            " request: %1\n").Arg(entityID));
        return false;
    }

    float destX = p.ReadFloat();
    float destY = p.ReadFloat();
    ClientTime stop = (ClientTime)p.ReadFloat();

    ServerTime stopTime = state->ToServerTime(stop);

    // Stop using the current rotation value
    eState->RefreshCurrentPosition(server->GetServerTime());
    float rot = eState->GetCurrentRotation();
    eState->SetDestinationRotation(rot);

    eState->SetDestinationX(destX);
    eState->SetCurrentX(destX);
    eState->SetDestinationY(destY);
    eState->SetCurrentY(destY);

    eState->SetDestinationTicks(stopTime);

    libcomp::Packet reply;
    reply.WritePacketCode(ChannelToClientPacketCode_t::PACKET_FIX_OBJECT_POSITION);
    reply.WriteS32Little(entityID);
    reply.WriteFloat(destX);
    reply.WriteFloat(destY);
    reply.WriteFloat(stop);

    server->GetZoneManager()->BroadcastPacket(client, reply, false);

    auto dState = std::dynamic_pointer_cast<DemonState>(eState);
    if(nullptr != dState)
    {
        // If a demon is being placed, it will have already been described to the
        // the client by this point so create and show it now.
        server->GetZoneManager()->PopEntityForZoneProduction(client, dState->GetEntityID(), 2);
        server->GetZoneManager()->ShowEntityToZone(client, dState->GetEntityID());
    }

    return true;
}
