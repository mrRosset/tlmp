#pragma once

#include "raknet/include/RakPeerInterface.h"
#include "raknet/include/RakNetworkFactory.h"
#include "raknet/include/MessageIdentifiers.h"
#include "raknet/include/BitStream.h"

#include "lobby/LobbyMessages.h"
using namespace TLMP::Network::Lobby;

#include "UI.h"
#include "lobby.pb.h"
#include "Game.h"


namespace TLMP {
  namespace Network {
    namespace Lobby {

      class LobbyClient
      {
      public:
        static LobbyClient& getSingleton();

        void Connect(const char* address, unsigned short port);
        void Disconnect();
        bool IsConnected();
        void ReceiveMessages();

        Game* getGameFromIndex(int index);

        template<typename T>
        void SendMessage(LobbyMessage msg, ::google::protobuf::Message *message);

      protected:
        LobbyClient();
        LobbyClient(const LobbyClient&);
        LobbyClient& operator=(const LobbyClient&);
        ~LobbyClient();

      private:
        /** Work on received packet data. */
        void WorkMessage(LobbyMessage msg, RakNet::BitStream *bitStream);

        // Handle messages
        void HandleVersion(LobbyMessages::Version *);
        void HandleClientPlayerName(LobbyMessages::ClientPlayerName *);
        void HandleBatchPlayerNames(LobbyMessages::BatchPlayerNames *);
        void HandlePlayerLeft(LobbyMessages::PlayerLeft *);
        void HandleChatMessage(LobbyMessages::ChatMessage *);

        /** */
        void HandleViewGames(LobbyMessages::ViewGames *);
        void HandleHostingNewGame(LobbyMessages::GameID *msgGameID);
        void HandleGameInfo(LobbyMessages::GameInfo *msgGameInfo);
        
        template<typename T>
        T* ParseMessage(RakNet::BitStream *bitStream);

        map<int, Game*> m_gamesList;

        RakPeerInterface *m_pClient;
        RakNet::BitStream *m_pBitStream;
        bool m_bConnected;
      };

    };
  };
};

// Template parameterization, needs to be defined after above declarations
#include "LobbyClient.cpp.h"
