#ifndef ABSTRACT_STATE_HPP
#define ABSTRACT_STATE_HPP

#include "Common.hpp"
#include "StateManager.hpp"


class AbstractState : private sf::NonCopyable // Abstract state finite state machine for the playing state 
{
public:
	AbstractState(StateManager& state_manager, bool load_game_ = false) :
		state_manager_(state_manager),
		paused_(false)
	{
		this->load_game_ = load_game_;
	}
	virtual ~AbstractState(){}

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void update(const sf::Time& delta) = 0;
	virtual void render() = 0;
	virtual void handle_input(const sf::Time& delta) = 0;
	virtual void handle_state_changes() = 0;

	void set_paused(bool pause) { paused_ = pause; }
	bool get_paused() const { return paused_; }

protected:
	StateManager& state_manager_;
	bool load_game_;
private:
	bool paused_;

	const std::string state_name_;
};

#endif