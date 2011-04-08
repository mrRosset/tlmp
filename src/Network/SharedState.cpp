#include "SharedState.h"
using namespace TLMP;

vector<NetworkEntity*> *TLMP::NetworkSharedEquipment  = new vector<NetworkEntity*>();
vector<NetworkEntity*> *TLMP::NetworkSharedCharacters = new vector<NetworkEntity*>();
vector<NetworkEntity*> *TLMP::ClientTemporaryEquipment = new vector<NetworkEntity*>();
vector<NetworkEntity*> *TLMP::ServerEquipmentOnGround = new vector<NetworkEntity*>();
vector<NetworkEntity*> *TLMP::NetworkSharedLevelItems = new vector<NetworkEntity*>();
vector<CBaseUnit*>     *TLMP::OutsideBaseUnits = new vector<CBaseUnit*>();

map<SystemAddress, vector<NetworkEntity*>*> *TLMP::Server_ClientCharacterMapping = new map<SystemAddress, vector<NetworkEntity*>*>();
map<SystemAddress, NetworkEntity*> *TLMP::Server_ClientUnequipMapping = new map<SystemAddress, NetworkEntity*>();

void TLMP::clearAllNetworkIDs()
{
  if (TLMP::Network::NetworkState::getSingleton().GetState() == TLMP::Network::CLIENT) {
    // Commented this because server doesn't recreate it's characters' inventory on level changes
    NetworkSharedEquipment->clear();
  }

  NetworkSharedCharacters->clear();
  ClientTemporaryEquipment->clear();
  ServerEquipmentOnGround->clear();
  OutsideBaseUnits->clear();
  NetworkSharedLevelItems->clear();

  Server_ClientCharacterMapping->clear();
  Server_ClientUnequipMapping->clear();
}
