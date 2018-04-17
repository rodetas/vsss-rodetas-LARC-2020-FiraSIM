#include <StrategyBase.h>

StrategyBase::StrategyBase(){
    goal_size  = btVector3(10,40);
    image_size = btVector3(170,130);
    movimentation = new UnivectorField();
}

Robot StrategyBase::apply(map<string, int> _id, RodetasState _state){

    // update states
    set_state(_id, _state);

    // update robot in this class
    robot.update_robot(_state.robots[id[name]]);

    // define target
    btVector3 target = define_target(robot);
    robot.set_target(target);

    // define basic movimentation
    Command movimentationCommand = movimentation->move_players(robot, robot.get_target());

    // define strategy
    Command strategyCommand = strategy(robot, movimentationCommand);

    // define command
    define_command(strategyCommand);

    return robot;
}

void StrategyBase::move(map<string, int> _id, RodetasState _state){
    
    // update states
    set_state(_id, _state);

    // update robot in this class
    robot.update_robot(_state.robots[id[name]]);    

    // define basic movimentation
    Command movimentationCommand = movimentation->move_players(robot, robot.get_target());

    // define strategy
    Command strategyCommand = stop_strategy(movimentationCommand);
    
    // define command
    define_command(strategyCommand); 
}

 Command StrategyBase::corner_strategy(Command command){
    Command c = command;

    //cout << robot.is_board(image_size) << " " << robot.is_stopped() << " " << robot.get_velocity() << endl;

	if (robot.is_board(image_size) && robot.is_stopped()){

        // girar caso robo esteja preso de frente pra parede
        if (robot.cos_from(state.ball.get_position()) > -0.9 && robot.cos_from(state.ball.get_position()) < 0.9) {
            if (robot.sin_from(state.ball.get_position()) > 0) {
                c = movimentation->turn_right(50,30);
            } else {
                c = movimentation->turn_left(50,50);
            }
//            cout << "preso pra parede" << endl;
        } 
        
        // girar caso robo prenda a bola na parede - 8 cm
        if (robot.distance_from(state.ball.get_position()) < (8) ) {

            if (robot.y() < (image_size.y/2)){
                c = movimentation->turn_left(60,60);
            } else {
                c = movimentation->turn_right(60,60);
            }
//            cout << "preso com bola" << endl;
        }
    }

    return c;
}

Command StrategyBase::stop_strategy(Command _command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = _command;
    float max_distance = 12; // 12 cm
	float distance_target = robot.distance_from(robot.get_target());

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		max_distance = 24; // 24 cm
	}
 */

	if(distance_target < max_distance){
		c.left  = c.left  * (distance_target/max_distance);
		c.right = c.right * (distance_target/max_distance);
	}

	if(distance_target < 4){ 

        if (robot.cos_from(state.ball.get_projection()) < -0.8 || robot.cos_from(state.ball.get_projection()) > 0.8) {
            c = movimentation->stop();
 
        } else {

            if (robot.sin_from(state.ball.get_position()) > 0) {
                c = movimentation->turn_right(10, 10);
            } else {
                c = movimentation->turn_left(10, 10);
            }
        }
    }

    return c;
}

Command StrategyBase::collision_strategy(Command _command){
    return Command(0,0);
}

Command StrategyBase::blocked_strategy(Command _command){
    return Command(0,0);
}

Command StrategyBase::kick_strategy(Command _command){
    return Command(0,0);
}

void StrategyBase::set_state(map<string, int> _id, RodetasState _state){
    id = _id;
    state = _state;
}

Robot StrategyBase::get_robot(string func){
    return state.robots[id[func]];
}

Command StrategyBase::get_command(){
    return command;
}

void StrategyBase::define_command(Command _command){
	command = _command;
}
