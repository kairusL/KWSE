#pragma once
#include "State.h"

namespace KWSE::AI
{
	template<class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>; // "using ... = ... ; " means def a name for whatevery you want to keep using.

		StateMachine(AgentType& agent)   //pass in AgentType => instance the calling type.
			: mAgent(agent)      
		{}

		//StateMachine(AgentType& agent);

		/*template<class NewStateType, 
			class = std::void_t<std::is_base_of <StateType,NewStateType>>>*/ //return true or false
		template<class NewStateType>
		void AddState(std::string name)
		{
			//static assertion means will check while compilering. get the error while compile time.
			//assertion with out static will let you run and compile for you. will get error during running time.
			//is_base_of=>bool check.   |CheckType|  |passingType|
			static_assert(std::is_base_of<StateType, NewStateType>::value,"[StateMachine] Can only add state for AgentType." );
			
			//auto=>std::pair<std::unordered_map<std::string, std::unique_ptr<StateType>>::iterrator, bool> [iter, success]
			//unorderedmap.emplace =>  std::pair<iterator,bool>.
			//make_unique => create a unique_ptr 
			auto[iter, success] =mState.emplace(std::move(name), std::make_unique<NewStateType>());
			if (success && !mCurrentState)
			{
				mCurrentState = iter->second.get();
			}
			//SFINAE
			//Substitution Failure is Not An Error.
		}


		void Update(float deltaTime)
		{
			mCurrentState->Update(mAgent, deltaTime);
		}
		void ChangeState(std::string stateName)
		{
			auto iter = mState.find(stateName);
			if (iter == mState.end())
			{
				return;
			}
				mCurrentState->Exit(mAgent);
				mCurrentState = iter->second.get();
				mCurrentState->Enter(mAgent);
			
		}
	private:
		//unordered_map=>fast access to individual elements directly by their key values 
		//type no need to sort key or mapped values//
		//unique_ptr is smartptr if you exit scope it delet itself.
		using StateMap = std::unordered_map<std::string, std::unique_ptr<StateType>>;

		AgentType& mAgent; // AgentType is object that use stateMachine.  &=> it cant not be nullptr.
		StateType* mCurrentState = nullptr;
		StateMap mState;
	};


}