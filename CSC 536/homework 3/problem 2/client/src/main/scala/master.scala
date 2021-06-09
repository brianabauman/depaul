package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef, Props, ActorSystem, AddressFromURIString}
import akka.remote.routing.RemoteRouterConfig
import akka.routing.{Broadcast, RoundRobinPool, ConsistentHashingPool}
import akka.routing.ConsistentHashingRouter.ConsistentHashMapping

class MasterActor extends Actor {
  val numberMappers  = ConfigFactory.load.getInt("number-mappers")
  val numberReducers  = ConfigFactory.load.getInt("number-reducers")
  var pending = numberReducers

  val addresses = Seq(
    AddressFromURIString("akka.tcp://MapReduceServer@127.0.0.1:2552"),
    AddressFromURIString(self.path.toString))

  def hashMapping: ConsistentHashMapping = {
    case Word(text: String, bookTitle: String) => 
      text.hashCode() % numberReducers
  }
  val reducerRemoteRouter = context.actorOf(
    RemoteRouterConfig(ConsistentHashingPool(numberReducers, hashMapping = hashMapping), addresses).props(Props(classOf[ReduceActor], self)))
  val mapperRemoteRouter = context.actorOf(
    RemoteRouterConfig(RoundRobinPool(numberMappers), addresses).props(Props(classOf[MapActor], reducerRemoteRouter)))

  def receive = {
    case Book(title: String, url: String) =>
      mapperRemoteRouter ! Book(title, url)
    case Flush =>
      mapperRemoteRouter ! Broadcast(Flush)
    case Done =>
      pending -= 1
      if (pending == 0) {
        context.system.terminate
      }
  }
}
