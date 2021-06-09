package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef, Props, ActorSystem}
import akka.routing.{Broadcast, RoundRobinPool}

class MasterActor extends Actor {
  val numberMappers  = ConfigFactory.load.getInt("number-mappers")
  val numberReducers  = ConfigFactory.load.getInt("number-reducers")
  var pending = numberReducers

  var reduceActors = List[ActorRef]()
  for (i <- 0 until numberReducers) {
    reduceActors = context.actorOf(Props[ReduceActor], name = "reduce"+i)::reduceActors
  }

  val mapActors = context.actorOf(RoundRobinPool(numberMappers).props(Props(classOf[MapActor], reduceActors)))

  def receive = {
    case Book(title: String, url: String) =>
      mapActors ! Book(title, url)
    case Flush =>
      mapActors ! Broadcast(Flush)
    case Done =>
      pending -= 1
      if (pending == 0) {
        context.system.terminate
      }
  }
}
