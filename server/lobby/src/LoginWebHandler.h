/**
 * @file server/lobby/src/LoginWebHandler.h
 * @ingroup lobby
 *
 * @author COMP Omega <compomega@tutanota.com>
 *
 * @brief Civet login webpage handler.
 *
 * This file is part of the Lobby Server (lobby).
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

#ifndef SERVER_LOBBY_SRC_LOGINWEBHANDLER_H
#define SERVER_LOBBY_SRC_LOGINWEBHANDLER_H

// Civet Includes
#include <CivetServer.h>

// libcomp Includes
#include <CString.h>
#include <Database.h>

// object Includes
#include <LobbyConfig.h>

// Standard C++11 Includes
#include <vector>

// VFS Includes
#include "PushIgnore.h"
#include <ttvfs/ttvfs.h>
#include <ttvfs/ttvfs_zip.h>
#include "PopIgnore.h"

namespace lobby
{

class AccountManager;
class SessionManager;

class LoginHandler : public CivetHandler
{
public:
    LoginHandler(const std::shared_ptr<libcomp::Database>& database);
    virtual ~LoginHandler();

    virtual bool handleGet(CivetServer *pServer,
        struct mg_connection *pConnection);

    virtual bool handlePost(CivetServer *pServer,
        struct mg_connection *pConnection);

    void SetConfig(const std::shared_ptr<objects::LobbyConfig>& config);

    void SetAccountManager(AccountManager *pManager);

    void SetSessionManager(SessionManager *pManager);

private:
    class ReplacementVariables
    {
    public:
        ReplacementVariables();

        libcomp::String birthday;
        libcomp::String cv;
        libcomp::String cvDisp;
        libcomp::String id;
        libcomp::String idReadOnly;
        libcomp::String idsave;
        libcomp::String idsaveReadOnly;
        libcomp::String msg;
        libcomp::String pass;
        libcomp::String passReadOnly;
        libcomp::String sid1;
        libcomp::String sid2;
        libcomp::String submit;
        bool auth;
        bool quit;
    };

    void ParsePost(CivetServer *pServer, struct mg_connection *pConnection,
        ReplacementVariables& postVars);

    bool HandlePage(CivetServer *pServer, struct mg_connection *pConnection,
        ReplacementVariables& postVars);

    std::vector<char> LoadVfsFile(const libcomp::String& path);

    ttvfs::Root mVfs;

    std::shared_ptr<libcomp::Database> mDatabase;
    std::shared_ptr<objects::LobbyConfig> mConfig;

    AccountManager *mAccountManager;
    SessionManager *mSessionManager;
};

} // namespace lobby

#endif // SERVER_LOBBY_SRC_LOGINWEBHANDLER_H
