#pragma once

// Size?: 118h
struct CItemSaveState
{
  PVOID vtable;
  u32 unk0;

  PVOID pCItemSaveState;    // Linked list node? ptr to another CItemSaveState

  // UNICODE String ie "4 Gold" in place (16 bytes)
  // OR I noticed a ptr string to "TNT Barrel"
  // This appears to be that if the string is > 7 in length then it uses
  // a ptr in place of the unicode data (union)
  // Burn off the 16 bytes for now
  union {
    wchar_t name[8];    // In-place unicode data
    PVOID namePtr[4];   // First is the unicode ptr, the rest are unk
  };

  u32 nameLength;
  u32 maxNameLength;    // Guess, double check this

  // .. more
};