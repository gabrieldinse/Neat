#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   constexpr std::size_t NT_MAX_COMPONENTS = 64;


   // ---------------------------------------------------------------------- //
   // BaseComponent -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct BaseComponent
   {
      using Family = UInt;

      void operator delete(void* ptr) { fail(); }
      void operator delete[](void* ptr) { fail(); }

   protected:
      static void fail() { throw BadComponentAllocationError(); }

      static Family s_familyCounter;
   };


   // ---------------------------------------------------------------------- //
   // Component ------------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   struct Component : public BaseComponent
   {
   private:
      friend class EntityManager;

      static Family getFamily()
      {
         static Family family = s_familyCounter++;
         if (family >= NT_MAX_COMPONENTS)
            throw MaximumNumberOfComponentsError();

         return family;
      }
   };
}