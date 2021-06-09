package mapreduce

import com.typesafe.config.ConfigFactory

import akka.actor.{ActorSystem, Actor, Props}

object MapReduceServer extends App {
  val system = ActorSystem("MapReduceServer", ConfigFactory.load.getConfig("reducerServer"))
  println("Server ready...")
  Thread.sleep(999999)
  system.terminate
}
