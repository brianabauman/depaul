package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef, Props, ActorSystem, AddressFromURIString}
import akka.remote.routing.RemoteRouterConfig
import akka.routing.{Broadcast, RoundRobinPool, ConsistentHashingPool}
import akka.routing.ConsistentHashingRouter.ConsistentHashMapping

class MasterActor[K1, V1, K2, V2, V3] extends Actor {

  case class ReducerInput(k2: K2, v2: V2)

  var hashMapping: ConsistentHashMapping = null
  var printResults: (V3) => Unit = null

  val numberMappers  = ConfigFactory.load.getInt("number-mappers")
  val numberReducers  = ConfigFactory.load.getInt("number-reducers")
  
  val addresses = Seq(
  //  AddressFromURIString(self.path.toString),
    AddressFromURIString("akka.tcp://MapReduceServer@127.0.0.1:2552"),
    AddressFromURIString("akka.tcp://MapReduceServer@127.0.0.1:2553"),
    AddressFromURIString("akka.tcp://MapReduceServer@127.0.0.1:2554"))
  //  AddressFromURIString("akka.tcp://MapReduceServer@127.0.0.1:2555"))

  var pending = numberReducers
  var reducerRemoteRouter: ActorRef = null
  var mapperRemoteRouter: ActorRef = null

  def receive = {
    case Start(activity: String) =>
      println(s"${self.path.name}: Configuring ${activity}...")
      configureSystem(activity)
    case MapperInput(k1: K1, v1: V1) =>
      mapperRemoteRouter ! MapperInput[K1, V1](k1, v1)
    case Finished =>      
      mapperRemoteRouter ! Broadcast(Finished)
    case ReducerOutput(v3: V3) =>
      printResults(v3)
      pending -= 1
      if (pending == 0) println(s"${self.path.name}: Processing finished...")
    case _ => //debug
      println(s"debug ${self.path.name}: received unnknown message...")

  }

  def configureSystem(activity: String) = {
    activity match {
      case "wordcounts" =>
        hashMapping = WordCount.hashMapping
        printResults = WordCount.printResults[V3] _
      case "propernouns" =>
        hashMapping = ProperNouns.hashMapping
        printResults = ProperNouns.printResults[V3] _
      case "hyperlinks" =>
        hashMapping = Hyperlinks.hashMapping
        printResults = Hyperlinks.printResults[V3] _
      case _ => 
        println(s"debug ${self.path.toString}: unknown activity...")
        //send error to client?
    }

    reducerRemoteRouter = context.actorOf(
      RemoteRouterConfig(
        ConsistentHashingPool(numberReducers, 
                              hashMapping = hashMapping),
        addresses)
      .props(Props[GenericReducerActor[K2, V2, V3]]))
    reducerRemoteRouter ! Broadcast(ReducerConfig(activity, numberMappers, self))
        
    mapperRemoteRouter = context.actorOf(
      RemoteRouterConfig(
        RoundRobinPool(numberMappers), 
        addresses)
      .props(Props[GenericMapperActor[K1, V1, K2, V2]]))
    mapperRemoteRouter ! Broadcast(MapperConfig(activity, reducerRemoteRouter))
  }
}
