#pragma once

#include <stdexcept>
#include <string>


namespace Neat
{
   // -------------------------------------------------------------------------
   // Base common exception ---------------------------------------------------
   struct Exception : public std::exception
   {
      Exception(const std::string& msg) : m_msg(msg) {}

      const std::string& msg() const { return m_msg; }
      virtual const char* what() const override { return m_msg.c_str(); }

   private:
      std::string m_msg;
   };
   // -------------------------------------------------------------------------
   // -------------------------------------------------------------------------


   // Timer exceptions --------------------------------------------------
   struct StopwatchError : Exception
   {
      StopwatchError(const std::string& msg) : Exception(msg) {}
   };

   struct WrongTimeUnitError : public StopwatchError
   {
      WrongTimeUnitError(
         const std::string& msg = "Wrong TimeUnit.")
         : StopwatchError(msg) {}
   };

   struct StopwatchNotStartedError : public StopwatchError
   {
      StopwatchNotStartedError(
         const std::string& msg = "Timer has not been started.")
         : StopwatchError(msg) {}
   };
   // -------------------------------------------------------------------------


   // Math exceptions ---------------------------------------------------------
   struct MathError : public Exception
   {
      MathError(const std::string& msg) : Exception(msg) {}
   };

   // Vectors
   struct VectorDimensionError : public MathError
   {
      VectorDimensionError(
         const std::string& msg = "Wrong Vector dimension being acessed.")
         : MathError(msg) {}
   };

   // Matrices
   struct MatrixDimensionError : public MathError
   {
      MatrixDimensionError(
         const std::string& msg = "Wrong Matrix dimension being acessed.")
         : MathError(msg) {}
   };
   // -------------------------------------------------------------------------


   // Event exceptions --------------------------------------------------------
   struct EventError : public Exception
   {
      EventError(const std::string& msg) : Exception(msg) {}
   };

   // Event subscriptions
   struct EventSubscriptionError : public EventError
   {
      EventSubscriptionError(
         const std::string& msg = "Event is not subscribed.")
         : EventError(msg) {}
   };
   // -------------------------------------------------------------------------


   // ECS exceptions ----------------------------------------------------------
   struct ECSError : public Exception
   {
      ECSError(const std::string& msg) : Exception(msg) {}
   };

   // Components
   struct ComponentError : public ECSError
   {
      ComponentError(const std::string& msg) : ECSError(msg) {}
   };

   struct BadComponentAllocationError : public ComponentError
   {
      BadComponentAllocationError(
         const std::string& msg = "You should not delete components directly. "
            "Use Entity::destroyEntity() instead.")
         : ComponentError(msg) {}
   };

   struct InvalidComponentError : public ComponentError
   {
      InvalidComponentError(
         const std::string& msg = "Acessed component is invalid.")
         : ComponentError(msg) {}
   };

   struct MaximumNumberOfComponentsError : public ComponentError
   {
      MaximumNumberOfComponentsError(
         const std::string& msg = "Maximum number of components reached.")
         : ComponentError(msg) {}
   };

   // Entities
   struct EntityError : public ECSError
   {
      EntityError(const std::string& msg) : ECSError(msg) {}
   };

   struct InvalidEntityError : public EntityError
   {
      InvalidEntityError(
         const std::string& msg = "Acessed Entity is invalid.")
         : EntityError(msg) {}
   };
   
   struct InvalidEntityIdIndexError : public InvalidEntityError
   {
      InvalidEntityIdIndexError(
         const std::string& msg = "Entity::Id outside Entity vector range.")
         : InvalidEntityError(msg) {}
   };

   struct InvalidEntityIdVersionError : public InvalidEntityError
   {
      InvalidEntityIdVersionError(
         const std::string& msg = "Attempt to access Entity via a stale"
            " Entity::Id.")
         : InvalidEntityError(msg) {}
   };

   struct ComponentAlreadyAddedError : public EntityError
   {
      ComponentAlreadyAddedError(
         const std::string& msg = "Component already added to Entity.")
         : EntityError(msg) {}
   };

   struct ComponentNotPresentError : public EntityError
   {
      ComponentNotPresentError(
         const std::string& msg = "Component is not present in the Entity.")
         : EntityError(msg) {}
   };
   
   // Systems
   struct SystemManagerNotInitializedError : public ECSError
   {
      SystemManagerNotInitializedError(
         const std::string& msg = "SystemManager::init() not called.")
         : ECSError(msg) {}
   };

   struct InvalidSystemError : public ECSError
   {
      InvalidSystemError(const std::string& msg = "System does not exist.")
         : ECSError(msg) {}
   };
   // -------------------------------------------------------------------------
}