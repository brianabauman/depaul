import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef, ActorSystem, PoisonPill, Props, Terminated}

case class Watch(watchee: ActorRef)

object DeathWatch extends App {
  val system = ActorSystem("DeathWatchClient", ConfigFactory.load.getConfig("client"))

  val watchee = system.actorOf(Props[SimpleActor], "watchee")
  val watcher = system.actorOf(Props[SimpleActor], "watcher")

  watcher ! "start"
  watchee ! "start" 
  watcher ! Watch(watchee)

  while(true) {}

  //Thread.sleep(5000)
  //watchee ! PoisonPill
}

class SimpleActor extends Actor {
  def receive = {
    case Terminated(corpse) => 
      println(s"${self.path.name} -- ${corpse.path.name} has died...")
    case Watch(watchee) => 
      println(s"${self.path.name} -- watching ${watchee.path.name}...")
      context.watch(watchee)
    case "start" => 
      println(s"${self.path.name} -- starting up...")
  }
}