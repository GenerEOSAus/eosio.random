#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>
using namespace eosio;

class random : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action
      void rand() {
         checksum256 result;
         auto mixedBlock = tapos_block_prefix() * tapos_block_num();

         const char *mixedChar = reinterpret_cast<const char *>(&mixedBlock);
         sha256( (char *)mixedChar, sizeof(mixedChar), &result);
         const char *p64 = reinterpret_cast<const char *>(&result);

         for(int i = 0; i<6; i++) {
           auto r = (abs((int64_t)p64[i]) % (49 + 1 - 1)) + 1;
           print(" ", r);
         }

      }
};

EOSIO_ABI( random, (rand) )
