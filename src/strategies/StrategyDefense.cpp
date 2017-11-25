#include "StrategyDefense.h"

StrategyDefense::StrategyDefense() : StrategyBase()	{
	name = "defense";
}

Command StrategyDefense::strategy(Robot robot, Command command){
	Command c = command;

	c = stop_strategy(c);

	return c;
}

btVector3 StrategyDefense::define_target(Robot robot){

	btVector3 target;
	btVector3 ballProjection = state.ball.get_projection();

	// altera o ponto de destino dependendo do sentido da bola, evitando bater no outro robo
	if(robot.x() < image_size.x*0.4){
		if(robot.y() > image_size.y/2){
			if(ballProjection.y < state.ball.y()){
				target = btVector3(image_size.x*0.5, image_size.y*0.2);
			} else {
				target = btVector3(image_size.x*0.5, image_size.y*0.8);
			}
		} else {
			if(ballProjection.y < state.ball.y()){
				target = btVector3(image_size.x*0.5, image_size.y*0.2);
			} else {
				target = btVector3(image_size.x*0.5, image_size.y*0.8);
			}
		}	
		
	}else{
		// se a bola esta no ataque posiciona o robo no meio do campo
		target = btVector3(image_size.x/2, image_size.y/2);
	}

	// posiciona o robo na defesa para facilitar a troca de posicao com o goleiro
	if(ballProjection.x > image_size.x/2){
		if(ballProjection.y > image_size.y/2){
			target = btVector3(image_size.x*0.7, image_size.y*0.2);
		} else {
			target = btVector3(image_size.x*0.7, image_size.y*0.8);
		}
	} 

	return target;
}