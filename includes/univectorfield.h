//
// Created by manoel on 24/03/18.
//

#ifndef SDK_RODETAS_UNIVECTORFIELD_HPP
#define SDK_RODETAS_UNIVECTORFIELD_HPP

#include <common.h>
#include <movimentation.h>
#include <robot.h>
#include <ball.h>

#include <functional>

using namespace common;

class UnivectorField : public Movimentation {

public:

	UnivectorField();

	Command move_players(Robot, btVector3) override;
	float define_fi(Robot& p, btVector3 r, btVector3 g);

	Command define_pwm(Robot, btVector3, char) override;

};

#endif //SDK_RODETAS_UNIVECTORFIELD_HPP
