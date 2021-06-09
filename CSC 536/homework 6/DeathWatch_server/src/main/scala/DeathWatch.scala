import com.typesafe.config.ConfigFactory

import akka.actor.{Actor, ActorRef, ActorSystem, PoisonPill, Props, Terminated}

case class Watch(watchee: ActorRef)

object Server extends App {
  val system = ActorSystem("DeathWatchServer", ConfigFactory.load.getConfig("server"))
  println("DeathWatch server ready...")
  Thread.sleep(999999)
  system.terminate
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