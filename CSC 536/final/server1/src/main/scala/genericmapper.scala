package mapreduce

import akka.actor.{Actor, ActorRef}
import akka.routing.Broadcast

class GenericMapperActor[K1, V1, K2, V2] extends Actor {

  var reducers: ActorRef = null
  var map: (K1, V1) => Unit = null

  def receive = {
    case MapperConfig(activity: String, reducerRouter: ActorRef) => 
      configureMapper(activity, reducerRouter)
      println(s"debug ${self.path.toString}: mapper configured...")
    case MapperInput(k1: K1, v1: V1) =>        
      map(k1, v1)
    case Finished => 
      println(s"debug ${self.path.toString}: mapper finished...")
      reducers ! Broadcast(Finished)
  }

  def configureMapper(activity: String, reducerRouter: ActorRef) = {
    reducers = reducerRouter

    activity match {
      case "wordcounts" =>
        map = WordCount.map[K1, V1](_, _, reducerRouter)
      case "propernouns" =>
        map = ProperNouns.map[K1, V1](_, _, reducerRouter) 
      case "hyperlinks" =>
        map = Hyperlinks.map[K1, V1](_, _, reducerRouter)
      case _ =>
        println(s"debug ${self.path.toString}: unknown activity...")
    }
  }
}
